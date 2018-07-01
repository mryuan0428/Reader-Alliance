#include "ra_usercenter.h"
#include "ui_ra_usercenter.h"
#include <QSqlQueryModel>
#include <QRegExp>

RA_UserCenter::RA_UserCenter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_UserCenter)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/11.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    //字体设置
    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    ui->label_8->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->pushButton->setFont(font);
    ui->comboBox->setFont(font);
    ui->comboBox_2->setFont(font);
    ui->tableView->setFont(font);
    ui->tableView_2->setFont(font);

    //基本信息显示
    QSqlQuery query;
    query.prepare(u8"select * from users where ID=:uid");
    query.bindValue(":uid",uid);
    if(!query.exec())
    {
        QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
    }
    else{
        query.next();
        ui->label_2->setText(QString(u8"%1").arg(query.value(0).toString()));
        ui->label_4->setText(QString(u8"%1").arg(query.value(1).toString()));
        ui->label_6->setText(QString(u8"%1").arg(query.value(3).toString()));
        ui->label_8->setText(QString(u8"%1").arg(query.value(4).toString()));

        //处理借阅请求显示
        QSqlQueryModel *model = new QSqlQueryModel;
        QString querystr=QString("select ISBN,borrowerid from lend where ownerid='%1' AND status=1").arg(uid);
        model->setQuery(querystr);//这里直接设置SQL语句，忽略最后一个参数
        ui->tableView->setModel(model);

        //以下是视觉方面的效果，不加也没影响
        //隔行变色
        ui->tableView->setAlternatingRowColors(true);

        //设置行高
        int row_count = model->rowCount();
        for(int i =0; i < row_count; i++)
        {
            ui->tableView->setRowHeight(i, 20);
        }
        ui->tableView->setColumnWidth(0,125);

        //comobox的iterm添加
        query.prepare(u8"select * from lend where ownerid=:uid AND status=1");
        query.bindValue(":uid",uid);
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
        }
        else{
            while(query.next()){
                ui->comboBox->addItem(query.value(2).toString()+" wanted "+query.value(0).toString());
            }
        }

        //处理归还请求显示
        QSqlQueryModel *model2 = new QSqlQueryModel;
        QString querystr2=QString("select ISBN,borrowerid from lend where ownerid='%1' AND status=0").arg(uid);
        model2->setQuery(querystr2);//这里直接设置SQL语句，忽略最后一个参数
        ui->tableView_2->setModel(model2);

        //以下是视觉方面的效果，不加也没影响
        //隔行变色
        ui->tableView_2->setAlternatingRowColors(true);

        //设置行高
        row_count = model->rowCount();
        for(int i =0; i < row_count; i++)
        {
            ui->tableView_2->setRowHeight(i, 20);
        }
        ui->tableView_2->setColumnWidth(0,125);

        //comobox的iterm添加
        query.prepare(u8"select * from lend where ownerid=:uid AND status=0");
        query.bindValue(":uid",uid);
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
        }
        else{
            while(query.next()){
                ui->comboBox_2->addItem(query.value(2).toString()+" returned "+query.value(0).toString());
            }
        }
    }
}

RA_UserCenter::~RA_UserCenter()
{
    delete ui;
}

void RA_UserCenter::on_pushButton_clicked()
{
    //正则表达式提取信息
    QString isbn;
    QString bid;

    QString pattern("(.*) wanted (.*)");
    QRegExp rx(pattern);
    QString msg=ui->comboBox->currentText();
    int pos=msg.indexOf(rx);
    if(pos>=0){
        bid=rx.cap(1);
        isbn=rx.cap(2);
        //更新借阅信息
        QSqlQuery query1;
        query1.prepare(u8"update lend set status=0 where ISBN= :isbn AND ownerid=:uid AND borrowerid =:bid");
        query1.bindValue(":isbn",isbn);
        query1.bindValue(":uid",uid);
        query1.bindValue(":bid",bid);
        if(!query1.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query1.lastError().text()));
        }
        else{
            QMessageBox::information(0,"Success",u8"借阅请求处理成功~");
            }
    }

}

void RA_UserCenter::on_pushButton_2_clicked()
{
    //正则表达式提取信息
    QString isbn;
    QString bid;

    QString pattern("(.*) returned (.*)");
    QRegExp rx(pattern);
    QString msg=ui->comboBox_2->currentText();
    int pos=msg.indexOf(rx);
    if(pos>=0){
        bid=rx.cap(1);
        isbn=rx.cap(2);
        //更新借阅信息
        QSqlQuery query1;
        query1.prepare(u8"delete from lend where ISBN= :isbn AND ownerid=:uid AND borrowerid =:bid AND status=0");
        query1.bindValue(":isbn",isbn);
        query1.bindValue(":uid",uid);
        query1.bindValue(":bid",bid);
        if(!query1.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query1.lastError().text()));
        }
        else{
            QMessageBox::information(0,"Success",u8"书籍归还处理成功~");
            }
    }
}
