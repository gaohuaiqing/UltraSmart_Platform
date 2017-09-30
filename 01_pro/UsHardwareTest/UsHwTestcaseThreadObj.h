#ifndef CUSHWTESTCASETHREAD_H
#define CUSHWTESTCASETHREAD_H

#include <QObject>
#include <QStandardItem>

#include "UsHwCustomWidget.h"

class CUsHwTestcaseThreadObj : public QObject
{
    Q_OBJECT
public:
    explicit CUsHwTestcaseThreadObj();

     CUsHwCustomWidget      *m_pwgtTestcase;
     QStandardItem          *m_pitemTestcaseResult;
signals:
    void UsHwSetTestcaseResultSignal(QStandardItem *pitemTestcaseResult, uint uiRetVal);

public slots:
    uint UsHwStartTest();
};

#endif // CUSHWTESTCASETHREAD_H
