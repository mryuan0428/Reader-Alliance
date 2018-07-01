#ifndef RA_BOOKMAN_H
#define RA_BOOKMAN_H

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
class RA_BookMan;
}

class RA_BookMan : public QDialog
{
    Q_OBJECT

public:
    explicit RA_BookMan(QWidget *parent = 0);
    ~RA_BookMan();
    QByteArray inByteArray; //书籍图片
    int flag=0; //是否已经选择图片标志
    int g=-1;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RA_BookMan *ui;
};

#endif // RA_BOOKMAN_H
