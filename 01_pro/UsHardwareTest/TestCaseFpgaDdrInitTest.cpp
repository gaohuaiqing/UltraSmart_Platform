#include "TestCaseFpgaDdrInitTest.h"

TestCaseFpgaDdrInitPress::TestCaseFpgaDdrInitPress()
{
    CreateUi();
}

TestCaseFpgaDdrInitPress::~TestCaseFpgaDdrInitPress()
{

}

void TestCaseFpgaDdrInitPress::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "FpgaDDRInitTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"InitInterval",  NULL,  UH_LABEL,	 0, 0, 1, 1},
        {"InitInterval",  NULL,  UH_EDIT,    0, 1, 1, 1},
        {"s",       	  NULL,  UH_LABEL,   0, 2, 1, 1},

        {"TestCout",      NULL,  UH_LABEL,   1, 0, 1, 1},
        {"TestCout",      NULL,  UH_EDIT,    1, 1, 1, 1},
		
        {"ErrStop",       NULL,  UH_CHECKBOX,2, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseFpgaDdrInitPress::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());



    return 0;
}
