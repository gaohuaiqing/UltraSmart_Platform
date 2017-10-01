#ifndef TEST_CASE_AUTO_SLEEP_WAKE_TEST_H
#define TEST_CASE_AUTO_SLEEP_WAKE_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseAutoSleepWake : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseAutoSleepWake();
    ~TestCaseAutoSleepWake();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_AUTO_SLEEP_WAKE_TEST_H
