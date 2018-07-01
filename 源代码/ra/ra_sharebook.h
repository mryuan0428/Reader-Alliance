#ifndef RA_SHAREBOOK_H
#define RA_SHAREBOOK_H

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

namespace Ui {
class RA_ShareBook;
}

extern QString uid;
extern QString upwd;

class RA_ShareBook : public QDialog
{
    Q_OBJECT

public:
    explicit RA_ShareBook(QWidget *parent = 0);
    ~RA_ShareBook();
    QByteArray inByteArray; //书籍图片
    int flag=0; //是否已经选择图片标志

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::RA_ShareBook *ui;
};

#endif // RA_SHAREBOOK_H
