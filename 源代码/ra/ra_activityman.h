#ifndef RA_ACTIVITYMAN_H
#define RA_ACTIVITYMAN_H

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
#include <QImage>
#include <QSqlQueryModel>
#include <QRegExp>
#include <QPalette>

namespace Ui {
class RA_ActivityMan;
}

class RA_ActivityMan : public QDialog
{
    Q_OBJECT

public:
    explicit RA_ActivityMan(QWidget *parent = 0);
    ~RA_ActivityMan();
    int g=-1;

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_ActivityMan *ui;
};

#endif // RA_ACTIVITYMAN_H
