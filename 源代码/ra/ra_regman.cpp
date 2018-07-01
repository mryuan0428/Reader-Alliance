#include "ra_regman.h"
#include "ui_ra_regman.h"
#include <QSqlQueryModel>

RA_RegMan::RA_RegMan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_RegMan)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/9.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->comboBox->setFont(font);
    ui->pushButton->setFont(font);
    ui->tableView->setFont((font));

    //信息显示
    QSqlQueryModel *model = new QSqlQueryModel;
    QString querystr=QString("select * from register");
    model->setQuery(querystr);//这里直接设置SQL语句，忽略最后一个参数
    ui->tableView->setModel(model);

    //以下是视觉方面的效果，不加也没影响
    //隔行变色
    ui->tableView->setAlternatingRowColors(true);

    //设置行高
    int row_count = model->rowCount();
    for(int i =0; i < row_count; i++)
    {
        ui->tableView->setRowHeight(i, 30);
    }
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->setColumnWidth(2,120);

    //comobox的iterm添加
    QSqlQuery query;
    query.prepare(u8"select ID from register");
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

RA_RegMan::~RA_RegMan()
{
    delete ui;
}

void RA_RegMan::on_pushButton_clicked()
{
    //新添加用户，删去注册申请
    QSqlQuery query;
    query.prepare(u8"select * from register where ID=:uid");
    query.bindValue(":uid",ui->comboBox->currentText());
    if(!query.exec()){
        QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query.lastError().text()));
    }
    else{
        query.next();
        QSqlQuery query1;
        query1.prepare(u8"insert into users values(:id,:name,:pwd,0,0)");
        query1.bindValue(":id",ui->comboBox->currentText());
        query1.bindValue(":name",query.value(2));
        query1.bindValue(":pwd",query.value(1));
        if(!query1.exec()){
            QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query1.lastError().text()));
        }
        else{
            QSqlQuery query2;
            query2.prepare(u8"delete from register where ID=:id");
            query2.bindValue(":id",ui->comboBox->currentText());
            if(!query2.exec()){
                QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query2.lastError().text()));
            }
            else{
                QMessageBox::information(0,"Success",u8"注册申请审核通过，新用户已创建");
            }

        }
    }
}
