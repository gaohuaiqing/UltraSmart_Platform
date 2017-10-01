#ifndef TEST_CASE_PROBE_ID_TEST_H
#define TEST_CASE_PROBE_ID_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseProbeIdPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseProbeIdPress();
    ~TestCaseProbeIdPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_PROBE_ID_TEST_H
