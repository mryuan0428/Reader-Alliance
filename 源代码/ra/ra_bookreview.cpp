#include "ra_bookreview.h"
#include "ui_ra_bookreview.h"

RA_BookReview::RA_BookReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_BookReview)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/8.jpg").scaled(// 缩放背景图.
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
    ui->lineEdit_2->setFont(font);
    ui->textEdit->setFont(font);
}

RA_BookReview::~RA_BookReview()
{
    delete ui;
}

void RA_BookReview::on_pushButton_clicked()
{
    //检查信息填写是否为空
    if((ui->lineEdit->text().isEmpty())||(ui->lineEdit_2->text().isEmpty())||(ui->textEdit->toPlainText().isEmpty())){
        QMessageBox::warning(0,"Error",u8"请完整填写信息！");
    }
    else{
        //先检查是否重复发表书评
        QSqlQuery query1;
        query1.prepare(u8"select count(*) from bkreview where ISBN=:isbn AND readerid=:uid");
        query1.bindValue(":isbn",ui->lineEdit->text());
        query1.bindValue(":uid",uid);
        if(!query1.exec()){
            QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
        }
        else{
            //若已经发表过，则提示不能重复发表
            query1.next();
            if(query1.value(0).toInt()==1){
                QMessageBox::warning(0,"Warning",u8"请勿重复发表书评");
            }
            else{ //提交书评
                query1.prepare(u8"insert into bkreview values (:isbn,:uid,:des)");
                query1.bindValue(":isbn",ui->lineEdit->text());
                query1.bindValue(":uid",uid);
                query1.bindValue(":des",ui->textEdit->toPlainText());
                if(!query1.exec()){
                    QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                }
                else{
                    QMessageBox::information(0,"Success",u8"书评发表成功，谢谢您的分享~");
                }
            }
        }
    }

}
