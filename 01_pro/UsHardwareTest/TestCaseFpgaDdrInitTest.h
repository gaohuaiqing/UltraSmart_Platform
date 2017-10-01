#ifndef TEST_CASE_FPGA_DDR_INIT_TEST_H
#define TEST_CASE_FPGA_DDR_INIT_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseFpgaDdrInitPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseFpgaDdrInitPress();
    ~TestCaseFpgaDdrInitPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_FPGA_DDR_INIT_TEST_H
