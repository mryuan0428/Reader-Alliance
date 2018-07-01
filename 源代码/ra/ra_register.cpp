#include "ra_register.h"
#include "ui_ra_register.h"

RA_Register::RA_Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_Register)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());

    //设置背景图片
    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":img/img/6.jpg").scaled(// 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);                           // 给widget加上背景图

    QFont font ("Microsoft YaHei", 10, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是50）
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->pushButton->setFont(font);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_pwd_2->setEchoMode(QLineEdit::Password);
    //用户ID只能是数字和大小写字母组合
    QRegExp regx("[a-zA-Z0-9]+$");
    ui->lineEdit_id->setValidator(new QRegExpValidator(regx,this));
}

RA_Register::~RA_Register()
{
    delete ui;
}

void RA_Register::on_pushButton_clicked()
{
    //检查填写信息是否为空
    if((ui->lineEdit_id->text().isEmpty())||(ui->lineEdit_name->text().isEmpty())||(ui->lineEdit_pwd->text().isEmpty())||(ui->lineEdit_pwd_2->text().isEmpty())){
        QMessageBox::warning(0,"Error",u8"请完整填写用户信息！");
    }
    //判断两次输入密码是否相同
    else if(ui->lineEdit_pwd->text()!=ui->lineEdit_pwd_2->text()){
        QMessageBox::warning(0,"Error",u8"两次输入密码不同！");
    }
    //判断ID是否已经被使用
    else{
        QSqlQuery query;
        query.prepare(u8"select count(*) from users where ID=:uid");
        query.bindValue(":uid",ui->lineEdit_id->text());
        if(!query.exec()){
            QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query.lastError().text()));
        }
        else{
            query.next();
            if(query.value(0).toInt()==1){
                QMessageBox::warning(0,"Error",u8"用户ID已被使用，请更改。");
            }
            else{
                QSqlQuery query;
                query.prepare(u8"select count(*) from register where ID=:uid");
                query.bindValue(":uid",ui->lineEdit_id->text());
                if(!query.exec()){
                    QMessageBox::warning(0,"Error",QString("Wrong!\n%1").arg(query.lastError().text()));
                }
                else{
                    query.next();
                    if(query.value(0).toInt()==1){
                        QMessageBox::warning(0,"Error",u8"用户ID已申请注册，请等待管理员审核。");
                    }
                    //插入新的数据
                    else{
                        query.prepare(u8"insert into register values (:uid,:upwd,:uname)");
                        query.bindValue(":uid",ui->lineEdit_id->text());
                        query.bindValue(":upwd",ui->lineEdit_pwd->text());
                        query.bindValue(":uname",ui->lineEdit_name->text());
                        if(!query.exec()){
                            QMessageBox::warning(0,"Error",QString("Error!\n%1").arg(query.lastError().text()));
                        }
                        else{
                            QMessageBox::information(0,"Success",u8"注册申请成功，请等待管理员审核!");
                            this->close();
                            }
                    }
                }
            }
        }
    }
}
