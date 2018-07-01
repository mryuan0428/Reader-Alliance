#ifndef RA_USERCENTER_H
#define RA_USERCENTER_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <QTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>

namespace Ui {
class RA_UserCenter;
}

extern QString uid;
extern QString upwd;

class RA_UserCenter : public QDialog
{
    Q_OBJECT

public:
    explicit RA_UserCenter(QWidget *parent = 0);
    ~RA_UserCenter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RA_UserCenter *ui;
};

#endif // RA_USERCENTER_H
