#include "gestion_des_jeux.h"
#include "ui_gestion_des_jeux.h"
#include"jeux.h"
#include <QString>
#include<QDateEdit>
#include <QTabWidget>
#include"jeux.h"
#include"gestion_des_jeux.h"
#include"connection.h"

#include<QMessageBox>
Gestion_des_jeux::Gestion_des_jeux(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestion_des_jeux)
{
    ui->setupUi(this);
}

Gestion_des_jeux::~Gestion_des_jeux()
{
    delete ui;
}



void Gestion_des_jeux::on_pushButton_AJOUTER_clicked()
{
            int ID_JEUX=ui->lineEdit_IDjeux->text().toInt();
            QString NATION=ui->lineEdit_nation->text();
            QString DISCIPLINE=ui->lineEdit_discipline->text();
            QString TYPE_JEUX=ui->lineEdit_IDjeux->text();
            int NBR_JEUX=ui->lineEdit_NBRJ->text().toInt();
   Jeux J( ID_JEUX, NBR_JEUX, TYPE_JEUX, NATION, DISCIPLINE);
   bool test =J.ajouter();
   if(test)
   {
     //  ui->tableView->setModel((etmp.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("Ajout effectué\n"
                                                   "Click Cancel to exit."),QMessageBox::Cancel);
   }
              else
                  QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                           QObject::tr("Ajout non effectué\n"
                                                       "Click Cancel to exit."),QMessageBox::Cancel);




}
