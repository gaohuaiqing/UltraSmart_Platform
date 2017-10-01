#ifndef TEST_CASE_CDROM_DETECT_H
#define TEST_CASE_CDROM_DETECT_H

#include "UsHwCustomWidget.h"

class TestCaseCDRomDetect : public CUsHwCustomWidget
{
    Q_OBJECT

public:
    explicit TestCaseCDRomDetect();
    ~TestCaseCDRomDetect();

    void CreateUi();
    uint UsHwStartTest();
};

#endif // TEST_CASE_CDROM_DETECT_H
