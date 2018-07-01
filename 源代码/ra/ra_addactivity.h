#ifndef RA_ADDACTIVITY_H
#define RA_ADDACTIVITY_H

#include <QDialog>
#include <QMessageBox>
#include <QFont>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QString>
#include <QSqlError>

namespace Ui {
class RA_AddActivity;
}

extern QString uid;
extern QString upwd;

class RA_AddActivity : public QDialog
{
    Q_OBJECT

public:
    explicit RA_AddActivity(QWidget *parent = 0);
    ~RA_AddActivity();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_AddActivity *ui;
};

#endif // RA_ADDACTIVITY_H
