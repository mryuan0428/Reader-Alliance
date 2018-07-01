#include "ra_mainwindow.h"
#include "ui_ra_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>

QString BookName;//书名，作为传递参数

RA_MainWindow::RA_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RA_MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/1.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图
    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->comboBox->setFont(font);
    ui->pushButton->setFont(font);

    //查询数据库中现有的分享书籍并在主页展示
    QSqlQuery query;
    query.exec("select * from book");
    int count=1;

    while(query.next())
    {
        QByteArray picture=query.value(4).toByteArray();
        QPixmap outimage;
        outimage.loadFromData(picture);
        outimage=outimage.scaled(199,249,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        switch(count) {
           case 1: ui->label_1_1->setPixmap(outimage);
                   ui->label_1_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_1_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 2: ui->label_2_1->setPixmap(outimage);
                   ui->label_2_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_2_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 3: ui->label_3_1->setPixmap(outimage);
                   ui->label_3_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_3_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 4: ui->label_4_1->setPixmap(outimage);
                   ui->label_4_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_4_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 5: ui->label_5_1->setPixmap(outimage);
                   ui->label_5_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_5_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 6: ui->label_6_1->setPixmap(outimage);
                   ui->label_6_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_6_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 7: ui->label_7_1->setPixmap(outimage);
                   ui->label_7_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_7_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           case 8: ui->label_8_1->setPixmap(outimage);
                   ui->label_8_2->setText(QString(u8"《%1》").arg(query.value(1).toString()));
                   ui->label_8_3->setText(QString(u8"作者：%1").arg(query.value(2).toString()));
                   break;
           default: break;
           }
        if(count>=8) break;
        else count++;
    }

    //comobox的iterm添加
    query.exec("select * from book");
    while(query.next()){
        ui->comboBox->addItem(query.value(1).toString());
    }

}

RA_MainWindow::~RA_MainWindow()
{
    delete ui;
}

void RA_MainWindow::on_pushButton_clicked()
{
    //查询书籍详细信息并新建dialog窗口显示
    BookName=ui->comboBox->currentText();
    dialog= new RA_BookInfo(this);
    dialog->setWindowTitle(u8"书籍信息");
    dialog->show();
}

void RA_MainWindow::on_actionLogin_triggered()
{
    //登录窗口显示
    dialog_login= new RA_Login(this);
    dialog_login->setAttribute(Qt::WA_DeleteOnClose);
    dialog_login->setWindowTitle(u8"登录");
    dialog_login->show();
    connect(dialog_login,SIGNAL(destroyed()),this,SLOT(check()));
}

void RA_MainWindow::on_actionRegister_triggered()
{
    //注册窗口显示
    dialog_register= new RA_Register(this);
    dialog_register->setAttribute(Qt::WA_DeleteOnClose);
    dialog_register->setWindowTitle(u8"注册");
    dialog_register->show();
}

void RA_MainWindow::on_actionActivity_triggered()
{ //线下活动显示
    dialog_acticity= new RA_Activity(this);
    dialog_acticity->setAttribute(Qt::WA_DeleteOnClose);
    dialog_acticity->setWindowTitle(u8"线下活动");
    dialog_acticity->show();
}

void RA_MainWindow::check(){
    if (who!=0) {
        this->close();
    }
}
