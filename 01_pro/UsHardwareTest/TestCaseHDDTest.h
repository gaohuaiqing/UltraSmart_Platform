#ifndef TEST_CASE_HDD_TEST_H
#define TEST_CASE_HDD_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseHDDPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseHDDPress();
    ~TestCaseHDDPress();

    void CreateUi();
    uint UsHwStartTest();

public slots:
    void UsHwBrowsePath();
};

#endif // TEST_CASE_HDD_TEST_H
