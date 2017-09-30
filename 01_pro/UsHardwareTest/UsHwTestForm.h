#ifndef USHWTESTFORM_H
#define USHWTESTFORM_H

#include <QStandardItem>
#include <QWidget>
#include <QVector>
#include <QList>
#include <QStackedWidget>
#include <QDateTime>
#include <QTimer>

#include "UsHardwareTest/UsHwCustomWidget.h"
#include "UsHardwareTest/UsHwTestcaseThreadObj.h"

#include "UltraSmartLog.h"

typedef struct tagUsHwTestCase
{
    QString                 strCaption;
    QStandardItem           **pitemParent;
    QStandardItem           *pitemTestCase;
    QStandardItem           *pitemTestResult;
    CUsHwCustomWidget       *pwgtTestCase;
}UH_TEST_CASE_S;

typedef struct tagUsHwTestcaseFuncThread
{
    QStandardItem           *pitemTestResult;
    CUsHwTestcaseThreadObj  *pObjTestcaseThread;
}UH_TEST_CASE_FUNC_THREAD_S;

namespace Ui {
class UsHwTestForm;
}

class UsHwTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit UsHwTestForm(QWidget *parent = 0);
    ~UsHwTestForm();

    void UsHwCreateHwTestTree();
    void UsHwConnectSignalAndSlots();
    void UsHwLoadParams(const char *pcCfgFilePath);
    void UsHwSaveParams(const char *pcCfgFilePath);
    void UsHwLoadGlobalParams(const char *pcCfgFilePath);
    void UsHwSaveGlobalParams(const char *pcCfgFilePath);
    QString UsHwCalInterval(uint64_t uiSeconds);
    void UsHwGetRuntimeCfgFromFile();
    void UsHwSaveRuntimeCfgToFile();

    bool IsAutoRun();
    void UsHwAutoStartTest();
    uint UsHwClearEnv();
    void UsHwPowerDown();
private:
    QVector<UH_TEST_CASE_S>     m_vectorUsHwTestCases;
    QStackedWidget              *m_pStackedWgtParams;
    uint                        m_uiTestcaseCnt;
    uint                        m_uiRecvResultCnt;
    QDateTime                   m_dateTimeStart;
    QTimer                      *m_pTimerDetectTest;

    QMap<QString, int64_t>      m_mapRuntimeCfg;

    Ui::UsHwTestForm *ui;

public slots:
    void UsHwLoadParams();
    void UsHwSaveParams();
    void UsHwStartTest();
    void UsHwPauseTest();
    void UsHwStopTest();
    void UsHwDetectTestTimer();

private slots:
    void on_treeView_HwTestItems_clicked(const QModelIndex &index);
    void treeItemChanged(QStandardItem *item);
    void treeItem_CheckChildChanged(QStandardItem *item);
    void treeItem_CheckAllChild_Recursion(QStandardItem *item, bool bChecked);
    void treeItem_CheckAllChild(QStandardItem *item, bool bChecked);
    Qt::CheckState CheckSibling(QStandardItem *item);

    void UsHwSetTestcaseResultSlot(QStandardItem *pitemResult, uint uiRetVal);
};

#define UH_TEST_RESULT_PASS     "Pass"
#define UH_TEST_RESULT_FAIL     "Fail"
#define UH_TEST_RESULT_TODO     "To do"

// ∂®“Â¥ÌŒÛ¬Î
#define UH_NO_ERROR             0
#define UH_FAIL                 (-1)
#define UH_PAUSED               1001




#endif // USHWTESTFORM_H
