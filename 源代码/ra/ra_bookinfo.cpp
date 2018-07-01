#include "ra_bookinfo.h"
#include "ui_ra_bookinfo.h"

RA_BookInfo::RA_BookInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_BookInfo)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/2.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    if(who==2) ui->pushButton->setVisible(false);
    QFont font ("Microsoft YaHei", 11, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    ui->label->setFont(font);
    QFont font2 ("Microsoft YaHei", 10, 50);
    ui->pushButton->setFont(font2);
    QFont font3 ("Microsoft YaHei", 10, 50);
    ui->label_3->setFont(font3);
    ui->label_4->setFont(font3);
    ui->label_5->setFont(font3);
    ui->label_6->setFont(font3);

    QSqlQuery query;
    query.prepare(u8"select * from book where name=:bookname");
    query.bindValue(":bookname",BookName);

    if(!query.exec())
    {
        QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
    }
    else{
        query.next();
        //显示图片
        QByteArray picture=query.value(4).toByteArray();
        QPixmap outimage;
        outimage.loadFromData(picture);
        outimage=outimage.scaled(199,249,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_1->setPixmap(outimage);
        //显示其他信息
        QFont font ( "Microsoft YaHei",14,75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
        ui->label_2->setFont(font);
        ui->label_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
        ui->label_3->setText(QString(u8"ISBN：%1").arg(query.value(0).toString()));
        isbn=query.value(0).toString();
        ui->label_4->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
        //检索分享者姓名
        QSqlQuery queryusr;
        queryusr.prepare(u8"select name from users where ID = :usid");
        queryusr.bindValue(":usid",query.value(3).toString());
        oid=query.value(3).toString();
        if(!queryusr.exec()){
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(queryusr.lastError().text()));
        }
        else{
            queryusr.next();
            ui->label_5->setText(QString(u8"分享用户：%1").arg(queryusr.value(0).toString()));
        }

        //查询可借阅数量
        QSqlQuery lendnum;
        lendnum.prepare(u8"select count(*) from lend where ISBN=:bkisbn AND ownerid=:oid AND status=0");
        lendnum.bindValue(":bkisbn",query.value(0).toString());
        lendnum.bindValue("oid",query.value(3).toString());
        if(!lendnum.exec()){
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(lendnum.lastError().text()));
        }
        else{
            lendnum.next();
            ui->label_6->setText(QString(u8"可借阅数量：%1").arg(query.value(5).toInt()-lendnum.value(0).toInt()));
            n=query.value(5).toInt()-lendnum.value(0).toInt();
        }

        //书评显示实现
        ui->tabWidget->clear();
        QSqlQuery bkreview;
        bkreview.prepare(u8"select * from bkreview where ISBN=:bkisbn");
        bkreview.bindValue(":bkisbn",query.value(0).toString());

        if(!bkreview.exec()){
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(bkreview.lastError().text()));
        }
        else{
            while(bkreview.next()){
                QSqlQuery queryusr;
                queryusr.prepare(u8"select name from users where ID = :usid");
                queryusr.bindValue(":usid",bkreview.value(1).toString());
                if(!queryusr.exec()){
                    QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(queryusr.lastError().text()));
                }
                else{
                    queryusr.next();
                    QLabel *l=new QLabel(bkreview.value(2).toString());
                    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
                    l->setFont(font);
                    l->setGeometry(QRect(328, 240, 329, 27*4)); //四倍行距
                    l->setWordWrap(true);
                    l->setAlignment(Qt::AlignTop);
                    ui->tabWidget->addTab(l,u8"By："+queryusr.value(0).toString());
                }
            }

        }

    }
}

RA_BookInfo::~RA_BookInfo()
{
    delete ui;
}

void RA_BookInfo::on_pushButton_clicked()
{
    if(who==0) //游客身份请求借阅
        {QMessageBox::warning(0,"Warning",u8"请登录后再申请借阅!");}
    else{
        if(n<=0){ //无多余可接书籍
            QMessageBox::warning(0,"Warning",u8"书籍已被他人借阅，可以再看一下其他分享的书籍哦~");
        }
        else { //先检查是否已经借阅过
            QSqlQuery query;
            query.prepare(u8"select count(*) from lend where ISBN=:isbn AND ownerid=:oid AND borrowerid=:uid");
            query.bindValue(":isbn",isbn);
            query.bindValue(":oid",oid);
            query.bindValue(":uid",uid);
            if(!query.exec()){
                QMessageBox::warning(0,"Error",QString("Error!\n%1").arg(query.lastError().text()));
            }
            else{
                query.next();
                if(query.value(0)>0){
                    QMessageBox::warning(0,"Warning",u8"该书籍您已借阅，请勿重复借阅！");
                }
                else{ //添加借阅请求记录
                    query.prepare(u8"insert into lend values (:isbn,:oid,:uid,1)");
                    query.bindValue(":isbn",isbn);
                    query.bindValue(":oid",oid);
                    query.bindValue(":uid",uid);
                    if(!query.exec()){
                        QMessageBox::warning(0,"Error",QString("Error!\n%1").arg(query.lastError().text()));
                    }
                    else{
                        QMessageBox::information(0,"Success",u8"申请成功，书主人会尽快审核的~");
                        }
                    QSqlQuery query1;

                    //更改用户借阅数量信息
                    query1.prepare(u8"select * from users where ID=:uid");
                    query1.bindValue(":uid",uid);
                    if(!query1.exec()){
                        QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                    }
                    else{
                        query1.next();
                        int sum=query1.value(4).toInt()+1;
                        query1.prepare(u8"update users set borrow =:sum where ID=:uid");
                        query1.bindValue(":uid",uid);
                        query1.bindValue(":sum",sum);
                        if(!query1.exec()){
                            QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
                        }
                    }
                }

            }

        }

    }
}
