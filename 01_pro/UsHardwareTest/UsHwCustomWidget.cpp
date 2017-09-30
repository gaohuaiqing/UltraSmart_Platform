
#include "UsHwCustomWidget.h"

uint CUsHwCustomWidget::UsHwInitParams(const char *pcCfgFilePath, bool &bChecked)
{
    // 从配置文件加载配置，并设置页面的控件值
    QSettings     configFile(pcCfgFilePath, QSettings::IniFormat);

    QString             strIniKey = "";
    QString             strIniVal = "";

    UH_CTRL_TYPE_E      enCtrlType;
    Qt::CheckState      checkState;

    strIniKey = m_strParamSection + "/NeedTest";
    if (!configFile.contains(strIniKey))
    {
        qDebug("%s", strIniKey.toStdString().data());
    }

    QVector<UH_TEST_CASE_PAGE_CTRL_S>::iterator     iteratorCtrl;

    configFile.beginGroup(m_strParamSection);

    for (iteratorCtrl = m_vectorTestcasePageCtrls.begin(); iteratorCtrl != m_vectorTestcasePageCtrls.end(); iteratorCtrl++)
    {
        strIniKey = iteratorCtrl->strCaption;

        enCtrlType = iteratorCtrl->enCtrlType;
        switch(enCtrlType)
        {
            case UH_EDIT:
                strIniVal = configFile.value(strIniKey).toString();
                if (strIniVal.startsWith("0x"))
                {
                    strIniVal = strIniVal.mid(2);
                }

                ((QLineEdit*)iteratorCtrl->pwgtCtrl)->setText(strIniVal);
                break;

            case UH_CHECKBOX:
                strIniKey = "Check" + strIniKey;
                strIniVal = configFile.value(strIniKey).toString();
                checkState = ("1" == strIniVal)? Qt::Checked : Qt::Unchecked;
                ((QCheckBox*)iteratorCtrl->pwgtCtrl)->setCheckState(checkState);
                break;

            default:
                continue;
        }
    }

    strIniKey = "NeedTest";
    strIniVal = configFile.value(strIniKey).toString();
    bChecked = ("1" == strIniVal)? true : false;

    configFile.endGroup();

    return 0;
}

uint CUsHwCustomWidget::UsHwSaveParams(const char *pcCfgFilePath, bool bChecked)
{
    // 保存控件的输入值到配置文件
    QSettings           configFile(pcCfgFilePath, QSettings::IniFormat);
    QString             strIniKey = "";
    QString             strIniVal = "";

    UH_CTRL_TYPE_E      enCtrlType;
    Qt::CheckState      checkState;
    QWidget             *pWidgetCtrl = NULL;

    QVector<UH_TEST_CASE_PAGE_CTRL_S>::iterator     iteratorCtrl;
    QVector<UH_TEST_CASE_PAGE_CTRL_S>::iterator     iteratorCtrlPrev;

    configFile.beginGroup(m_strParamSection);

    for (iteratorCtrl = m_vectorTestcasePageCtrls.begin(); iteratorCtrl != m_vectorTestcasePageCtrls.end(); iteratorCtrl++)
    {
        strIniKey = iteratorCtrl->strCaption;

        enCtrlType = iteratorCtrl->enCtrlType;
        pWidgetCtrl = iteratorCtrl->pwgtCtrl;
        switch(enCtrlType)
        {
            case UH_EDIT:
                iteratorCtrlPrev = iteratorCtrl - 1;

                strIniVal = ((QLineEdit*)pWidgetCtrl)->text();
                if (iteratorCtrlPrev->strCaption.startsWith("0x"))
                {
                    strIniVal = "0x" + strIniVal;
                }
                configFile.setValue(strIniKey, strIniVal);

                break;

            case UH_CHECKBOX:
                checkState = ((QCheckBox*)pWidgetCtrl)->checkState();

                strIniKey = "Check" + strIniKey;
                strIniVal = (Qt::Checked == checkState)? "1" : "0";
                configFile.setValue(strIniKey, strIniVal);
                break;

            default:
                continue;
        }
    }

    strIniKey = "NeedTest";
    strIniVal = bChecked? "1" : "0";
    configFile.setValue(strIniKey, strIniVal);

    configFile.endGroup();

    return 0;
}

uint CUsHwCustomWidget::UsHwStartTest()
{
    return 0;
}
