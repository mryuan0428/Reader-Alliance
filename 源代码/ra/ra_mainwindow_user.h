#ifndef RA_MAINWINDOW_USER_H
#define RA_MAINWINDOW_USER_H

#include <QMainWindow>
#include <QString>
#include <ra_bookinfo.h>
#include <ra_sharebook.h>
#include <ra_bookreview.h>
#include <ra_addactivity.h>
#include <ra_activity.h>
#include <ra_usercenter.h>

namespace Ui {
class RA_MainWindow_User;
}

extern QString uid;
extern QString upwd;

class RA_MainWindow_User : public QMainWindow
{
    Q_OBJECT

public:
    explicit RA_MainWindow_User(QWidget *parent = 0);
    ~RA_MainWindow_User();

private slots:
    void on_pushButton_clicked();
    void on_actionShare_triggered();
    void on_actionReview_triggered();
    void on_actionAddActivity_triggered();
    void on_actionActivity_triggered();
    void on_actionUserCenter_triggered();

private:
    Ui::RA_MainWindow_User *ui;
    RA_BookInfo *dialog;  //书籍信息窗口
    RA_ShareBook *dialog_sb; //分享书籍窗口
    RA_BookReview *dialog_br; //写书评窗口
    RA_AddActivity *dialog_aa; //活动发布窗口
    RA_Activity *dialog_acticity; //线下活动窗口
    RA_UserCenter *dialog_uc; //用户中心
};

#endif // RA_MAINWINDOW_USER_H
