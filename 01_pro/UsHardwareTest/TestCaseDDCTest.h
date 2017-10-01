#ifndef TEST_CASE_DDC_TEST_H
#define TEST_CASE_DDC_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseDDCPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseDDCPress();
    ~TestCaseDDCPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_DDC_TEST_H
