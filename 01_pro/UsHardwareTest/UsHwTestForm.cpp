#include "UsHwTestForm.h"
#include "ui_UsHwTestForm.h"

#include <QDebug>
#include <QMap>
#include <QString>
#include <QFileDialog>

#include "UsHwPowerControl.h"
#include "UltraSmartLog.h"
#include "TestCaseAutoPowerTest.h"
#include "TestCaseBatteryTest.h"
#include "TestCasePcieTest.h"
#include "TestCaseLpcTest.h"


static  const char   *g_pcParamsCfgFileDefaultPath = ".\\DefaultTestCfg.ini";
static  const char   *g_pcGlobalParamSection = "GlobalParams";

static  const char   *g_pcRuntimeCfgFilePath = ".\\RuntimeCfg.ini";
static  const char   *g_pcRuntimeParamSection = "RuntimeCfg";


static QString  g_strLogDir = ".\\LeogaoLog";
static QString  g_strDefaultLogFile = "AutoTestLog.txt";

#define UH_CURRENT_TEST_CNT             "CurrentTestCnt"
#define UH_SINGLE_TEST_TIME             "SingleTestTime"
#define UH_TOTAL_TEST_COUNT             "TestCount"
#define UH_TOTAL_TEST_TIME              "TestTime"
#define UH_CHECK_TOTAL_TEST_COUNT       "CheckTestCount"
#define UH_CHECK_TOTAL_TEST_TIME        "CheckTestTime"


static  char  *g_apcRuntimeCfgKey[] =
{
    UH_CURRENT_TEST_CNT,
    UH_SINGLE_TEST_TIME,
    UH_TOTAL_TEST_COUNT,
    UH_TOTAL_TEST_TIME,
    UH_CHECK_TOTAL_TEST_COUNT,
    UH_CHECK_TOTAL_TEST_TIME
};


UsHwTestForm::UsHwTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsHwTestForm)
{
    ui->setupUi(this);

    m_uiTestcaseCnt = 0;
    m_uiRecvResultCnt = 0;

    UsHwCreateHwTestTree();

    UsHwConnectSignalAndSlots();

    UsHwLoadParams(g_pcParamsCfgFileDefaultPath);

    if (IsAutoRun())
    {
        UsHwAutoStartTest();
    }
}

UsHwTestForm::~UsHwTestForm()
{
    delete ui;
}

void UsHwTestForm::UsHwCreateHwTestTree()
{
    UH_TEST_CASE_S   g_astTestCase[] =
    {
        {"Power",           NULL, NULL, NULL, NULL},
        {"AutoPowerTest",   &g_astTestCase[0].pitemTestCase, NULL, NULL, (CUsHwCustomWidget*)new TestCaseAutoPower()},
        {"BatteryI2cTest",  &g_astTestCase[0].pitemTestCase, NULL, NULL, (CUsHwCustomWidget*)new TestCaseBatteryI2C()},
        {"BackEnd",         NULL, NULL, NULL, NULL},
        {"PciePressTest",   &g_astTestCase[3].pitemTestCase, NULL, NULL, (CUsHwCustomWidget*)new TestCasePciePress()},
        {"LpcPressTest",    &g_astTestCase[3].pitemTestCase, NULL, NULL, (CUsHwCustomWidget*)new TestCaseLpcPress()}
    };

    QStandardItemModel  *model = new QStandardItemModel(ui->treeView_HwTestItems);
    model->setHorizontalHeaderLabels(QStringList() << tr("Test Items") << tr("Test Result"));

    QStandardItem   *pitemTestCaseTitle = NULL;
    QStandardItem   *pitemTestCaseResult = NULL;
    uint            uiIndex = 0;
    uint            uiItemsCnt = sizeof(g_astTestCase) / sizeof(UH_TEST_CASE_S);

    m_pStackedWgtParams = new QStackedWidget(this);

    for (uiIndex = 0; uiIndex < uiItemsCnt; uiIndex++)
    {
        pitemTestCaseTitle = new QStandardItem(tr(g_astTestCase[uiIndex].strCaption.toLocal8Bit().data()));
        if (NULL == pitemTestCaseTitle)
        {
            qDebug() << " pitemTestCaseTitle is NULL \n";
        }

        pitemTestCaseTitle->setCheckable(true);

        g_astTestCase[uiIndex].pitemTestCase = pitemTestCaseTitle;

        if (NULL == g_astTestCase[uiIndex].pitemParent)
        {
            pitemTestCaseTitle->setTristate(true);
            model->appendRow(pitemTestCaseTitle);
        }
        else
        {
            (*(g_astTestCase[uiIndex].pitemParent))->appendRow(pitemTestCaseTitle);
            pitemTestCaseResult = new QStandardItem(tr(UH_TEST_RESULT_TODO));
            (*g_astTestCase[uiIndex].pitemParent)->setChild(pitemTestCaseTitle->index().row(), 1, pitemTestCaseResult);

            m_pStackedWgtParams->addWidget(g_astTestCase[uiIndex].pwgtTestCase);

            g_astTestCase[uiIndex].pitemTestResult = pitemTestCaseResult;

            m_vectorUsHwTestCases.append(g_astTestCase[uiIndex]);
        }
    }

    m_pStackedWgtParams->setCurrentIndex(0);
    ui->gridLayout->addWidget(m_pStackedWgtParams, 0, 0);

    ui->treeView_HwTestItems->setModel(model);
    ui->treeView_HwTestItems->expandAll();
    ui->treeView_HwTestItems->setColumnWidth(0, 180);

    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(treeItemChanged(QStandardItem*)));
  
    ui->label_CurrCntVal->setVisible(false);
    ui->label_CurrCntTitle->setVisible(false);
}

void UsHwTestForm::UsHwConnectSignalAndSlots()
{
    // 添加信号和槽的连接关系
    // 连接开始按钮的信号和槽
    connect(ui->toolButton_Start, SIGNAL(clicked()), this, SLOT(UsHwStartTest()));
    // 连接暂停按钮的信号和槽
    connect(ui->toolButton_Pause, SIGNAL(clicked()), this, SLOT(UsHwPauseTest()));
    // 连接停止按钮的信号的槽
    connect(ui->toolButton_Stop, SIGNAL(clicked()), this, SLOT(UsHwStopTest()));
    // 连接加载配置按钮的信号和槽
    connect(ui->pushButton_LoadCfg, SIGNAL(clicked()), this, SLOT(UsHwLoadParams()));
    // 连接保存配置按钮的信号和槽
    connect(ui->pushButton_SaveCfg, SIGNAL(clicked()), this, SLOT(UsHwSaveParams()));
}

void UsHwTestForm::UsHwLoadParams(const char *pcCfgFilePath)
{
    // 遍历  m_vectorUsHwTestCases
    QVector<UH_TEST_CASE_S>::iterator       iteratorTestcase;
    bool        bChecked = false;

    UsHwLoadGlobalParams(pcCfgFilePath);

    for (iteratorTestcase = m_vectorUsHwTestCases.begin(); iteratorTestcase != m_vectorUsHwTestCases.end(); iteratorTestcase++)
    {
        iteratorTestcase->pwgtTestCase->UsHwInitParams(pcCfgFilePath, bChecked);
        if (bChecked)
        {
            iteratorTestcase->pitemTestCase->setCheckState(Qt::Checked);
        }
        else
        {
            iteratorTestcase->pitemTestCase->setCheckState(Qt::Unchecked);
        }
    }
}

void UsHwTestForm::UsHwSaveParams(const char *pcCfgFilePath)
{
    // 遍历  m_vectorUsHwTestCases
    QVector<UH_TEST_CASE_S>::iterator       iteratorTestcase;
    bool            bChecked = false;
    Qt::CheckState  checkState;

    UsHwSaveGlobalParams(pcCfgFilePath);

    for (iteratorTestcase = m_vectorUsHwTestCases.begin(); iteratorTestcase != m_vectorUsHwTestCases.end(); iteratorTestcase++)
    {
        checkState = iteratorTestcase->pitemTestCase->checkState();
        bChecked = (Qt::Checked == checkState)? true : false;

        iteratorTestcase->pwgtTestCase->UsHwSaveParams(pcCfgFilePath, bChecked);
    }

    // 判断是否需要自动运行，如果要求程序自动运行，则保存本次运行参数
    if (IsAutoRun())
    {
        UsHwSaveRuntimeCfgToFile();
    }
}

void UsHwTestForm::UsHwLoadGlobalParams(const char *pcCfgFilePath)
{
    // 加载全局参数
    Qt::CheckState  checkState;
    QString         strIniKey = "";
    QString         strIniVal = "";
    QSettings       configFile(pcCfgFilePath, QSettings::IniFormat);

    configFile.beginGroup(g_pcGlobalParamSection);

    strIniKey = "Check" + ui->checkBox_Gbl_TestCnt->text();
    strIniVal = configFile.value(strIniKey).toString();
    checkState = ("1" == strIniVal)? Qt::Checked : Qt::Unchecked;
    ui->checkBox_Gbl_TestCnt->setCheckState(checkState);
    m_mapRuntimeCfg.insert(strIniKey, strIniVal.toInt());

    strIniKey = ui->checkBox_Gbl_TestCnt->text();
    strIniVal = configFile.value(strIniKey).toString();
    ui->lineEdit_Gbl_TestCnt->setText(strIniVal);
    m_mapRuntimeCfg.insert(strIniKey, strIniVal.toInt());

    strIniKey = "Check" + ui->checkBox_Gbl_TestTime->text();
    strIniVal = configFile.value(strIniKey).toString();
    checkState = ("1" == strIniVal)? Qt::Checked : Qt::Unchecked;
    ui->checkBox_Gbl_TestTime->setCheckState(checkState);
    m_mapRuntimeCfg.insert(strIniKey, strIniVal.toInt());

    strIniKey = ui->checkBox_Gbl_TestTime->text();
    strIniVal = configFile.value(strIniKey).toString();
    ui->lineEdit_Gbl_TestTime->setText(strIniVal);
    m_mapRuntimeCfg.insert(strIniKey, (strIniVal.toULongLong() * 60 * 60));

    strIniKey = "Check" + ui->checkBox_ErrStop->text();
    strIniVal = configFile.value(strIniKey).toString();
    checkState = ("1" == strIniVal)? Qt::Checked : Qt::Unchecked;
    ui->checkBox_ErrStop->setCheckState(checkState);
    m_mapRuntimeCfg.insert(strIniKey, strIniVal.toInt());

    configFile.endGroup();
}

void UsHwTestForm::UsHwSaveGlobalParams(const char *pcCfgFilePath)
{
    // 保存全局参数
    Qt::CheckState  checkState;
    QString         strIniKey = "";
    QString         strIniVal = "";
    QSettings       configFile(pcCfgFilePath, QSettings::IniFormat);

    configFile.beginGroup(g_pcGlobalParamSection);

    strIniKey = ui->checkBox_Gbl_TestCnt->text();
    strIniVal = ui->lineEdit_Gbl_TestCnt->text();
    configFile.setValue(strIniKey, strIniVal);

    strIniKey = ui->checkBox_Gbl_TestTime->text();
    strIniVal = ui->lineEdit_Gbl_TestTime->text();
    configFile.setValue(strIniKey, strIniVal);

    strIniKey = "Check" + ui->checkBox_Gbl_TestCnt->text();
    checkState = ui->checkBox_Gbl_TestCnt->checkState();
    strIniVal = (Qt::Checked == checkState)? "1" : "0";
    configFile.setValue(strIniKey, strIniVal);

    strIniKey = "Check" + ui->checkBox_Gbl_TestTime->text();
    checkState = ui->checkBox_Gbl_TestTime->checkState();
    strIniVal = (Qt::Checked == checkState)? "1" : "0";
    configFile.setValue(strIniKey, strIniVal);

    strIniKey = "Check" + ui->checkBox_ErrStop->text();
    checkState = ui->checkBox_ErrStop->checkState();
    strIniVal = (Qt::Checked == checkState)? "1" : "0";
    configFile.setValue(strIniKey, strIniVal);

    configFile.endGroup();
}

QString UsHwTestForm::UsHwCalInterval(uint64_t uiSeconds)
{
    QString     strTemp = "";

    int         iDays = 0;
    int         iHours = 0;
    int         iMinutes = 0;
    int         iSeconds = 0;

    iDays = uiSeconds / (60 * 60 * 24);
    uiSeconds = uiSeconds % (60 * 60 * 24);

    iHours = uiSeconds / (60 * 60);
    uiSeconds = uiSeconds % (60 * 60);

    iMinutes = uiSeconds / 60;
    iSeconds = uiSeconds % 60;

    strTemp.sprintf("%02d:%02d:%02d:%02d", iDays, iHours, iMinutes, iSeconds);

    return strTemp;
}

void UsHwTestForm::UsHwGetRuntimeCfgFromFile()
{
    QSettings   settingRuntimeCfg(g_pcRuntimeCfgFilePath, QSettings::IniFormat);
    QFile       fileRuntimeCfg(g_pcRuntimeCfgFilePath);
    QString     strIniKey;
    QString     strIniVal;
    int         iIniVal;
    int         iIndex;
    int         iNum = 0;

    if (!fileRuntimeCfg.exists())
    {
        m_mapRuntimeCfg.insert(UH_CURRENT_TEST_CNT, 0);
        m_mapRuntimeCfg.insert(UH_SINGLE_TEST_TIME, 0);

        return;
    }

    settingRuntimeCfg.beginGroup(g_pcRuntimeParamSection);

    iNum = sizeof(g_apcRuntimeCfgKey) / sizeof(char*);
    for (iIndex = 0; iIndex < iNum; iIndex++)
    {
        strIniKey = g_apcRuntimeCfgKey[iIndex];
        strIniVal = settingRuntimeCfg.value(strIniKey).toString();
        iIniVal = strIniVal.toInt();

        m_mapRuntimeCfg.insert(strIniKey, iIniVal);
    }

    settingRuntimeCfg.endGroup();

    QString     strCurrCnt = "";

    strCurrCnt.sprintf("%d", (m_mapRuntimeCfg[UH_CURRENT_TEST_CNT] + 1));
    ui->label_CurrCntVal->setText(strCurrCnt);
    ui->label_CurrCntVal->setVisible(true);
    ui->label_CurrCntTitle->setVisible(true);
}

void UsHwTestForm::UsHwSaveRuntimeCfgToFile()
{
    QSettings   settingRuntimeCfg(g_pcRuntimeCfgFilePath, QSettings::IniFormat);
    QFile       fileRuntimeCfg(g_pcRuntimeCfgFilePath);
    QString     strIniKey;
    QString     strIniVal;
    int         iIndex;
    int         iNum = 0;

    if (!fileRuntimeCfg.exists())
    {
        m_mapRuntimeCfg.insert(UH_CURRENT_TEST_CNT, 0);

        QDateTime   dateTimeEnd = QDateTime::currentDateTime();
        m_mapRuntimeCfg.insert(UH_SINGLE_TEST_TIME, (dateTimeEnd.toTime_t() - m_dateTimeStart.toTime_t()));
    }

    m_mapRuntimeCfg[UH_CURRENT_TEST_CNT] += 1;

    settingRuntimeCfg.beginGroup(g_pcRuntimeParamSection);

    iNum = sizeof(g_apcRuntimeCfgKey) / sizeof(char*);
    for (iIndex = 0; iIndex < iNum; iIndex++)
    {
        strIniKey = g_apcRuntimeCfgKey[iIndex];
        strIniVal = QString::number(m_mapRuntimeCfg[strIniKey], 10);
        settingRuntimeCfg.setValue(strIniKey, strIniVal);
    }

    settingRuntimeCfg.endGroup();
}

bool UsHwTestForm::IsAutoRun()
{
    // Windows平台下，通过判断注册表启动项是否有本程序
    QSettings   settingRegedit(g_pcHKLMRunSection, QSettings::NativeFormat);
    QString     strAppPath = "";

    strAppPath = settingRegedit.value(g_pcHKLMRunKey, "").toString();
    return ("" != strAppPath)? true : false;
}

void UsHwTestForm::UsHwAutoStartTest()
{
    // 保存日志到文件
    QDir        dirLog;
    QString     strLogPath;

    strLogPath = QCoreApplication::applicationDirPath() + g_strLogDir;
    dirLog.setPath(strLogPath);

    if (!dirLog.exists())
    {
        dirLog.mkdir(strLogPath);
    }

    QString     strDefaultLog = strLogPath + "\\" + g_strDefaultLogFile;
    CUltraSmartLog::Instance()->StartLogToFile(strDefaultLog.toStdString().data());

    // 加载运行时参数
    UsHwGetRuntimeCfgFromFile();

    // 开始启动测试
    Logout("Auto Test Start, test time %d", (m_mapRuntimeCfg[UH_CURRENT_TEST_CNT] + 1));

    ui->toolButton_Start->click();
}

uint UsHwTestForm::UsHwClearEnv()
{
    if (IsAutoRun())
    {
        QSettings   settingRegedit(g_pcHKLMRunSection, QSettings::NativeFormat);

        settingRegedit.remove(g_pcHKLMRunKey);
    }

    QFile   fileRunCfg(g_pcRuntimeCfgFilePath);

    if (fileRunCfg.exists())
    {
        fileRunCfg.remove();
    }

    //  关闭日志
    CUltraSmartLog::Instance()->StopLogToFile();
}

void UsHwTestForm::UsHwPowerDown()
{
    if (IsAutoRun())
    {
        //ShutDownOS(TRUE);
    }
}

void UsHwTestForm::UsHwLoadParams()
{
    QString     strPath = "";

    strPath = QFileDialog::getOpenFileName(this, "Please choose ini file", ".", "ini files(*.*)");
    if ("" != strPath)
    {
        UsHwLoadParams(strPath.toStdString().data());
    }
}

void UsHwTestForm::UsHwSaveParams()
{
    QString     strPath = "";

    strPath = QFileDialog::getSaveFileName(this, "Please choose save path", "./DefaultTestCfg.ini", "ini files(*.*)");
    if ("" != strPath)
    {
        UsHwSaveParams(strPath.toStdString().data());
    }
}

void UsHwTestForm::UsHwStartTest()
{
    // 遍历  m_vectorUsHwTestCases
    QVector<UH_TEST_CASE_S>::iterator       iteratorTestcase;
    QStandardItem       *pitemTestcase;
    QStandardItem       *pitemTestcaseResult;

    m_pTimerDetectTest = new QTimer();
    m_pTimerDetectTest->setInterval(1000);
    connect(m_pTimerDetectTest, SIGNAL(timeout()), this, SLOT(UsHwDetectTestTimer()));
    m_pTimerDetectTest->start();

    m_dateTimeStart = QDateTime::currentDateTime();

    for (iteratorTestcase = m_vectorUsHwTestCases.begin(); iteratorTestcase != m_vectorUsHwTestCases.end(); iteratorTestcase++)
    {
        // 判断当前item是否被勾选，如果勾选则调用其执行函数，并返回测试结果
        pitemTestcase = iteratorTestcase->pitemTestCase;
        pitemTestcaseResult = iteratorTestcase->pitemTestResult;

        if (Qt::Checked == pitemTestcase->checkState())
        {
            QThread                 *pThreadTest = new QThread();
            CUsHwTestcaseThreadObj  *pTestcaseThreadObj = new CUsHwTestcaseThreadObj();

            pTestcaseThreadObj->m_pwgtTestcase = iteratorTestcase->pwgtTestCase;
            pTestcaseThreadObj->m_pitemTestcaseResult = iteratorTestcase->pitemTestResult;
            pTestcaseThreadObj->m_pitemTestcaseResult->setText(tr(UH_TEST_RESULT_TODO));

            // 将每个testcase加到线程中
            pTestcaseThreadObj->moveToThread(pThreadTest);
            connect(pThreadTest, SIGNAL(started()), pTestcaseThreadObj, SLOT(UsHwStartTest()));
            // 连接signal和slot，根据返回的测试结果，设置item的结果Pass还是Fail
            connect(pTestcaseThreadObj, SIGNAL(UsHwSetTestcaseResultSignal(QStandardItem*, uint)),
                                  this, SLOT(UsHwSetTestcaseResultSlot(QStandardItem*, uint)));
            pThreadTest->start();

            m_uiTestcaseCnt++;
        }
    }
}

void UsHwTestForm::UsHwPauseTest()
{

}

void UsHwTestForm::UsHwStopTest()
{
    // 清除相关运行配置
    UsHwClearEnv();
}

void UsHwTestForm::UsHwDetectTestTimer()
{
    QDateTime   dateTimeEnd = QDateTime::currentDateTime();
    QString     strTemp = "";
    uint64_t    uiTotalSeconds;
    uint64_t    uiSingleSeconds;
    int64_t     iRemainSeconds;

    // 如果全局参数勾选了测试时间，则测试需要的总时间直接使用该全局参数
    // 如果全局参数勾选了测试次数，则测试需要的总时间用测试测试*每次测试需要的时间来估算
    if ((1 == m_mapRuntimeCfg[UH_CHECK_TOTAL_TEST_TIME])
            && (0 != m_mapRuntimeCfg[UH_TOTAL_TEST_TIME]))
    {
        uiTotalSeconds = m_mapRuntimeCfg[UH_TOTAL_TEST_TIME];
    }
    else
    {
        uiTotalSeconds = m_mapRuntimeCfg[UH_TOTAL_TEST_COUNT] * m_mapRuntimeCfg[UH_SINGLE_TEST_TIME];
    }

    if (0 != uiTotalSeconds)
    {
        iRemainSeconds = uiTotalSeconds - (dateTimeEnd.toTime_t() - m_dateTimeStart.toTime_t());
        strTemp = UsHwCalInterval(iRemainSeconds);
        ui->lcdNumber_TotalLeft->display(strTemp);
    }

    // 本次测试剩余时间
    uiSingleSeconds = m_mapRuntimeCfg[UH_SINGLE_TEST_TIME];
    if (0 != uiSingleSeconds)
    {
        iRemainSeconds = uiSingleSeconds - (dateTimeEnd.toTime_t() - m_dateTimeStart.toTime_t());
        strTemp = UsHwCalInterval(iRemainSeconds);
        ui->lcdNumber_CurrLeft->display(strTemp);
    }
}

void UsHwTestForm::UsHwSetTestcaseResultSlot(QStandardItem *pitemResult, uint uiRetVal)
{
    QString         strResult = (0 == uiRetVal)? "Pass" : "Fail";

    switch(uiRetVal)
    {
        case UH_NO_ERROR:
            strResult = UH_TEST_RESULT_PASS;
            break;

        case UH_PAUSED:
            strResult = UH_TEST_RESULT_TODO;
            break;

        default:
            strResult = UH_TEST_RESULT_FAIL;
            break;
    }

    pitemResult->setText(strResult);

    m_uiRecvResultCnt++;
    // 检查是否所有的testcase均已经返回结果
    if (m_uiRecvResultCnt == m_uiTestcaseCnt)
    {
        Logout("all testcases have finished");
        m_pTimerDetectTest->stop();
        UsHwSaveParams(g_pcParamsCfgFileDefaultPath);
        
        ui->lcdNumber_TotalLeft->display("0");
        ui->lcdNumber_CurrLeft->display("0");        
    }

    // 如果出错，需要设置信号灯
}

void UsHwTestForm::on_treeView_HwTestItems_clicked(const QModelIndex &index)
{
    QStandardItemModel      *pitemModeTreeView = static_cast<QStandardItemModel*>(ui->treeView_HwTestItems->model());
    QStandardItem           *pitemCurrentTestcase = pitemModeTreeView->itemFromIndex(index);

    // 遍历  m_vectorUsHwTestCases
    QVector<UH_TEST_CASE_S>::iterator       iteratorTestcase;
    QStandardItem       *pitemTestcase;

    for (iteratorTestcase = m_vectorUsHwTestCases.begin(); iteratorTestcase != m_vectorUsHwTestCases.end(); iteratorTestcase++)
    {
        // 查找当前的testcase item
        pitemTestcase = iteratorTestcase->pitemTestCase;
        if (pitemTestcase == pitemCurrentTestcase)
        {
            m_pStackedWgtParams->setCurrentWidget(iteratorTestcase->pwgtTestCase);
        }
    }
}

void UsHwTestForm::treeItemChanged(QStandardItem *item)
{
    if (NULL == item)
    {
        return;
    }

    if (item->isCheckable())
    {
        // 如果条目是复选框
        Qt::CheckState  state = item->checkState();
        if (item->isTristate())
        {
            if (state != Qt::PartiallyChecked)
            {
                treeItem_CheckAllChild(item, (state == Qt::Checked)? true : false);
            }
        }
        else
        {
            treeItem_CheckChildChanged(item);
        }
    }
}

void UsHwTestForm::treeItem_CheckAllChild(QStandardItem *item, bool bChecked)
{
    if (NULL == item)
    {
        return;
    }

    int iRowCount = item->rowCount();
    for (int iIndex = 0; iIndex < iRowCount; iIndex++)
    {
        QStandardItem       *itemsChild = item->child(iIndex);
        treeItem_CheckAllChild_Recursion(itemsChild, bChecked);
    }

    if (item->isCheckable())
    {
        item->setCheckState(bChecked? Qt::Checked : Qt::Unchecked);
    }
}

Qt::CheckState UsHwTestForm::CheckSibling(QStandardItem *item)
{
    QStandardItem       *itemParent = item->parent();

    if (NULL == itemParent)
    {
        return item->checkState();
    }

    int brotherCount = itemParent->rowCount();
    int checkedCount = 0;
    int unCheckedCount = 0;
    Qt::CheckState      state;

    for (int iIndex = 0; iIndex < brotherCount; iIndex++)
    {
        QStandardItem   *siblingItem = itemParent->child(iIndex);
        state = siblingItem->checkState();

        if (Qt::PartiallyChecked == state)
        {
            return Qt::PartiallyChecked;
        }
        else if (Qt::Unchecked == state)
        {
            ++unCheckedCount;
        }
        else
        {
            ++checkedCount;
        }

        if ((checkedCount > 0) && (unCheckedCount > 0))
        {
            return Qt::PartiallyChecked;
        }
    }

    if (unCheckedCount > 0)
    {
        return Qt::Unchecked;
    }

    return Qt::Checked;
}

void UsHwTestForm::treeItem_CheckAllChild_Recursion(QStandardItem *item, bool bChecked)
{
    if (NULL == item)
    {
        return;
    }

    int iRowCount = item->rowCount();
    for (int iIndex = 0; iIndex < iRowCount; iIndex++)
    {
        QStandardItem   *itemsChild = item->child(iIndex);
        treeItem_CheckAllChild_Recursion(itemsChild, bChecked);
    }

    if (item->isCheckable())
    {
        item->setCheckState(bChecked? Qt::Checked : Qt::Unchecked);
    }
}

void UsHwTestForm::treeItem_CheckChildChanged(QStandardItem *item)
{
    if (NULL == item)
    {
        return ;
    }

    Qt::CheckState      siblingState = CheckSibling(item);
    QStandardItem       *itemParent = item->parent();

    if (NULL == itemParent)
    {
        return;
    }

    if (Qt::PartiallyChecked == siblingState)
    {
        if (itemParent->isCheckable() && itemParent->isTristate())
        {
            itemParent->setCheckState(Qt::PartiallyChecked);
        }
    }
    else if (Qt::Checked == siblingState)
    {
        if (itemParent->isCheckable())
        {
            itemParent->setCheckState(Qt::Checked);
        }
    }
    else
    {
        if (itemParent->isCheckable())
        {
            itemParent->setCheckState(Qt::Unchecked);
        }
    }

    treeItem_CheckChildChanged(itemParent);
}

