#ifndef RA_BOOKREVIEW_H
#define RA_BOOKREVIEW_H

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
class RA_BookReview;
}

extern QString uid;
extern QString upwd;

class RA_BookReview : public QDialog
{
    Q_OBJECT

public:
    explicit RA_BookReview(QWidget *parent = 0);
    ~RA_BookReview();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RA_BookReview *ui;
};

#endif // RA_BOOKREVIEW_H
