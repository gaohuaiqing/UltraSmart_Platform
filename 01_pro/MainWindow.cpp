#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QFileDialog>

#include "UsHardwareTest/TestCaseAutoPowerTest.h"
#include "UltraSmartLog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 日志初始化
    UsHwLogInit();

    UsHwCreateCustomCtrl();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UsHwLogInit()
{
    m_pclDockWgt = new QDockWidget("UltraSmart Log Win", this);

    m_pclDockWgtEdit = new CDockWidgetTextEdit;
    m_pclDockWgtEdit->setReadOnly(true);

    m_pclDockWgt->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_pclDockWgt->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_pclDockWgt->setWidget(m_pclDockWgtEdit);

    addDockWidget(Qt::BottomDockWidgetArea, m_pclDockWgt);

    // 绑定记录日志操作的signal和slot
    connect((QObject*)(CUltraSmartLog::Instance()), SIGNAL(UsHwLogoutSignal(QString)), this, SLOT(UsHwLogoutSlot(QString)));
    connect((QObject*)(CUltraSmartLog::Instance()), SIGNAL(UsHwClearLogSignal()), this, SLOT(UsHwCleanLogSlot()));
}

void MainWindow::UsHwCreateCustomCtrl()
{
    m_FormHwTest = new UsHwTestForm(this);

    setCentralWidget(m_FormHwTest);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_FormHwTest->UsHwStopTest();
}

void MainWindow::UsHwLogoutSlot(QString strLog)
{
    m_pclDockWgtEdit->append(strLog);
}

void MainWindow::UsHwCleanLogSlot()
{
    m_pclDockWgtEdit->clear();
}

void MainWindow::on_action_LogToFile_triggered()
{
    static  bool    s_bEnableLogToFile = false;
    QString     strPath = "";
    QIcon       iconLogOn(":/image/Icons/LogOutOn.png");
    QIcon       iconLogOff(":/image/Icons/LogOutOff.png");

    if (s_bEnableLogToFile)
    {
        CUltraSmartLog::Instance()->StopLogToFile();
        ui->action_LogToFile->setIcon(iconLogOn);
        ui->action_LogToFile->setText(tr("Save log to file"));
        s_bEnableLogToFile = false;
    }
    else
    {
        strPath = QFileDialog::getSaveFileName(this, tr("save log file"), ".", "txt files(*.txt)");
        if ("" == strPath)
        {
            return;
        }

        CUltraSmartLog::Instance()->StartLogToFile(strPath.toStdString().data());
        ui->action_LogToFile->setIcon(iconLogOff);
        ui->action_LogToFile->setText(tr("Stop save log"));
        s_bEnableLogToFile = true;
    }
}

void MainWindow::on_action_LogWindow_triggered()
{
    static  bool    s_LogWinShow = true;
    QIcon   iconWinShow(":/image/Icons/ShowLog.png");
    QIcon   iconWinHide(":/image/Icons/HideLog.png");


    if (s_LogWinShow)
    {
        //  隐藏日志窗口(即DockWidget)
        m_pclDockWgt->hide();
        ui->action_LogWindow->setIcon(iconWinShow);
        ui->action_LogWindow->setText(tr("Show Log Window"));
        ui->action_LogWindow->setToolTip(tr("Show Log Window"));
        s_LogWinShow = false;
    }
    else
    {
        m_pclDockWgt->show();
        ui->action_LogWindow->setIcon(iconWinHide);
        ui->action_LogWindow->setText(tr("Hide Log Window"));
        ui->action_LogWindow->setToolTip(tr("Hide Log Window"));
        s_LogWinShow = true;
    }
}

void MainWindow::on_action_ClearLog_triggered()
{
    UsHwCleanLogSlot();
}
