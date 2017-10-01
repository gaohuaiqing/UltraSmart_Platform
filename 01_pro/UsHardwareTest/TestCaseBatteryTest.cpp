#include "TestCaseBatteryTest.h"


TestCaseBatteryI2C::TestCaseBatteryI2C()
{
    CreateUi();
}

TestCaseBatteryI2C::~TestCaseBatteryI2C()
{

}

void TestCaseBatteryI2C::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "BatteryManagementI2CTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"TestCount",     NULL,  UH_CHECKBOX,0, 0, 1, 1},
        {"TestCount",     NULL,  UH_EDIT,    0, 1, 1, 1},

        {"TestTime",      NULL,  UH_CHECKBOX,1, 0, 1, 1},
        {"TestTime",      NULL,  UH_EDIT,    1, 1, 1, 1},
        {"minutes",       NULL,  UH_LABEL,   1, 2, 1, 1},
        {"ErrStop",       NULL,  UH_CHECKBOX,2, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseBatteryI2C::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());



    return 0;
}
