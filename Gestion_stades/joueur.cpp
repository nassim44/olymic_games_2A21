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
QByteArray Joueur::verifier_code_bd(QByteArray data)
{
    QSqlQuery querycode;
    QString nomJoueur = "";

    //if there is a problem remove ligne number 44

    QString Data = QString(data);
    querycode.prepare("SELECT * FROM joueur WHERE CODE_CARTE = :Data");
    querycode.bindValue(":Data",Data);
    querycode.exec();
    if(querycode.next()==false)
    {
        return "code n'existe pas";
    }else
    {
        while(querycode.next()) {
            nomJoueur = querycode.value(5).toString();
        }
        data=nomJoueur.toLocal8Bit();
        return data;
    }

}
