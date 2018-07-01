#ifndef RA_BOOKINFO_H
#define RA_BOOKINFO_H

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
class RA_BookInfo;
}

extern QString BookName;
extern int who;
extern QString uid;
extern QString upwd;

class RA_BookInfo : public QDialog
{
    Q_OBJECT

public:
    explicit RA_BookInfo(QWidget *parent = 0);
    ~RA_BookInfo();
    QString oid;
    QString isbn;
    int n;

public:
    Ui::RA_BookInfo *ui;
private slots:
    void on_pushButton_clicked();
};

#endif // RA_BOOKINFO_H
