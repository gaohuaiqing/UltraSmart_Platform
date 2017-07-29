#include "UsHardwareTest\widgetAutoPowerTest.h"
#include "ui_widgetAutoPowerTest.h"

widgetAutoPowerTest::widgetAutoPowerTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetAutoPowerTest)
{
    ui->setupUi(this);
}

widgetAutoPowerTest::~widgetAutoPowerTest()
{
    delete ui;
}
