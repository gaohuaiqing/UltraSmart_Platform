#ifndef USHWCUSTOMWIDGET_H
#define USHWCUSTOMWIDGET_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QMap>
#include <QSettings>
#include <QThread>
#include <QLabel>

#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>

#include "UltraSmartLog.h"

typedef enum tagCtrlType
{
    UH_LABEL = 0,
    UH_EDIT,
    UH_CHECKBOX
}UH_CTRL_TYPE_E;

typedef struct tagTestCasePageCtrl
{
    QString             strCaption;
    QWidget             *pwgtCtrl;
    UH_CTRL_TYPE_E      enCtrlType;
    int                 iRow;
    int                 iColumn;
    int                 iRowSpan;
    int                 iColumnSpan;
}UH_TEST_CASE_PAGE_CTRL_S;

class CUsHwCustomWidget : public QWidget
{
    Q_OBJECT

public slots:
    virtual uint UsHwInitParams(const char *pcCfgFilePath, bool &bChecked);
    virtual uint UsHwSaveParams(const char *pcCfgFilePath, bool bChecked);
    virtual uint UsHwStartTest();

public:
    QVector<UH_TEST_CASE_PAGE_CTRL_S>   m_vectorTestcasePageCtrls;
    QMap<QString, QWidget*>             m_mapCtrl;

    //  定义写到参数配置文件中的section字段名称
    QString         m_strParamSection;

};

static  const char   *g_pcHKLMRunSection = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
static  const char   *g_pcHKLMRunKey = "UltraSmart";


#endif // USHWCUSTOMWIDGET_H
