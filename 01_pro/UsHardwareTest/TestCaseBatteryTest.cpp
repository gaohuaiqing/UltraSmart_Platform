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
    uint        uiIndex = 0;
    uint        uiNum = 0;
    UH_CTRL_TYPE_E      enCtrlType;
    QWidget             *pWidgetTemp = NULL;

    QString             strCtrlCaption = "";

    // 新建栅格布局管理器
    QGridLayout *pGrdLytParams = new QGridLayout(this);

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

uint TestCaseBatteryI2C::UsHwStartTest()
{
    Logout("Current Testcase is %s ", m_strParamSection.toStdString().data());



    return 0;
}
