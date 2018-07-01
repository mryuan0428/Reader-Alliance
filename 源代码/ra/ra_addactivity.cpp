#include "ra_addactivity.h"
#include "ui_ra_addactivity.h"
#include <QDate>
#include <QDateEdit>

RA_AddActivity::RA_AddActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_AddActivity)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/3.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->pushButton->setFont(font);
    ui->lineEdit->setFont(font);
    ui->dateEdit->setFont(font);
    ui->textEdit->setFont(font);
}

RA_AddActivity::~RA_AddActivity()
{
    delete ui;
}

void RA_AddActivity::on_pushButton_clicked()
{
    //先检查信息是否完整
    if((ui->lineEdit->text().isEmpty())||(ui->textEdit->toPlainText().isEmpty())){
        QMessageBox::warning(0,"Error",u8"请完整填写信息！");
    }
    else{
        //检查日期的正确性
        if(ui->dateEdit->date()<QDate::currentDate()){
            QMessageBox::warning(0,"Error",u8"日期信息可能存在错误，请检查。");
        }
        else{
            QSqlQuery query1;
            query1.prepare(u8"insert into activity values (:uid,:name,:date,:des)");
            query1.bindValue(":name",ui->lineEdit->text());
            query1.bindValue(":uid",uid);
            query1.bindValue(":des",ui->textEdit->toPlainText());
            query1.bindValue(":date",ui->dateEdit->date().toString("yyyy-MM-dd"));
            if(!query1.exec()){
                QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
            }
            else{
                QMessageBox::information(0,"Success",u8"活动发布成功~");
            }
        }
    }

}
