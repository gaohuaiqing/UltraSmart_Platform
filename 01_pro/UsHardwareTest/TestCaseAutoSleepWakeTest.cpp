#include "TestCaseAutoSleepWakeTest.h"

#include <QCoreApplication>


//  ����д�����������ļ��е�section��������

TestCaseAutoSleepWake::TestCaseAutoSleepWake()
{
    CreateUi();
}

TestCaseAutoSleepWake::~TestCaseAutoSleepWake()
{

}

void TestCaseAutoSleepWake::CreateUi()
{
    uint        uiIndex = 0;
    uint        uiNum = 0;
    UH_CTRL_TYPE_E      enCtrlType;
    QWidget             *pWidgetTemp = NULL;

    QString             strCtrlCaption = "";

    // �½�դ�񲼾ֹ�����
    QGridLayout *pGrdLytParams = new QGridLayout(this);

    //  ����д�����������ļ��е�section�ֶ�����
    m_strParamSection = "AutoSleepWake";

    UH_TEST_CASE_PAGE_CTRL_S    astTestcasePageCtrls[] =
    {
        {"SleepDelay", NULL,  UH_LABEL,   0, 0, 1, 1},
        {"SleepDelay", NULL,  UH_EDIT,    0, 1, 1, 1},
        {"s",          NULL,  UH_LABEL,   0, 2, 1, 1},

        {"WakeDelay",  NULL,  UH_LABEL,   1, 0, 1, 1},
        {"WakeDelay",  NULL,  UH_EDIT,    1, 1, 1, 1},
        {"s",          NULL,  UH_LABEL,   1, 2, 1, 1},
    };

    uiNum = sizeof(astTestcasePageCtrls) / sizeof(UH_TEST_CASE_PAGE_CTRL_S);
    for (uiIndex = 0; uiIndex < uiNum; uiIndex++)
    {
        enCtrlType = astTestcasePageCtrls[uiIndex].enCtrlType;
        strCtrlCaption = astTestcasePageCtrls[uiIndex].strCaption;
        switch (enCtrlType)
        {
            case UH_LABEL:
                pWidgetTemp = (QWidget*)(new QLabel(strCtrlCaption, this));
                break;

            case UH_EDIT:
                pWidgetTemp = (QWidget*)(new QLineEdit(this));
                break;

            case UH_CHECKBOX:
                pWidgetTemp = (QWidget*)(new QCheckBox(strCtrlCaption, this));
                break;
            default:
                return;
        }

        astTestcasePageCtrls[uiIndex].pwgtCtrl = pWidgetTemp;
        m_vectorTestcasePageCtrls.append(astTestcasePageCtrls[uiIndex]);

        m_mapCtrl.insert(strCtrlCaption, pWidgetTemp);

        pGrdLytParams->addWidget(
                                  pWidgetTemp,
                                  astTestcasePageCtrls[uiIndex].iRow,
                                  astTestcasePageCtrls[uiIndex].iColumn,
                                  astTestcasePageCtrls[uiIndex].iRowSpan,
                                  astTestcasePageCtrls[uiIndex].iColumnSpan
                                );
    }
}

uint TestCaseAutoSleepWake::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());


    return 0;
}
