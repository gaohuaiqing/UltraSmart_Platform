#ifndef USHWTESTFORM_H
#define USHWTESTFORM_H

#include <QWidget>
#include "widgetAutoPowerTest.h"

namespace Ui {
class UsHwTestForm;
}

class UsHwTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit UsHwTestForm(QWidget *parent = 0);
    ~UsHwTestForm();

    widgetAutoPowerTest     *pageAutoPowerTest;

    void UsHwCreateHwTestTree();

private:
    Ui::UsHwTestForm *ui;
};

#endif // USHWTESTFORM_H
