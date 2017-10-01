#include "TestCaseFpgaDdrRwTest.h"

TestCaseFpgaDdrRw::TestCaseFpgaDdrRw()
{
    CreateUi();
}

TestCaseFpgaDdrRw::~TestCaseFpgaDdrRw()
{

}

void TestCaseFpgaDdrRw::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "FpgaDDRRwTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"TestCout",      NULL,  UH_LABEL,   0, 0, 1, 1},
        {"TestCout",      NULL,  UH_EDIT,    0, 1, 1, 1},
		
        {"ErrStop",       NULL,  UH_CHECKBOX,1, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseFpgaDdrRw::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());



    return 0;
}
