#include "jeux.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QList>
Jeux::Jeux()
{
    id_jeux=0;nbr_jeux=0;discipline="";type_jeux="";nation="";
}
QSqlQueryModel* Jeux::getidj()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT ID_JEUX FROM jeux");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}

Jeux* Jeux::getjeux(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM jeux WHERE ID_JEUX = :id");
    query.bindValue(":id",id);
    query.exec();
    Jeux* j = new Jeux();
    while (query.next()) {
            j->setIdjeux(query.value(0).toInt());
            j->setTypejeux(query.value(1).toString());
            j->setNation(query.value(2).toString());
            j->setDiscipline(query.value(3).toString());
            j->setNombrejeux(query.value(4).toInt());
        }
    return j;
}
