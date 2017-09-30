#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "UsHardwareTest/UsHwTestForm.h"

namespace Ui {
class MainWindow;
}

class CDockWidgetTextEdit : public QTextEdit
{
public:
    QSize sizeHint() const
    {
        return QSize(850, 60);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void UsHwLogInit();
    void UsHwCreateCustomCtrl();

private:
    Ui::MainWindow *ui;

    UsHwTestForm            *m_FormHwTest;
    QDockWidget             *m_pclDockWgt;
    CDockWidgetTextEdit     *m_pclDockWgtEdit;

    void closeEvent(QCloseEvent *event);

public slots:
    void UsHwLogoutSlot(QString strLog);
    void UsHwCleanLogSlot();

private slots:
    void on_action_LogToFile_triggered();
    void on_action_LogWindow_triggered();
    void on_action_ClearLog_triggered();
};

#endif // MAINWINDOW_H
