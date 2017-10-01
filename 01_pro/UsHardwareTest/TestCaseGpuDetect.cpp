#include "TestCaseGpuDetect.h"

TestCaseGpuDetect::TestCaseGpuDetect()
{
    CreateUi();
}

TestCaseGpuDetect::~TestCaseGpuDetect()
{

}

void TestCaseGpuDetect::CreateUi()
{
    //  ����д�����������ļ��е�section�ֶ�����
    m_strParamSection = "GpuDetect";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"ExpectedGpuModel",    NULL,  UH_LABEL,   0, 0, 1, 1},
        {"ExpectedGpuModel", 	  NULL,  UH_EDIT,    0, 1, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseGpuDetect::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}
