#include "TestCaseDisplayTest.h"

TestCaseDisplayTest::TestCaseDisplayTest()
{
    CreateUi();
}

TestCaseDisplayTest::~TestCaseDisplayTest()
{

}

void TestCaseDisplayTest::CreateUi()
{
    //  ����д�����������ļ��е�section�ֶ�����
    m_strParamSection = "DisplayTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"Resolution",    NULL,  UH_LABEL,   0, 0, 1, 1},
        {"Resolution", 	  NULL,  UH_EDIT,    0, 1, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseDisplayTest::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}
