#include "TestCaseProbeIdTest.h"
#include <QFileDialog>

TestCaseProbeIdPress::TestCaseProbeIdPress()
{
    CreateUi();
}

TestCaseProbeIdPress::~TestCaseProbeIdPress()
{

}

void TestCaseProbeIdPress::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "ProbeIdTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"ProbeBase",	NULL,  UH_LABEL,   0, 0, 1, 1},
        {"ProbeId",     NULL,  UH_LABEL,   0, 2, 1, 1},
        {"PresentSt",	NULL,  UH_LABEL,   0, 3, 1, 1},
        {"TestResult",	NULL,  UH_LABEL,   0, 4, 1, 1},

        {"ProbeA",      NULL,  UH_LABEL,   1, 0, 1, 1},
        {"0x",          NULL,  UH_LABEL,   1, 1, 1, 1},
        {"ProbeA",      NULL,  UH_EDIT,    1, 2, 1, 1},
		
        {"ProbeB",	NULL,  UH_LABEL,   2, 0, 1, 1},
        {"0x",      NULL,  UH_LABEL,   2, 1, 1, 1},
        {"ProbeB", 	NULL,  UH_EDIT,    2, 2, 1, 1}
        ,
        {"ProbeC",	NULL,  UH_LABEL,   3, 0, 1, 1},
        {"0x",      NULL,  UH_LABEL,   3, 1, 1, 1},
        {"ProbeC", 	NULL,  UH_EDIT,    3, 2, 1, 1},

        {"ProbeD",	NULL,  UH_LABEL,   4, 0, 1, 1},
        {"0x",      NULL,  UH_LABEL,   4, 1, 1, 1},
        {"ProbeD", 	NULL,  UH_EDIT,    4, 2, 1, 1},

        {"ProbeE",	NULL,  UH_LABEL,   5, 0, 1, 1},
        {"0x",      NULL,  UH_LABEL,   5, 1, 1, 1},
        {"ProbeE", 	NULL,  UH_EDIT,    5, 2, 1, 1},
        
        {"ProbePen", NULL,  UH_LABEL,   6, 0, 1, 1},
        {"0x",       NULL,  UH_LABEL,   6, 1, 1, 1},
        {"ProbePen", NULL,  UH_EDIT,    6, 2, 1, 1},
		
        {"TestCount", 	NULL,  UH_CHECKBOX,7, 0, 1, 1},
        {"TestCount", 	NULL,  UH_EDIT,    7, 2, 1, 1},
	
        {"TestTime",  	NULL,  UH_CHECKBOX,8, 0, 1, 1},
        {"TestTime",  	NULL,  UH_EDIT,    8, 2, 1, 1},
        {"minutes",   	NULL,  UH_LABEL,   8, 3, 1, 1},
        {"ErrStop",   	NULL,  UH_CHECKBOX,9, 0, 1, 1},
    };	

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);
}

uint TestCaseProbeIdPress::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}

