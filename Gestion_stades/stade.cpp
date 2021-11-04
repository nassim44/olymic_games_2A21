#include "stade.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
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
