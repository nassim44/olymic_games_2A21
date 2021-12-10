#include "admin.h"
#include "ui_admin.h"
#include<QMessageBox>
#include"gestion_des_jeux.h"
#include"mainwindow.h"
#include"gestion_des_stades.h"
#include"ui_gestion_des_stades.h"
admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
   //-----------annimer le bouton authentifier----------------------------------------
//    animation =new QPropertyAnimation(ui->pushButton_admin ,"geometry");
//    animation->setDuration(1000);
//    animation->setStartValue(ui->pushButton_admin->geometry());
//    animation->setEndValue(QRect(50,40,100,50));
//    animation->start();
    //---------------------------------------------------
    animation1 =new QPropertyAnimation(ui->lineEdit_username ,"geometry");
    animation1->setDuration(1000);
    animation1->setStartValue(ui->lineEdit_username->geometry());
    animation1->setEndValue(QRect(200,100,100,50));
    animation1->start();
    //---------------------------------------------------
    animation2 =new QPropertyAnimation(ui->lineEdit_password ,"geometry");
    animation2->setDuration(1000);
    animation2->setStartValue(ui->lineEdit_password->geometry());
    animation2->setEndValue(QRect(200,200,100,50));
    animation2->start();
}
admin::~admin()
{
    delete ui;
}




/*bool admin::on_pushButton_authentifier_clicked()
{
   // bool test=false;
    QString USERNAME=ui->lineEdit_username->text();
    QString PASSWORD=ui->lineEdit_password->text();
    connOpen();
    QSqlQuery query;
    query.prepare("select * from ADMIN where USERNAME=:USERNAME and PASSWORD=:PASSWORD");
    query.bindValue(":USERNAME",USERNAME);
    query.bindValue(":PASSWORD",PASSWORD);
    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }
    if(total==1){
        return true;
    }
    else{
        return false;
    }
}*/


void admin::on_pushButton_admin_clicked()
{
    Gestion_des_jeux W;
    MainWindow M;
    admin A;

    //gestion_des_stades GST;

    QString USERNAME=ui->lineEdit_username->text();
    QString PASSWORD=ui->lineEdit_password->text();
    if((USERNAME=="fedi")&&(PASSWORD=="0000"))
    {
    M.show();
    W.show();
    W.exec();
    A.hide();
    }
}


void admin::on_pushButton_clicked()
{
    QString USERNAME=ui->lineEdit_username->text();
    QString PASSWORD=ui->lineEdit_password->text();
    if((USERNAME=="NASSIM")&&(PASSWORD=="1111"))
    {
        GT=new gestion_des_stades(this);
        GT->show();
    }
}
