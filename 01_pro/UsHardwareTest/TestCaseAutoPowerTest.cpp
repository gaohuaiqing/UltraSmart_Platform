#include "TestCaseAutoPowerTest.h"

#include <QCoreApplication>


//  定义写到参数配置文件中的section名和组名

TestCaseAutoPower::TestCaseAutoPower()
{
    CreateUi();
}

TestCaseAutoPower::~TestCaseAutoPower()
{

}

void TestCaseAutoPower::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "AutoPowerOnOff";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"ShutDownDelay", NULL,  UH_LABEL,   0, 0, 1, 1},
        {"ShutDownDelay", NULL,  UH_EDIT,    0, 1, 1, 1},
        {"s",             NULL,  UH_LABEL,   0, 2, 1, 1},

        {"PowerOnDelay",  NULL,  UH_LABEL,   1, 0, 1, 1},
        {"PowerOnDelay",  NULL,  UH_EDIT,    1, 1, 1, 1},
        {"s",             NULL,  UH_LABEL,   1, 2, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseAutoPower::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    // 设置开机启动项为本可执行程序
    QSettings   settingRegedit(g_pcHKLMRunSection, QSettings::NativeFormat);
    QString     strAppPath = QCoreApplication::applicationFilePath();

    settingRegedit.setValue(g_pcHKLMRunKey, strAppPath);

    // 设置自动关机时间和开机时间
    qDebug("Set power on delay time : %d ", ((QLineEdit*)m_mapCtrl["ShutDownDelay"])->text().toInt());

    uint    nDelayPowerDownDelay = ((QLineEdit*)m_mapCtrl["ShutDownDelay"])->text().toUInt();

    QThread::sleep(nDelayPowerDownDelay);

    return 0;
}
