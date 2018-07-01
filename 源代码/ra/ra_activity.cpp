#include "ra_activity.h"
#include "ui_ra_activity.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QString>
#include <QSqlError>
#include <QtWidgets/QtWidgets>


RA_Activity::RA_Activity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RA_Activity)
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

    //线下活动显示实现
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

}

RA_Activity::~RA_Activity()
{
    delete ui;
}
