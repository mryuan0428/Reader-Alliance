#include "ra_login.h"
#include "ui_ra_login.h"

RA_Login::RA_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_Login)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/7.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->lineEdit_id->setFont(font);
    ui->pushButton->setFont(font);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

RA_Login::~RA_Login()
{
    delete ui;
}

void RA_Login::on_pushButton_clicked()
{
    uid=ui->lineEdit_id->text();
    upwd=ui->lineEdit_pwd->text();
    QSqlQuery query;
    query.prepare(u8"select count(*) from users where ID=:uid AND pwd=:upwd");
    query.bindValue(":uid",uid);
    query.bindValue(":upwd",upwd);
    if(!query.exec())
    {
        QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query.lastError().text()));
    }
    else{
        query.next();
        if(query.value(0).toInt()==1){
            who=1;
            dialog= new RA_MainWindow_User(0);
            dialog->setWindowTitle(u8"Reader Alliance");
            dialog->show();
            this->close();
        }
        else {
            query.prepare(u8"select count(*) from admin where ID=:uid AND pwd=:upwd");
            query.bindValue(":uid",uid);
            query.bindValue(":upwd",upwd);
            if(!query.exec()){
                QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query.lastError().text()));
            }
            else{
                query.next();
                if(query.value(0).toInt()==1){
                    who=2;
                    dialog_a= new RA_MainWindow_Admin(0);
                    dialog_a->setWindowTitle(u8"管理平台");
                    dialog_a->show();
                    this->close();
                }
                else QMessageBox::warning(0,"Error",u8"请输入正确的ID和密码！");
            }
        }
    }
}
