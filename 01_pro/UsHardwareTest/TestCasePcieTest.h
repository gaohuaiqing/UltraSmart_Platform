#ifndef TEST_CASE_PCIE_TEST_H
#define TEST_CASE_PCIE_TEST_H

#include "UsHwCustomWidget.h"

class TestCasePciePress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCasePciePress();
    ~TestCasePciePress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_PCIE_TEST_H
