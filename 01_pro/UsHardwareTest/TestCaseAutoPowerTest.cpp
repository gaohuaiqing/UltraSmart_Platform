#include "TestCaseAutoPowerTest.h"

#include <QCoreApplication>


//  ����д�����������ļ��е�section��������

TestCaseAutoPower::TestCaseAutoPower()
{
    CreateUi();
}

TestCaseAutoPower::~TestCaseAutoPower()
{

}

void TestCaseAutoPower::CreateUi()
{
    //  ����д�����������ļ��е�section�ֶ�����
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
