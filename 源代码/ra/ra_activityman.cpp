#include "ra_activityman.h"
#include "ui_ra_activityman.h"

RA_ActivityMan::RA_ActivityMan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_ActivityMan)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/4.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);

    //信息显示
    ui->tabWidget->clear();
    QSqlQuery query;
    query.prepare(u8"select * from activity");

    if(!query.exec()){
        QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
    }
    else{
        while(query.next()){
            //查询活动发起人name
            QSqlQuery queryusr;
            queryusr.prepare(u8"select name from users where ID = :usid");
            queryusr.bindValue(":usid",query.value(0).toString());
            if(!queryusr.exec()){
                QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(queryusr.lastError().text()));
            }
            else{
                queryusr.next();
                QLabel *l=new QLabel(u8"活动名称："+query.value(1).toString()+"\n\n"+u8"活动发起人："+queryusr.value(0).toString()+"\n\n"+u8"活动时间："+query.value(2).toString()+"\n\n"+u8"活动描述：\n"+query.value(3).toString());
                QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
                l->setFont(font);
                l->setGeometry(QRect(328, 240, 329, 27*4)); //四倍行距
                l->setWordWrap(true);
                l->setAlignment(Qt::AlignTop);
                ui->tabWidget->addTab(l,query.value(1).toString());
            }
        }
    }

    //comobox的iterm添加
    query.prepare(u8"select name,ownerid from activity");
    if(!query.exec())
    {
        QMessageBox::warning(0,"Error",QString("Fail to select\n%1").arg(query.lastError().text()));
    }
    else{
        while(query.next()){
            ui->comboBox->addItem(query.value(0).toString()+"  By:"+query.value(1).toString());
        }
    }

}

RA_ActivityMan::~RA_ActivityMan()
{
    delete ui;
}

void RA_ActivityMan::on_pushButton_clicked()
{
    //正则表达式提取信息
    QString name;
    QString oid;

    QString pattern("(.*)  By:(.*)");
    QRegExp rx(pattern);
    QString msg=ui->comboBox->currentText();
    int pos=msg.indexOf(rx);
    if(pos>=0){
        name=rx.cap(1);
        oid=rx.cap(2);

        //更新信息
        if((ui->checkBox->isChecked()==true)&&(ui->lineEdit->text().isEmpty()!=true)){
            g=1;
            QSqlQuery query;
            query.prepare(u8"update activity set name=:name0 where name=:name AND ownerid=:oid");
            query.bindValue(":name",name);
            query.bindValue(":oid",oid);
            query.bindValue(":name0",ui->lineEdit->text());
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"活动名称更改成功~");}
        }
        if((ui->checkBox_2->isChecked()==true)&&(ui->dateEdit->date()>=QDate::currentDate())){
            g=2;
            QSqlQuery query;
            query.prepare(u8"update activity set date=:date where name=:name AND ownerid=:oid");
            query.bindValue(":name",name);
            query.bindValue(":oid",oid);
            query.bindValue(":date",ui->dateEdit->date().toString("yyyy-MM-dd"));
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"活动时间更改成功~");}
        }
        if((ui->checkBox_3->isChecked()==true)&&(ui->textEdit->toPlainText().isEmpty()!=true)){
            g=3;
            QSqlQuery query;
            query.prepare(u8"update activity set description=:des where name=:name AND ownerid=:oid");
            query.bindValue(":name",name);
            query.bindValue(":oid",oid);
            query.bindValue(":des",ui->textEdit->toPlainText());
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"活动描述更改成功~");}
        }
        if(g==-1){
            QMessageBox::warning(0,"Error",QString(u8"活动信息修改失败\n请检查内容填写是否完整及复选框是否勾选"));
        }
    }
}
