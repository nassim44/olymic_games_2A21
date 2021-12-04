#include "admin.h"
#include "ui_admin.h"
#include<QMessageBox>
#include"gestion_des_jeux.h"
admin::admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
  //---------------------------------------------------

    //---------------------------------------------------


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
    QString USERNAME=ui->lineEdit_username->text();
    QString PASSWORD=ui->lineEdit_password->text();
    if((USERNAME=="fedi")&&(PASSWORD=="0000"))
    {
    W.show();
    W.exec();
    }

}
