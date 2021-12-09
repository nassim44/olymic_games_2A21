
#include "joueur.h"
#include <QFileDialog>
#include <QtDebug>
#include<QPainter>
#include<QPdfWriter>
#include <QFile>
#include<QMessageBox>
#include"gestion_des_joueurs.h"
#include"ui_gestion_des_joueurs.h"

#include<QDesktopServices>
#include "historique.h"
//#include<QPrinter>

Gestion_des_joueurs::Gestion_des_joueurs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gestion_des_joueurs)
{
    ui->setupUi(this);

    ui->lineEditja->setValidator(new QIntValidator(0,999999,this));

         ui->tableViewja->setModel(j.afficherj());
          ui->tableViewja_2->setModel(j.afficherj());
         ui->combosupj->setModel(j.afficheroncomboj());
}

//destructeur
Gestion_des_joueurs::~Gestion_des_joueurs()
{
    delete ui;

}


void Gestion_des_joueurs::on_pushButtonajouterjou_clicked()
{
    joueur j(ui->lineEditja->text().toInt(),ui->lineEdit_nomja->text(),ui->dateEditja->text(),ui->combopaysja->currentText(),ui->combospja->currentText());
       bool test= j.ajouterj();
       ui->tableViewja->setModel(j.afficherj());
        ui->tableViewja_2->setModel(j.afficherj());
               ui->combosupj->setModel(j.afficheroncomboj());

               Historique h;
                 h.save("ID joueur:"+ui->lineEditja->text(),"nom :"+ui->lineEdit_nomja->text(),"pays:"+ui->combopaysja->currentText());

}

void Gestion_des_joueurs::on_pushButtonajouterjou_2_clicked()
{
    bool    test=j.modifierj(ui->lineEditja->text().toInt(),ui->lineEdit_nomja->text(),ui->dateEditja->text(),ui->combopaysja->currentText(),ui->combospja->currentText()) ;
       ui->tableViewja->setModel(j.afficherj());
       ui->tableViewja_2->setModel(j.afficherj());
    if (test)
          {
                  ui->tableViewja->setModel(j.afficherj());
                          ui->combosupj->setModel(j.afficheroncomboj());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void Gestion_des_joueurs::on_combosupj_currentIndexChanged(int index)
{
    ui->combosupj->currentText();
}

void Gestion_des_joueurs::on_pushButton_4_clicked()
{  bool testt=j.ajfichehisto(ui->lineEdit_SUP->text().toInt());
    bool test=j.supprimerj(ui->lineEdit_SUP->text().toInt());
    ui->tableViewja_2->setModel(j.afficherj());

    if(test)
    {
        ui->tableViewja->setModel(j.afficherj());//actualisation taa afficher
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("suppression succful .\n"),
                    QMessageBox::Cancel);
        }

        else
            QMessageBox::critical(nullptr,QObject::tr("supprimer not open"),
                                    QObject::tr("click cancel to exist"),
                                    QMessageBox::Cancel);
}

void Gestion_des_joueurs::on_pushButton_clicked()//boutton fiche historique
{
    //bool test=j.ajfichehisto(ui->lineEdit_SUP->text().toInt());


    QString link="C:/Users/Admin/Desktop/gestion_joueurs/his.txt";
        QDesktopServices::openUrl(QUrl(link));


}

void Gestion_des_joueurs::on_lineEdit_recherhche_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
            QSqlQuery   *query= new QSqlQuery();
    if(ui->cobo_crit->currentText()=="IDJ"
            ){
        query->prepare("SELECT * FROM JOUEUR WHERE IDJ LIKE'"+arg1+"%'");//
query->exec();
    model->setQuery(*query);
 ui->tableViewja_2->setModel(model);


    }
    else {
        if(ui->cobo_crit->currentText()=="pays"){
            query->prepare("SELECT * FROM JOUEUR WHERE pays LIKE'"+arg1+"%'");//+tri
    query->exec();
        model->setQuery(*query);
   ui->tableViewja_2->setModel(model);
        }
        else{
            if(ui->cobo_crit->currentText()=="NAIS")
                query->prepare("SELECT * FROM JOUEUR WHERE NAIS LIKE'"+arg1+"%'");//+tri
        query->exec();
            model->setQuery(*query);
        ui->tableViewja_2->setModel(model);
            }

        }
}

void Gestion_des_joueurs::on_pushButton_tri_clicked()
{
    joueur *j =new  joueur(ui->lineEditja->text().toInt(),ui->lineEdit_nomja->text(),ui->dateEditja->text(),ui->combopaysja->currentText(),ui->combospja->currentText());
    if(ui->asc->isChecked())
    {
        if((ui->cobo_crit->currentText()=="IDJ"))

            {
       ui->tableViewja_2->setModel(j->triasc());

            }
            else if(ui->cobo_crit->currentText()=="nom")
            {

                 ui->tableViewja_2->setModel(j->triascnom());

            }
            else if (ui->cobo_crit->currentText()=="pays")
            {
                 ui->tableViewja_2->setModel(j->triascpays());
            }

     }
    if(ui->desc->isChecked()){
        ui->tableViewja_2->setModel(j->trides());    }
    delete j;
}

//void Gestion_des_joueurs::on_pushButton_2_clicked()
//{
//    QPrinter  printer;
//    printer.setPrinterName("test");
//    QPrintDialog dialog(&printer,this);
//    if (dialog.exec()==QDialog::Rejected) return;
//}

void Gestion_des_joueurs::on_pushButton_3_clicked()
{
 j.pdf();
 //C:\Users\Admin\Documents\fiche_historique.pdf
 QString link="C:/Users/Admin/Documents/fiche_historique.pdf";
     QDesktopServices::openUrl(QUrl(link));
}

//void Gestion_des_joueurs::on_pushButton_5_clicked()
//{
//    stat_j=new statj(this);
//    stat_j->show();
//}

void Gestion_des_joueurs::on_historique_clicked()
{
    Historique h;
    h.load();
    h.load();
}
