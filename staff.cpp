#include "staff.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>


Staff::Staff()
{
CIN=0;NOM="";PRENOM="";TYPES="";
}
Staff::Staff(int CIN,QString NOM,QString PRENOM,QString TYPES)
{
this->CIN=CIN;
this->NOM=NOM;
this->PRENOM=PRENOM;
this->TYPES=TYPES;
}

int Staff::getCin(){return CIN;}
QString Staff::getType(){return TYPES;}
QString Staff::getNom(){return PRENOM;}
QString Staff::getPrenom(){return TYPES;}
void Staff::setCin(int CIN){this->CIN=CIN;}
void Staff::setNom(QString NOM){this->NOM=NOM;}
void Staff::setPrenom(QString PRENOM){this->PRENOM=PRENOM;}
void Staff::setType(QString TYPES) {this->TYPES=TYPES;}

bool Staff::ajouter()
{
    QString Cin_string= QString::number(CIN);
    bool test=false;
    QSqlQuery query;
      query.prepare("INSERT INTO STAFF (CIN, NOM,PRENOM,TYPES) "
                    "VALUES (:CIN, :NOM, :PRENOM,:TYPES)");
      query.bindValue(0,Cin_string);
      query.bindValue(1,NOM);
      query.bindValue(2,PRENOM);
      query.bindValue(3,TYPES);
      query.exec();
      test =true;
    return test ;
}

QSqlQueryModel* Staff::afficher()
{
     QSqlQueryModel* model=new  QSqlQueryModel();

     model->setQuery("SELECT* FROM STAFF");

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type "));

    return model;

}

bool Staff::supprimer(int cin)
{
 QSqlQuery query;
 QString res= QString::number(cin);
 query.prepare("Delete from STAFF where CIN= :CIN");
 query.bindValue(":CIN",res);
 return query.exec();
}
bool Staff::modifier()
{
    bool test=false;
    QSqlQuery query;

    QString Cin= QString::number(CIN);

      query.prepare("UPDATE STAFF set CIN=:CIN , NOM=:NOM, PRENOM=:PRENOM , TYPES=:TYPES   WHERE CIN=:CIN");

      query.bindValue(":CIN",Cin);
      query.bindValue(":NOM",NOM);
      query.bindValue(":PRENOM",PRENOM);
      query.bindValue(":TYPES",TYPES);

     if( query.exec())
        test =true;


    return test ;
}


QSqlQueryModel * Staff::afficher_tri_nom()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from STAFF order by NOM asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPES"));



    return model;
}

QSqlQueryModel * Staff::afficher_tri_prenom()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from STAFF order by PRENOM asc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPES"));

    return model;
}

QSqlQueryModel* Staff::chercher_staff(QString text)
{
QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
   {
     query.prepare("SELECT * FROM STAFF where CIN like '"+text+"'");
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPES"));
     }

    return model;

}
