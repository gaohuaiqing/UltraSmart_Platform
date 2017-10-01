#ifndef TEST_CASE_SMBUS_TEST_H
#define TEST_CASE_SMBUS_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseSmBusPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseSmBusPress();
    ~TestCaseSmBusPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_SMBUS_TEST_H
