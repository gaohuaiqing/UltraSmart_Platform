#ifndef TEST_CASE_SSD_TEST_H
#define TEST_CASE_SSD_TEST_H

#include "UsHwCustomWidget.h"

class TestCaseSSDPress : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseSSDPress();
    ~TestCaseSSDPress();

    void CreateUi();
    uint UsHwStartTest();

public slots:
    void UsHwBrowsePath();
};

#endif // TEST_CASE_SSD_TEST_H
