#ifndef WIDGETAUTOPOWERTEST_H
#define WIDGETAUTOPOWERTEST_H

#include <QWidget>

namespace Ui {
class widgetAutoPowerTest;
}

class widgetAutoPowerTest : public QWidget
{
    Q_OBJECT

public:
    explicit widgetAutoPowerTest(QWidget *parent = 0);
    ~widgetAutoPowerTest();

private:
    Ui::widgetAutoPowerTest *ui;
};

#endif // WIDGETAUTOPOWERTEST_H
