#include "ra_sharebook.h"
#include "ui_ra_sharebook.h"
#include <QPalette>

RA_ShareBook::RA_ShareBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_ShareBook)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/10.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    //设置页面字体
    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->pushButton->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->lineEdit->setFont(font);
    ui->lineEdit_2->setFont(font);
    ui->lineEdit_3->setFont(font);
    ui->lineEdit_4->setFont(font);

}

RA_ShareBook::~RA_ShareBook()
{
    delete ui;
}

void RA_ShareBook::on_pushButton_clicked()
{
    //选择图片上传
    QString imgName = QFileDialog::getOpenFileName(  this, tr("选择图片"),  "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));
    if(imgName.isEmpty())
        {
            QMessageBox mesg;
            mesg.warning(this,u8"警告",u8"打开图片失败!");
        }
    else
        {
            //指示label改变
            ui->label_6->setText("*selected");
            QPalette pa;
            pa.setColor(QPalette::WindowText,Qt::blue);
            ui->label_6->setPalette(pa);

            QFile file(imgName);
            if (!file.open(QIODevice::ReadOnly))
                {
                    QMessageBox mesg;
                    mesg.warning(this,u8"警告",u8"打开图片失败!");
                }
            else{
                inByteArray=file.readAll();
                flag=1;
                /*QSqlQuery query;
                QString str(u8"insert into book values ('25259302','银火箭少年科幻系列','刘慈欣','user1', :picture ,1)");
                query.prepare(str);
                query.bindValue(":picture",inByteArray);
                if(!query.exec())
                {
                    QMessageBox::warning(0,"Error",QString("Fail to insert\n%1").arg(query.lastError().text()));
                }
                */
            }

        }
}

void RA_ShareBook::on_pushButton_2_clicked()
{
    //检查信息是否完整
    if((ui->lineEdit->text().isEmpty())||(ui->lineEdit_2->text().isEmpty())||(ui->lineEdit_3->text().isEmpty())||(ui->lineEdit_4->text().isEmpty())||(flag==0)){
        QMessageBox::warning(0,"Error",u8"请完整填写书籍信息！");
    }
    else{
        //检查是否已经分享过
        QSqlQuery query1;
        query1.prepare(u8"select count(*) from book where ISBN=:isbn AND ownerid=:uid");
        query1.bindValue(":isbn",ui->lineEdit->text());
        query1.bindValue(":uid",uid);
        if(!query1.exec()){
            QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
        }
        else{
            //若已经分享过则查询分享数量，改动一下num即可
            query1.next();
            if(query1.value(0).toInt()==1){
                query1.prepare(u8"select * from book where ISBN=:isbn AND ownerid=:uid");
                query1.bindValue(":isbn",ui->lineEdit->text());
                query1.bindValue(":uid",uid);
                if(!query1.exec()){
                    QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                }
                else{
                    query1.next();
                    int sum=query1.value(5).toInt()+ui->lineEdit_4->text().toInt();
                    query1.prepare(u8"update book set num =:sum where ISBN= :isbn AND ownerid=:uid");
                    query1.bindValue(":isbn",ui->lineEdit->text());
                    query1.bindValue(":uid",uid);
                    query1.bindValue(":sum",sum);
                    if(!query1.exec()){
                        QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                    }
                    else{
                        QMessageBox::information(0,"Success",u8"图书分享成功，谢谢您的分享~");
                    }
                }
            }
            else{ //若未分享过
                query1.prepare(u8"insert into book values (:isbn,:name,:author,:uid,:pic,:num)");
                query1.bindValue(":isbn",ui->lineEdit->text());
                query1.bindValue(":name",ui->lineEdit_2->text());
                query1.bindValue(":author",ui->lineEdit_3->text());
                query1.bindValue(":uid",uid);
                query1.bindValue(":pic",inByteArray);
                query1.bindValue(":num",ui->lineEdit_4->text());
                if(!query1.exec()){
                    QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                }
                else{
                    QMessageBox::information(0,"Success",u8"图书分享成功，谢谢您的分享~");
                }

                //给分享者更改分享书籍数量值
                QSqlQuery query2;
                query2.prepare(u8"select * from users where ID=:uid ");
                query2.bindValue(":uid",uid);
                if(!query2.exec()){
                    QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query2.lastError().text()));
                }
                else{
                    query2.next();
                    int s=query2.value(3).toInt()+ui->lineEdit_4->text().toInt();
                    query2.prepare(u8"update users set share =:s where ID=:uid");
                    query2.bindValue(":uid",uid);
                    query2.bindValue(":s",s);
                    if(!query2.exec()){
                        QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                    }
                }

            }

        }
    }

}
