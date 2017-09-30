#ifndef TEST_CASE_AUTO_POWER_TEST_H
#define TEST_CASE_AUTO_POWER_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseAutoPower : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseAutoPower();
    ~TestCaseAutoPower();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_AUTO_POWER_TEST_H
