#include "UsHwTestForm.h"
#include "ui_UsHwTestForm.h"
#include <QStandardItem>
#include <QMap>


UsHwTestForm::UsHwTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsHwTestForm)
{
    ui->setupUi(this);

    UsHwCreateHwTestTree();

    pageAutoPowerTest = new widgetAutoPowerTest();

    ui->stackedWidget_Param->addWidget(pageAutoPowerTest);

}

UsHwTestForm::~UsHwTestForm()
{
    delete ui;
}

void UsHwTestForm::UsHwCreateHwTestTree()
{
    QStandardItemModel  *model = new QStandardItemModel(ui->treeView_HwTestItems);
    model->setHorizontalHeaderLabels(QStringList() << tr("Test Items") << tr("Test Result"));

    QStandardItem   *itemTestGroup = new QStandardItem(tr("Power"));
    itemTestGroup->setCheckable(true);
    itemTestGroup->setTristate(true);

    model->appendRow(itemTestGroup);

    QStandardItem   *itemTestCase = new QStandardItem(tr("Auto Power"));
    itemTestCase->setCheckable(true);
    itemTestCase->setTristate(false);

    itemTestGroup->appendRow(itemTestCase);

    QStandardItem   *itemTestCaseResult = new QStandardItem(tr("To do"));
    itemTestGroup->setChild(itemTestCase->index().row(), 1, itemTestCaseResult);

    //itemTestCaseResult->setText("Pass");

    itemTestCase = new QStandardItem(tr("BatteryI2C Test"));
    itemTestCase->setCheckable(true);
    itemTestCase->setTristate(false);

    itemTestGroup->appendRow(itemTestCase);

    itemTestCaseResult = new QStandardItem(tr("To do"));
    itemTestGroup->setChild(itemTestCase->index().row(), 1, itemTestCaseResult);


    ui->treeView_HwTestItems->setModel(model);
    ui->treeView_HwTestItems->expandAll();
    ui->treeView_HwTestItems->setColumnWidth(0, 200);

    //ui->splitter->setStretchFactor(0, 400);
    //ui->splitter->setStretchFactor(1, 400);

    //ui->frame->set

}
