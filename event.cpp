#include "event.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include"olympic_games.h"

Event::Event()
{
    ID_EVENT=0;
    ID_STADE=0;
    ID_JEUX=0;
}
Event::Event(int ID_EVENT,int ID_STADE,int ID_JEUX,QDateTime DATE)
{
    this->ID_EVENT=ID_EVENT;
    this->ID_STADE=ID_STADE;
    this->ID_JEUX=ID_JEUX;
    this->DATE=DATE;
}
QString Event::ajouterevent()
{
    QSqlQuery queryStade;
    QSqlQuery queryJeu;
    QSqlQuery queryDateExiste;
    QSqlQuery queryInsert;
    QString idEvent = QString::number(ID_EVENT);
    QString idStade = QString::number(ID_STADE);
    QString idJeux = QString::number(ID_JEUX);
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
    queryJeu.prepare("SELECT * FROM OLYMPIC_GAMES WHERE ID_JEUX = :id");
    queryJeu.bindValue(":id",idJeux);
    queryJeu.exec();
    while(queryJeu.next()) {
        typeJeu = queryJeu.value(3).toString();
    }

    //Check if stade is available
    queryDateExiste.prepare("SELECT * FROM EVENT WHERE ID_STADE = :id AND DATE_EVENT = :date");
    queryDateExiste.bindValue(":id",idStade);
    queryDateExiste.bindValue(":date",DATE.toString("dd-MM-yyyy hh:mm"));
    queryDateExiste.exec();
    if(QString::compare(typeStade,typeJeu,Qt::CaseInsensitive) == 0) {
        if(queryDateExiste.next() == false) {
            queryInsert.prepare("INSERT INTO EVENT (ID_EVENT,ID_STADE,ID_JEUX,DATE_EVENT,TYPE_EVENT)"
                                " values (:ID_EVENT,:ID_STADE,:ID_JEUX,:DATE_EVENT,:TYPE_EVENT)");
            //queryInsert.bindValue (":ID_EVENT",ID_EVENT);
            //queryInsert.bindValue (":ID_STADE",ID_STADE);
            //queryInsert.bindValue(":ID_JEUX",ID_JEUX);
            //queryInsert.bindValue(":DATE_EVENT",DATE.toString("dd-MM-yyyy hh:mm"));
            //queryInsert.bindValue(":TYPE_EVENT",typeJeu);
            queryInsert.bindValue (":ID_EVENT",idEvent);
            queryInsert.bindValue (":ID_STADE",idStade);
            queryInsert.bindValue(":ID_JEUX",idJeux);
            queryInsert.bindValue(":DATE_EVENT",DATE.toString("dd-MM-yyyy hh:mm"));
            //queryInsert.bindValue(":TYPE_EVENT",typeStade);
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

//--------------------------------afficher---------------------------------
QSqlQueryModel* Event::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

   // model->setQuery("SELECT * from event");
                   // "TYPE_EVENT,DATE,NOM_STADE FROM event, stade WHERE event.ID_STADE=stade.ID_STADE");
    model->setQuery("SELECT ID_EVENT,DATE_EVENT,TYPE_EVENT,NOM_STADE FROM EVENT, STADE WHERE EVENT.ID_STADE=STADE.ID_STADE");
    return model;
}
//--------------------------------afficher---------------------------------

QSqlQueryModel* Event::getidev()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_EVENT FROM EVENT");
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
