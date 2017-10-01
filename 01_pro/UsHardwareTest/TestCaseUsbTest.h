#ifndef TEST_CASE_USB_TEST_H
#define TEST_CASE_USB_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseUsbPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseUsbPress();
    ~TestCaseUsbPress();

    void CreateUi();
    uint UsHwStartTest();

public slots:
    void UsHwBrowsePath();

private:
    QMap<QPushButton*, QLineEdit*>      m_mapBrowsePath;
};

#endif // TEST_CASE_USB_TEST_H
