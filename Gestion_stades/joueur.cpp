#include "joueur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QList>
Joueur::Joueur()
{
    id_joueur=0;Nom_joueur="";Prenom_joueur="";specialite="";pays="";
}
QSqlQueryModel* Joueur::getidjou()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_Joueur FROM joueur");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}

Joueur* Joueur::getjoueur(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM joueur WHERE ID_JOUEUR = :id");
    query.bindValue(":id",id);
    query.exec();
    Joueur* jou = new Joueur();
    while (query.next()) {
            jou->setIdjoueur(query.value(0).toInt());
            jou->setNomjoueur(query.value(1).toString());
            jou->setPrenomjoueur(query.value(2).toString());
            jou->setSpecialite(query.value(3).toString());
            jou->setPays(query.value(4).toString());
        }
    return jou;
}
