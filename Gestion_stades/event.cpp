#include "event.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
Event::Event()
{
    id_event=0;
    id_stade=0;
    id_jeux=0;
}
Event::Event(int id_event,int id_stade,int id_jeux,QDateTime date)
{
    this->id_event=id_event;
    this->id_stade=id_stade;
    this->id_jeux=id_jeux;
    this->date=date;
}
QString Event::ajouterevent()
{
    QSqlQuery queryStade;
    QSqlQuery queryJeu;
    QSqlQuery queryDateExiste;
    QSqlQuery queryInsert;
    QString idEvent = QString::number(id_event);
    QString idStade = QString::number(id_stade);
    QString idJeux = QString::number(id_jeux);
    QString typeStade = "";
    QString typeJeu = "";

    //Get type stade
    queryStade.prepare("SELECT * FROM stade WHERE ID_STADE = :id");
    queryStade.bindValue(":id",idStade);
    queryStade.exec();
    while(queryStade.next()) {
        typeStade = queryStade.value(2).toString();
    }

    //Get type jeu
    queryJeu.prepare("SELECT * FROM jeux WHERE ID_JEUX = :id");
    queryJeu.bindValue(":id",idJeux);
    queryJeu.exec();
    while(queryJeu.next()) {
        typeJeu = queryJeu.value(1).toString();
    }

    //Check if stade is available
    queryDateExiste.prepare("SELECT * FROM event WHERE ID_STADE = :id AND DATE_EVENT = :date");
    queryDateExiste.bindValue(":id",idStade);
    queryDateExiste.bindValue(":date",date.toString("dd-MM-yyyy hh:mm"));
    queryDateExiste.exec();
    if(QString::compare(typeStade,typeJeu,Qt::CaseInsensitive) == 0) {
        if(queryDateExiste.next() == false) {
            queryInsert.prepare("INSERT INTO event (ID_EVENT,ID_STADE,ID_JEUX,DATE_EVENT,TYPE_EVENT) values (:ID_EVENT,:ID_STADE,:ID_JEUX,:DATE_EVENT,:TYPE_EVENT)");
            queryInsert.bindValue (":ID_EVENT",idEvent);
            queryInsert.bindValue (":ID_STADE",idStade);
            queryInsert.bindValue(":ID_JEUX",idJeux);
            queryInsert.bindValue(":DATE_EVENT",date.toString("dd-MM-yyyy hh:mm"));
            queryInsert.bindValue(":TYPE_EVENT",typeJeu);

            if(queryInsert.exec()) {
                return "Match affecte";
            } else {
                return "Match non affecte";
            }
        }
        return "Ce stade est complet dans cette date";
    }
    return "Le match et le stade n'ont pas le meme type";
}
QSqlQueryModel* Event::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_EVENT,TYPE_EVENT,DATE_EVENT,NOM_STADE FROM event, stade WHERE event.ID_STADE=stade.ID_STADE");



    return model;
}
QSqlQueryModel* Event::getidev()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_EVENT FROM event");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}

Event* Event::getevent(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM event WHERE ID_EVENT = :id");
    query.bindValue(":id",id);
    query.exec();
    Event* E = new Event();
    while (query.next()) {
            E->setidevent(query.value(0).toInt());
            E->setidstadeevent(query.value(1).toInt());
            E->setidjeuxevent(query.value(2).toInt());
            E->settypeevent(query.value(4).toString());


        }
    return E;
}
