#ifndef TEST_CASE_FPGA_DDR_RW_TEST_H
#define TEST_CASE_FPGA_DDR_RW_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseFpgaDdrRw : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseFpgaDdrRw();
    ~TestCaseFpgaDdrRw();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_FPGA_DDR_RW_TEST_H
