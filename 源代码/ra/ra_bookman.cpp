#include "ra_bookman.h"
#include "ui_ra_bookman.h"

RA_BookMan::RA_BookMan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_BookMan)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/5.jpg").scaled(// 缩放背景图.
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
    QString querystr=QString("select ISBN,name,author,ownerid,num from book");
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
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,130);
    ui->tableView->setColumnWidth(2,120);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,60);

    //comobox的iterm添加
    QSqlQuery query;
    query.prepare(u8"select ISBN,ownerid from book");
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

RA_BookMan::~RA_BookMan()
{
    delete ui;
}

void RA_BookMan::on_pushButton_2_clicked()
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
            }

        }
}

void RA_BookMan::on_pushButton_clicked()
{
    //正则表达式提取信息
    QString isbn;
    QString oid;

    QString pattern("(.*)  By:(.*)");
    QRegExp rx(pattern);
    QString msg=ui->comboBox->currentText();
    int pos=msg.indexOf(rx);
    if(pos>=0){
        isbn=rx.cap(1);
        oid=rx.cap(2);

        //更新信息
        if((ui->checkBox->isChecked()==true)&&(ui->lineEdit->text().isEmpty()!=true)){
            g=1;
            QSqlQuery query;
            query.prepare(u8"update book set name=:name where ISBN=:isbn AND ownerid=:oid");
            query.bindValue(":isbn",isbn);
            query.bindValue(":oid",oid);
            query.bindValue(":name",ui->lineEdit->text());
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"书名更改成功~");}
        }
        if((ui->checkBox_2->isChecked()==true)&&(ui->lineEdit_2->text().isEmpty()!=true)){
            g=2;
            QSqlQuery query;
            query.prepare(u8"update book set author=:author where ISBN=:isbn AND ownerid=:oid");
            query.bindValue(":isbn",isbn);
            query.bindValue(":oid",oid);
            query.bindValue(":author",ui->lineEdit_2->text());
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"作者更改成功~");}
        }
        if((ui->checkBox_3->isChecked()==true)&&(ui->lineEdit_3->text().isEmpty()!=true)){
            g=3;
            QSqlQuery query;
            query.prepare(u8"update book set num=:num where ISBN=:isbn AND ownerid=:oid");
            query.bindValue(":isbn",isbn);
            query.bindValue(":oid",oid);
            query.bindValue(":num",ui->lineEdit_3->text());
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"数量更改成功~");}
        }
        if((ui->checkBox_4->isChecked()==true)&&(flag==1)){
            g=4;
            QSqlQuery query;
            query.prepare(u8"update book set picture=:pic where ISBN=:isbn AND ownerid=:oid");
            query.bindValue(":isbn",isbn);
            query.bindValue(":oid",oid);
            query.bindValue(":pic",inByteArray);
            if(!query.exec())
            {
                QMessageBox::warning(0,"Error",QString("Fail\n%1").arg(query.lastError().text()));
            }
            else{QMessageBox::information(0,"Success",u8"图片更改成功~");}
        }
        if(g==-1){
            QMessageBox::warning(0,"Error",QString(u8"书籍信息修改失败\n请检查内容填写是否完整及复选框是否勾选"));
        }
    }

}
