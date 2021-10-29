#include "joueur.h"

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
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idj"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nais "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("pays "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("specialite "));

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

bool joueur :: supprimerj(int id)
{QSqlQuery query;
    //QString ident1= QString ::number(id);

    query.prepare("Delete from joueur where idj = :id ");
    query.bindValue(":id",idj);
    return    query.exec();

}

