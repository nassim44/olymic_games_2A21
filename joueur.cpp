#include "joueur.h"
#include<QSqlRecord>
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include"joueur.h"
joueur::joueur(int idj,QString nom,QString nais,QString pays,QString specialite)
{
    this->idj=idj;
    this->nom=nom;
    this->nais=nais;
    this->pays=pays;
    this->specialite=specialite;

}
bool joueur::ajouterj()
{
QSqlQuery query;
    //QString id= QString::number(ID);
    query.prepare("INSERT INTO JOUEUR (IDJ,NOM,NAIS,PAYS,SPECIALITE) "
                        "VALUES (:idj, :nom, :nais,:pays ,:specialite)");
    query.bindValue(":idj",idj);
    query.bindValue(":nom",nom);
    query.bindValue(":nais",nais);
    query.bindValue(":pays",pays);
    query.bindValue(":specialite",specialite);



    return    query.exec();

}

QSqlQueryModel * joueur ::afficherj()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from JOUEUR");
  /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("specialite "));*/

        return model;
}

bool joueur::modifierj(int idj, QString nom, QString nais, QString pays, QString specialite)
{

    QSqlQuery query;
//QString idc=QString::number(id);
    query.prepare("UPDATE JOUEUR SET nom= :nom, nais= :nais, pays= :pays, specialite= :specialite where idj= :idj ");
    query.bindValue(":idj", idj);
    query.bindValue(":nom", nom);
    query.bindValue(":nais",nais);
    query.bindValue(":pays",pays);
    query.bindValue(":specialite",specialite);

            return    query.exec();

}
QSqlQueryModel * joueur::afficheroncomboj()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from joueur");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDJ"));

        return model;
}

bool joueur :: supprimerj(int idj)
{

    QSqlQuery query;
    query.prepare("Delete from joueur where idj = :idj ");
    query.bindValue(":idj",idj);
    return    query.exec();

}

bool joueur::ajfichehisto(int idjj)
{QSqlQuery query;
    query.prepare("INSERT INTO tabh (IDJ,NOM,NAIS,PAYS,SPECIALITE) SELECT IDJ,NOM,NAIS,PAYS,SPECIALITE FROM joueur where idj= :idjj "   );

    query.bindValue(":idjj",idj);
    query.bindValue(":nom",nom);
    query.bindValue(":nais",nais);
    query.bindValue(":pays",pays);
    query.bindValue(":specialite",specialite);



    return    query.exec();

}
QSqlQueryModel* joueur::trides()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from joueur order by IDJ DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));



            return model;
}

QSqlQueryModel * joueur::triasc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from joueur order by IDJ ASC");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));

           return model;
}
QSqlQueryModel* joueur::tridesnom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from joueur order by nom DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));



            return model;
}

QSqlQueryModel * joueur::triascnom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from joueur order by nom ASC");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));

           return model;
}

QSqlQueryModel* joueur::tridesnais()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from joueur order by nais DESC");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));



            return model;
}

QSqlQueryModel * joueur::triascnais()
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from joueur order by nais ASC");
      /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));*/

           return model;
}

QSqlQueryModel* joueur::tridespays()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from joueur order by pays DESC");
       /* model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));*/



            return model;
}

QSqlQueryModel * joueur::triascpays()
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from joueur order by pays ASC");
       /*model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("SPECIALITE "));*/

           return model;
}

void joueur::pdf()
{
//    QDateTime datecreation = date.currentDateTime();
//                QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                       QPdfWriter pdf("C:/Users/Admin/Documents/fiche_historique.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Arial", 30));
                           painter.drawText(1100,1200,"Liste Des Joueurs");
                           painter.setPen(Qt::black);
                           painter.setFont(QFont("Arial", 15));
                          // painter.drawText(1100,2000,afficheDC);
                           painter.drawRect(100,100,7300,2600);
                           //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                           painter.drawRect(0,3000,9600,500);
                           painter.setFont(QFont("Arial", 9));
                           painter.drawText(200,3300,"idj");
                           painter.drawText(1300,3300,"nom");
                           painter.drawText(2400,3300,"nais");
                            painter.drawText(3500,3300,"pays");
                             painter.drawText(4600,3300,"specialite");

                           QSqlQuery query;
                           query.prepare("select * from joueur");
                           query.exec();
                           while (query.next())
                           {
                               painter.drawText(200,i,query.value(0).toString());
                               painter.drawText(1300,i,query.value(1).toString());
                               painter.drawText(2400,i,query.value(2).toString());
                               painter.drawText(3500,i,query.value(3).toString());
                               painter.drawText(4600,i,query.value(4).toString());

                              i = i + 500;
}

                           int reponse = QMessageBox::Yes;
                               if (reponse == QMessageBox::Yes)
                               {
                                   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                                   notifyIcon->show();
                                  notifyIcon->setIcon(QIcon("icone.png"));

                                   notifyIcon->showMessage("GESTION DES  JOUEUR ","Liste joueur pret dans PDF",QSystemTrayIcon::Information,15000);

                                   painter.end();
                               }
                               if (reponse == QMessageBox::No)
                               {
                                    painter.end();
                               }
}
QSqlQueryModel* joueur::getidjou()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT IDJ FROM JOUEUR");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}

//joueur* joueur::getjoueur(int id)
//{
//    QSqlQuery query;
//    query.prepare("SELECT * FROM joueur WHERE ID_JOUEUR = :id");
//    query.bindValue(":id",id);
//    query.exec();
//    joueur* jou = new joueur();
//    while (query.next()) {
//            jou->setIdjoueur(query.value(0).toInt());
//            jou->setNomjoueur(query.value(1).toString());
//            jou->setPrenomjoueur(query.value(2).toString());
//            jou->setSpecialite(query.value(3).toString());
//            jou->setPays(query.value(4).toString());
//        }
//    return jou;
//}
