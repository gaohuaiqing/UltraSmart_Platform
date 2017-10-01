#include "TestCaseHDDTest.h"
#include <QFileDialog>

TestCaseHDDPress::TestCaseHDDPress()
{
    CreateUi();
}

TestCaseHDDPress::~TestCaseHDDPress()
{

}

void TestCaseHDDPress::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "SATATest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"SataDiskPath",  NULL,  UH_LABEL,   0, 0, 1, 1},
        {"SataDiskPath",  NULL,  UH_EDIT,    0, 1, 1, 1},
        {"BrowsePath",    NULL,  UH_DLG_BUTTON,  0, 2, 1, 1},

        {"TestCount",     NULL,  UH_CHECKBOX,1, 0, 1, 1},
        {"TestCount",     NULL,  UH_EDIT,    1, 1, 1, 1},

        {"TestTime",      NULL,  UH_CHECKBOX,2, 0, 1, 1},
        {"TestTime",      NULL,  UH_EDIT,    2, 1, 1, 1},
        {"minutes",       NULL,  UH_LABEL,   2, 2, 1, 1},
		
        {"ErrStop",       NULL,  UH_CHECKBOX,3, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);

    QPushButton*    pushBrowse = (QPushButton*)m_mapCtrl["BrowsePath"];
    connect(pushBrowse, SIGNAL(clicked()), this, SLOT(UsHwBrowsePath()));
}

uint TestCaseHDDPress::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}

void TestCaseHDDPress::UsHwBrowsePath()
{
    QString         strPath = "";

    strPath = QFileDialog::getSaveFileName(this, tr("chose test file path"), ".\\SataPressTestFile", "bin files(*.bin)");
    if ("" == strPath)
    {
        return;
    }

    ((QLineEdit*)m_mapCtrl["SataDiskPath"])->setText(strPath);
}
