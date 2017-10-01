#include "TestCaseCDRomDetect.h"

TestCaseCDRomDetect::TestCaseCDRomDetect()
{
    CreateUi();
}

TestCaseCDRomDetect::~TestCaseCDRomDetect()
{

}

void TestCaseCDRomDetect::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "CDRomDetect";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"ExpectedCDRomModel",    NULL,  UH_LABEL,   0, 0, 1, 1},
        {"ExpectedCDRomModel", 	  NULL,  UH_EDIT,    0, 1, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseCDRomDetect::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}
