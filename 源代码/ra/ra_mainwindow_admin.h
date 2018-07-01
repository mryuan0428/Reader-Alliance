#ifndef RA_MAINWINDOW_ADMIN_H
#define RA_MAINWINDOW_ADMIN_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>
#include <ra_bookinfo.h>
#include <ra_regman.h>
#include <ra_bookman.h>
#include <ra_activityman.h>
#include <ra_userman.h>

namespace Ui {
class RA_MainWindow_Admin;
}

class RA_MainWindow_Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit RA_MainWindow_Admin(QWidget *parent = 0);
    ~RA_MainWindow_Admin();

private slots:
    void on_pushButton_clicked();

    void on_actionRegMan_triggered();

    void on_actionBookMan_triggered();

    void on_actionActivityMan_triggered();

    void on_actionUserMan_triggered();

private:
    Ui::RA_MainWindow_Admin *ui;
    RA_BookInfo *dialog;  //书籍信息窗口
    RA_RegMan *dialog_rm; //注册管理窗口
    RA_BookMan *dialog_bm; //书籍管理窗口
    RA_ActivityMan *dialog_am; //活动管理窗口
    RA_UserMan *dialog_um; //用户管理窗口
};

#endif // RA_MAINWINDOW_ADMIN_H
