#include "ra_mainwindow.h"
#include <QApplication>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QString>

void OpenDatabase();

int who=0;//身份表示，0：游客;1：用户;2：管理员。
QString uid;
QString upwd;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenDatabase();
    RA_MainWindow w;
    w.setWindowTitle("Reader Alliance");
    w.show();

    return a.exec();
}

//打开本地数据库
void OpenDatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;"  //服务器名称
                               "DATABASE=%2;"//数据库名
                               "UID=%3;"     //登录名
                               "PWD=%4;"     //密码
                               ).arg("rm-bp123v39eso83qfqlbo.sqlserver.rds.aliyuncs.com,3433")//阿里云数据库
                                .arg("ra")
                                .arg("luyeluye111")
                                .arg("Luye1997")
                       );
    if (!db.open()) //打开失败弹窗提示
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              db.lastError().databaseText(), QMessageBox::Cancel);

    }
}
