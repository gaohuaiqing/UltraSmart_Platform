#ifndef TEST_CASE_PHV_COM_TEST_H
#define TEST_CASE_PHV_COM_TEST_H

#include "UsHwCustomWidget.h"

class TestCasePhvComPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCasePhvComPress();
    ~TestCasePhvComPress();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_PHV_COM_TEST_H
