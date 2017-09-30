#ifndef TEST_CASE_BATTERY_TEST_H
#define TEST_CASE_BATTERY_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseBatteryI2C : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseBatteryI2C();
    ~TestCaseBatteryI2C();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_BATTERY_TEST_H
