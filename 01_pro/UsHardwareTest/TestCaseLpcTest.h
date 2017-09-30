#ifndef TEST_CASE_LPC_TEST_H
#define TEST_CASE_LPC_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseLpcPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseLpcPress();
    ~TestCaseLpcPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_LPC_TEST_H
