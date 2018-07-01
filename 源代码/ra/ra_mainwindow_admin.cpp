#include "ra_mainwindow_admin.h"
#include "ui_ra_mainwindow_admin.h"

extern QString BookName; //书名，作为传递参数

RA_MainWindow_Admin::RA_MainWindow_Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RA_MainWindow_Admin)
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

RA_MainWindow_Admin::~RA_MainWindow_Admin()
{
    delete ui;
}

void RA_MainWindow_Admin::on_pushButton_clicked()
{
    //查询书籍详细信息并新建dialog窗口显示
    BookName=ui->comboBox->currentText();
    dialog= new RA_BookInfo(this);
    dialog->setWindowTitle(u8"书籍信息");
    dialog->show();
}

void RA_MainWindow_Admin::on_actionRegMan_triggered()
{
    //注册管理窗口显示
    dialog_rm= new RA_RegMan(this);
    dialog_rm->setAttribute(Qt::WA_DeleteOnClose);
    dialog_rm->setWindowTitle(u8"注册管理");
    dialog_rm->show();
}

void RA_MainWindow_Admin::on_actionBookMan_triggered()
{
    //书籍管理窗口显示
    dialog_bm= new RA_BookMan(this);
    dialog_bm->setAttribute(Qt::WA_DeleteOnClose);
    dialog_bm->setWindowTitle(u8"书籍管理");
    dialog_bm->show();
}

void RA_MainWindow_Admin::on_actionActivityMan_triggered()
{
    //活动管理窗口显示
    dialog_am= new RA_ActivityMan(this);
    dialog_am->setAttribute(Qt::WA_DeleteOnClose);
    dialog_am->setWindowTitle(u8"活动管理");
    dialog_am->show();
}

void RA_MainWindow_Admin::on_actionUserMan_triggered()
{
    //用户管理窗口显示
    dialog_um= new RA_UserMan(this);
    dialog_um->setAttribute(Qt::WA_DeleteOnClose);
    dialog_um->setWindowTitle(u8"用户管理");
    dialog_um->show();
}
