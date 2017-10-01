#ifndef TEST_CASE_DISPLAY_TEST_H
#define TEST_CASE_DISPLAY_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseDisplayTest : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseDisplayTest();
    ~TestCaseDisplayTest();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_DISPLAY_TEST_H
