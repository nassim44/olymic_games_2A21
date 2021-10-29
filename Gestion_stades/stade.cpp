#include "stade.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
Stade::Stade(int id ,int capacite,QString nom,QString type/*,QString date*/)
{
    this->id=id;
    this->nom=nom;
    this->capacite=capacite;
    this->type=type;
   // this->date=date;
}
bool Stade::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString cap=QString::number(capacite);

    query.prepare("insert into STADE (id,nom,capacite,type)" "values(:id,:nom,:capacite,:type)");
    query.bindValue (":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":capacite",capacite);
    query.bindValue(":type",type);
    //query.bindValue(":event",date);

    return query.exec();
}
/*QSqlQueryModel* Stade::afficher()
{

QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM stade");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Capacite"));
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Type"));
return model;
}
bool Stade::supprimer(int id)
{
    QSqlQuery query;


    query.prepare("Delete from STADE where id=:id");
    query.bindValue (":id",id);




    return query.exec();
}*/
