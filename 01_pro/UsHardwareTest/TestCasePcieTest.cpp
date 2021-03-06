#include "TestCasePcieTest.h"

TestCasePciePress::TestCasePciePress()
{
    CreateUi();
}

TestCasePciePress::~TestCasePciePress()
{

}

void TestCasePciePress::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "PCIeTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"DspFpgaVer",    NULL,  UH_LABEL,   0, 0, 1, 1},
        {"0x",            NULL,  UH_LABEL,   0, 1, 1, 1},
        {"DspFpgaVer", 	  NULL,  UH_EDIT,    0, 2, 1, 1},

		
        {"TestCount",     NULL,  UH_CHECKBOX,1, 0, 1, 1},
        {"TestCount",     NULL,  UH_EDIT,    1, 2, 1, 1},

        {"TestTime",      NULL,  UH_CHECKBOX,2, 0, 1, 1},
        {"TestTime",      NULL,  UH_EDIT,    2, 2, 1, 1},
        {"minutes",       NULL,  UH_LABEL,   2, 3, 1, 1},
        {"ErrStop",       NULL,  UH_CHECKBOX,3, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCasePciePress::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());



    return 0;
}
