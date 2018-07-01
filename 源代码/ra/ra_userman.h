#ifndef RA_USERMAN_H
#define RA_USERMAN_H

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
class RA_UserMan;
}

class RA_UserMan : public QDialog
{
    Q_OBJECT

public:
    explicit RA_UserMan(QWidget *parent = 0);
    ~RA_UserMan();
    int g=-1;

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_UserMan *ui;
};

#endif // RA_USERMAN_H
