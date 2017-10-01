#ifndef TEST_CASE_WIFI_DETECT_H
#define TEST_CASE_WIFI_DETECT_H

#include "UsHwCustomWidget.h"

class TestCaseWiFiDetect : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseWiFiDetect();
    ~TestCaseWiFiDetect();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_WIFI_DETECT_H
