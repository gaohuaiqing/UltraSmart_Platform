#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T09:11:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UltraSmart
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
        UsHardwareTest/UsHwTestForm.cpp \
    UsHardwareTest/UsHwCustomWidget.cpp \
    UsHardwareTest/TestCaseAutoPowerTest.cpp \
    UsHardwareTest/TestCaseBatteryTest.cpp \
    UsHardwareTest/TestCaseLpcTest.cpp \
    UsHardwareTest/TestCasePcieTest.cpp \
    UltraSmartLog.cpp \
    UsHardwareTest/UsHwTestcaseThreadObj.cpp \
    UsHwPowerControl.cpp \
    UsHardwareTest/TestCaseUsbTest.cpp \
    UsHardwareTest/TestCaseAutoSleepWakeTest.cpp \
    UsHardwareTest/TestCaseHDDTest.cpp \
    UsHardwareTest/TestCaseSSDTest.cpp \
    UsHardwareTest/TestCaseSmBusTest.cpp \
    UsHardwareTest/TestCaseDisplayTest.cpp \
    UsHardwareTest/TestCaseDDCTest.cpp \
    UsHardwareTest/TestCaseCDRomDetect.cpp \
    UsHardwareTest/TestCaseWiFiDetect.cpp \
    UsHardwareTest/TestCaseGpuDetect.cpp \
    UsHardwareTest/TestCaseFpgaDdrInitTest.cpp \
    UsHardwareTest/TestCaseFpgaDdrRwTest.cpp \
    UsHardwareTest/TestCasePhvComTest.cpp \
    UsHardwareTest/TestCaseProbeIdTest.cpp
        
HEADERS += \
        MainWindow.h \
        UsHardwareTest/UsHwTestForm.h \
    UsHardwareTest/UsHwCustomWidget.h \
    UsHardwareTest/TestCaseAutoPowerTest.h \
    UsHardwareTest/TestCaseBatteryTest.h \
    UsHardwareTest/TestCaseLpcTest.h \
    UsHardwareTest/TestCasePcieTest.h \
    UltraSmartLog.h \
    UsHardwareTest/UsHwTestcaseThreadObj.h \
    UsHwPowerControl.h \
    UsHardwareTest/TestCaseUsbTest.h \
    UsHardwareTest/TestCaseAutoSleepWakeTest.h \
    UsHardwareTest/TestCaseHDDTest.h \
    UsHardwareTest/TestCaseSSDTest.h \
    UsHardwareTest/TestCaseSmBusTest.h \
    UsHardwareTest/TestCaseDisplayTest.h \
    UsHardwareTest/TestCaseDDCTest.h \
    UsHardwareTest/TestCaseCDRomDetect.h \
    UsHardwareTest/TestCaseWiFiDetect.h \
    UsHardwareTest/TestCaseGpuDetect.h \
    UsHardwareTest/TestCaseFpgaDdrInitTest.h \
    UsHardwareTest/TestCaseFpgaDdrRwTest.h \
    UsHardwareTest/TestCasePhvComTest.h \
    UsHardwareTest/TestCaseProbeIdTest.h
        
FORMS += \
    MainWindow.ui \
    UsHardwareTest/UsHwTestForm.ui

RESOURCES += \
    customresource.qrc


unix|win32: LIBS += -lpowrprof
