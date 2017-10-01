#include "TestCaseWiFiDetect.h"

TestCaseWiFiDetect::TestCaseWiFiDetect()
{
    CreateUi();
}

TestCaseWiFiDetect::~TestCaseWiFiDetect()
{

}

void TestCaseWiFiDetect::CreateUi()
{
    //  ����д�����������ļ��е�section�ֶ�����
    m_strParamSection = "WiFiDetect";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"ExpectedWiFiModel",    NULL,  UH_LABEL,   0, 0, 1, 1},
        {"ExpectedWiFiModel", 	  NULL,  UH_EDIT,    0, 1, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseWiFiDetect::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}
