#include "TestCaseUsbTest.h"
#include <QFileDialog>

TestCaseUsbPress::TestCaseUsbPress()
{
    CreateUi();
}

TestCaseUsbPress::~TestCaseUsbPress()
{

}

void TestCaseUsbPress::CreateUi()
{
    //  定义写到参数配置文件中的section字段名称
    m_strParamSection = "UsbTest";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"UsbDiskCount",  NULL,  UH_LABEL,   0, 0, 1, 1},
        {"UsbDiskCount",  NULL,  UH_EDIT,    0, 1, 1, 1},

        {"UsbDiskPath0",  NULL,  UH_LABEL,   1, 0, 1, 1},
        {"UsbDiskPath0",  NULL,  UH_EDIT,    1, 1, 1, 1},
        {"BrowsePath0",   NULL,  UH_DLG_BUTTON,  1, 2, 1, 1},

        {"UsbDiskPath1",  NULL,  UH_LABEL,   2, 0, 1, 1},
        {"UsbDiskPath1",  NULL,  UH_EDIT,    2, 1, 1, 1},
        {"BrowsePath1",   NULL,  UH_DLG_BUTTON,  2, 2, 1, 1},

        {"UsbDiskPath2",  NULL,  UH_LABEL,   3, 0, 1, 1},
        {"UsbDiskPath2",  NULL,  UH_EDIT,    3, 1, 1, 1},
        {"BrowsePath2",   NULL,  UH_DLG_BUTTON,  3, 2, 1, 1},

        {"UsbDiskPath3",  NULL,  UH_LABEL,   4, 0, 1, 1},
        {"UsbDiskPath3",  NULL,  UH_EDIT,    4, 1, 1, 1},
        {"BrowsePath3",   NULL,  UH_DLG_BUTTON,  4, 2, 1, 1},

        {"TestCount",     NULL,  UH_CHECKBOX,5, 0, 1, 1},
        {"TestCount",     NULL,  UH_EDIT,    5, 1, 1, 1},

        {"TestTime",      NULL,  UH_CHECKBOX,6, 0, 1, 1},
        {"TestTime",      NULL,  UH_EDIT,    6, 1, 1, 1},
        {"minutes",       NULL,  UH_LABEL,   6, 2, 1, 1},
        {"ErrStop",       NULL,  UH_CHECKBOX,7, 0, 1, 1},
    };

    uint uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);

    UsHwCreateUi(astTestcasePageCtrls, uiNum);

    uint            nIndex = 0;
    QString         strBtnCaption  = "";
    QString         strEditCaption = "";
    QPushButton*    pushBrowse;

    for (nIndex < 0; nIndex < 4; nIndex++)
    {
        strBtnCaption.sprintf("BrowsePath%d", nIndex);
        strEditCaption.sprintf("UsbDiskPath%d", nIndex);

        pushBrowse = (QPushButton*)m_mapCtrl[strBtnCaption];
        connect(pushBrowse, SIGNAL(clicked()), this, SLOT(UsHwBrowsePath()));
        m_mapBrowsePath[pushBrowse] = (QLineEdit*)m_mapCtrl[strEditCaption];
    }
}

uint TestCaseUsbPress::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());

    return 0;
}

void TestCaseUsbPress::UsHwBrowsePath()
{
    QPushButton     *pbtnClicked = dynamic_cast<QPushButton*>(sender());
    QString         strPath = "";

    strPath = QFileDialog::getSaveFileName(this, tr("chose test file path"), ".\\UsbPressTestFile", "bin files(*.bin)");
    if ("" == strPath)
    {
        return;
    }

    m_mapBrowsePath[pbtnClicked]->setText(strPath);
}
