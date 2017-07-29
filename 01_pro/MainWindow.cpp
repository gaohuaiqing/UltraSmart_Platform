#include "MainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_FormHwTest = new UsHwTestForm(this);
    setCentralWidget(m_FormHwTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}
