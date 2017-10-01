#include "TestCaseAutoSleepWakeTest.h"

#include <QCoreApplication>


//  ����д�����������ļ��е�section��������

TestCaseAutoSleepWake::TestCaseAutoSleepWake()
{
    CreateUi();
}

TestCaseAutoSleepWake::~TestCaseAutoSleepWake()
{

}

void TestCaseAutoSleepWake::CreateUi()
{
    //  ����д�����������ļ��е�section�ֶ�����
    m_strParamSection = "AutoSleepWake";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"SleepDelay", NULL,  UH_LABEL,   0, 0, 1, 1},
        {"SleepDelay", NULL,  UH_EDIT,    0, 1, 1, 1},
        {"s",          NULL,  UH_LABEL,   0, 2, 1, 1},

        {"WakeDelay",  NULL,  UH_LABEL,   1, 0, 1, 1},
        {"WakeDelay",  NULL,  UH_EDIT,    1, 1, 1, 1},
        {"s",          NULL,  UH_LABEL,   1, 2, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseAutoSleepWake::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    // ���ÿ���������Ϊ����ִ�г���
    QSettings   settingRegedit(g_pcHKLMRunSection, QSettings::NativeFormat);
    QString     strAppPath = QCoreApplication::applicationFilePath();

    settingRegedit.setValue(g_pcHKLMRunKey, strAppPath);

    // �����Զ��ػ�ʱ��Ϳ���ʱ��
    qDebug("Set power on delay time : %d ", ((QLineEdit*)m_mapCtrl["ShutDownDelay"])->text().toInt());

    uint    nDelayPowerDownDelay = ((QLineEdit*)m_mapCtrl["ShutDownDelay"])->text().toUInt();

    QThread::sleep(nDelayPowerDownDelay);

    return 0;
}
