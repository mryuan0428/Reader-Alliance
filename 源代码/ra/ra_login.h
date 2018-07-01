#ifndef RA_LOGIN_H
#define RA_LOGIN_H
#include <ra_mainwindow_user.h>
#include <ra_mainwindow_admin.h>
#include <QDialog>
#include <QMessageBox>
#include <QFont>
#include <QSqlQuery>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>

namespace Ui {
class RA_Login;
}

//用户状态
extern int who;
extern QString uid;
extern QString upwd;

class RA_Login : public QDialog
{
    Q_OBJECT

public:
    explicit RA_Login(QWidget *parent = 0);
    ~RA_Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_Login *ui;
    RA_MainWindow_User *dialog;
    RA_MainWindow_Admin *dialog_a;
};

#endif // RA_LOGIN_H
