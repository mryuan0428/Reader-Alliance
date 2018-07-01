#include "ra_userman.h"
#include "ui_ra_userman.h"

RA_UserMan::RA_UserMan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_UserMan)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/12.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->comboBox->setFont(font);
    ui->tableView->setFont(font);

    //信息显示
    QSqlQueryModel *model = new QSqlQueryModel;
    QString querystr=QString("select * from users");
    model->setQuery(querystr);//这里直接设置SQL语句，忽略最后一个参数
    ui->tableView->setModel(model);

    //以下是视觉方面的效果，不加也没影响
    //隔行变色
    ui->tableView->setAlternatingRowColors(true);

    //设置行高
    int row_count = model->rowCount();
    for(int i =0; i < row_count; i++)
    {
        ui->tableView->setRowHeight(i, 25);
    }
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,70);

    //comobox的iterm添加
    QSqlQuery query;
    query.prepare(u8"select ID from users");
    if(!query.exec())
    {
        QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
    }
    else{
        while(query.next()){
            ui->comboBox->addItem(query.value(0).toString());
        }
    }
}

RA_UserMan::~RA_UserMan()
{
    delete ui;
}

void RA_UserMan::on_pushButton_clicked()
{
    QString oid=ui->comboBox->currentText();
    if((ui->checkBox->isChecked()==true)&&(ui->lineEdit->text().isEmpty()!=true)){
        g=1;
        QSqlQuery query;
        query.prepare(u8"update users set name=:name where ID=:oid");
        query.bindValue(":oid",oid);
        query.bindValue(":name",ui->lineEdit->text());
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
        }
        else{QMessageBox::information(0,"Success",u8"姓名更改成功~");}
    }
    if((ui->checkBox_2->isChecked()==true)&&(ui->lineEdit_2->text().isEmpty()!=true)){
        g=2;
        QSqlQuery query;
        query.prepare(u8"update users set pwd=:pwd where ID=:oid");
        query.bindValue(":oid",oid);
        query.bindValue(":pwd",ui->lineEdit_2->text());
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
        }
        else{QMessageBox::information(0,"Success",u8"密码更改成功~");}
    }
    if((ui->checkBox_3->isChecked()==true)&&(ui->lineEdit_3->text().isEmpty()!=true)){
        g=3;
        QSqlQuery query;
        query.prepare(u8"update users set share=:sh where ID=:oid");
        query.bindValue(":oid",oid);
        query.bindValue(":sh",ui->lineEdit_3->text());
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
        }
        else{QMessageBox::information(0,"Success",u8"分享数量更改成功~");}
    }
    if((ui->checkBox_4->isChecked()==true)&&(ui->lineEdit_4->text().isEmpty()!=true)){
        g=4;
        QSqlQuery query;
        query.prepare(u8"update users set borrow=:bw where ID=:oid");
        query.bindValue(":oid",oid);
        query.bindValue(":bw",ui->lineEdit_4->text());
        if(!query.exec())
        {
            QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
        }
        else{QMessageBox::information(0,"Success",u8"借阅数量更改成功~");}
    }
    if(g==-1){
        QMessageBox::warning(0,"Error",QString(u8"用户信息修改失败\n请检查内容填写是否完整及复选框是否勾选"));
    }
}
