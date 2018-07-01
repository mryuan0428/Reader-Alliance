#ifndef RA_REGISTER_H
#define RA_REGISTER_H

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
class RA_Register;
}

class RA_Register : public QDialog
{
    Q_OBJECT

public:
    explicit RA_Register(QWidget *parent = 0);
    ~RA_Register();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_Register *ui;
};

#endif // RA_REGISTER_H
