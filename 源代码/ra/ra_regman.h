#ifndef RA_REGMAN_H
#define RA_REGMAN_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>
#include <QFont>

namespace Ui {
class RA_RegMan;
}

class RA_RegMan : public QDialog
{
    Q_OBJECT

public:
    explicit RA_RegMan(QWidget *parent = 0);
    ~RA_RegMan();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_RegMan *ui;
};

#endif // RA_REGMAN_H
