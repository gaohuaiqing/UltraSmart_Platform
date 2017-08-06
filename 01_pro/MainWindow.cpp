#include "MainWindow.h"
#include "UsHardwareTest/widgetAutoPowerTest.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_FormHwTest = new UsHwTestForm(this);
    widgetAutoPowerTest *widgetAutoPwrTest = new widgetAutoPowerTest(this);

    setCentralWidget(widgetAutoPwrTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}
