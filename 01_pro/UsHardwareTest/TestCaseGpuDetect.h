#ifndef TEST_CASE_GPU_DETECT_H
#define TEST_CASE_GPU_DETECT_H

#include "UsHwCustomWidget.h"

class TestCaseGpuDetect : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseGpuDetect();
    ~TestCaseGpuDetect();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_GPU_DETECT_H
