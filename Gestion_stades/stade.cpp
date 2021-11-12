#include "stade.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QList>
Stade::Stade()
{
    id=0;capacite=0;nom="";type="";
}
Stade::Stade(int id ,int capacite,QString nom,QString type)
{
    this->id=id;
    this->nom=nom;
    this->capacite=capacite;
    this->type=type;
}
bool Stade::ajouter()
{

    QSqlQuery query;
    QString res=QString::number(id);
    QString cap=QString::number(capacite);

    query.prepare("INSERT INTO STADE (ID_STADE,NOM_STADE,CAPACITE,TYPES_STADE) values (:ID_STADE,:NOM_STADE,:CAPACITE,:TYPES_STADE)");
    query.bindValue (":ID_STADE",res);
    query.bindValue(":NOM_STADE",nom);
    query.bindValue(":CAPACITE",capacite);
    query.bindValue(":TYPES_STADE",type);


    return query.exec();
}
bool Stade::supprimer(int id)
{
    QSqlQuery query;
    QSqlQuery queryevent;

    queryevent.prepare("Delete from event where ID_STADE=:ID_STADE");
    queryevent.bindValue(":ID_STADE",id);
    queryevent.exec();

    query.prepare("Delete from stade where ID_STADE=:ID_STADE");
    query.bindValue(":ID_STADE",id);
    return query.exec();
}
QSqlQueryModel* Stade::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM stade");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Type Stade"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Capacite"));


    return model;
}
bool Stade::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString cap=QString::number(capacite);

    query.prepare("UPDATE STADE SET  NOM_STADE=:NOM_STADE , CAPACITE=:CAPACITE, TYPES_STADE=:TYPES_STADE where ID_STADE = :ID_STADE");
    query.bindValue (":ID_STADE",res);
    query.bindValue(":NOM_STADE",nom);
    query.bindValue(":CAPACITE",cap);
    query.bindValue(":TYPES_STADE",type);
    return query.exec();


}
QSqlQueryModel* Stade::trier()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM stade ORDER BY CAPACITE ASC");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Type Stade"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Capacite"));


    return model;
}

QSqlQueryModel* Stade::trierparnom()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM stade ORDER BY NOM_STADE ASC");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Type Stade"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Capacite"));


    return model;
}

QSqlQueryModel* Stade::getids()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_STADE FROM stade");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}

Stade* Stade::getstade(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM stade WHERE ID_STADE = :id");
    query.bindValue(":id",id);
    query.exec();
    Stade* s = new Stade();
    while (query.next()) {
            s->setid(query.value(0).toInt());
            s->setnom(query.value(1).toString());
            s->settype(query.value(2).toString());
            s->setcapacite(query.value(3).toInt());
        }
    return s;
}

QSqlQueryModel* Stade::recherche(QString nom, QString capacite)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QString query = "SELECT * FROM stade ";
    if((nom != "") && (capacite != "")){
        query = query + "WHERE NOM_STADE LIKE '%" + nom +"%' AND CAPACITE = " + capacite;
    } else if((nom != "") && (capacite == "")) {
        query = query + "WHERE NOM_STADE LIKE '%" + nom +"%'";
    } else if((nom == "") && (capacite != "")) {
        query = query + "WHERE CAPACITE = " + capacite;
    }
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Type Stade"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Capacite"));


    return model;
}
bool Stade::ajouterevent()
{

    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("INSERT INTO event (ID_STADE) values (:ID_STADE)");
    query.bindValue (":ID_STADE",res);



    return query.exec();
}
