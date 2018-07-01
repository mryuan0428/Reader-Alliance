#ifndef RA_MAINWINDOW_H
#define RA_MAINWINDOW_H

#include <QMainWindow>
#include <ra_bookinfo.h>
#include <QString>
#include <ra_login.h>
#include <ra_register.h>
#include <ra_activity.h>

namespace Ui {
class RA_MainWindow;
}
//用户状态
extern int who;

class RA_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RA_MainWindow(QWidget *parent = 0);
    ~RA_MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionLogin_triggered();

    void on_actionRegister_triggered();

    void on_actionActivity_triggered();

    void check();

private:
    Ui::RA_MainWindow *ui;
    RA_BookInfo *dialog;
    RA_Login *dialog_login;
    RA_Register *dialog_register;
    RA_Activity *dialog_acticity;
};

#endif // RA_MAINWINDOW_H
