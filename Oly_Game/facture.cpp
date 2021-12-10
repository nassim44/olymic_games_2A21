#include "facture.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>
#include <QDate>

Facture::Facture()
{
    id=0000000;
    date=QDate::currentDate();
    designation="";
    prix=0;
    quantite=0;
    total=0;
}

    Facture::Facture(int id,QDate date,QString designation,int prix,int quantite,int total)
    {
        this->id=id;
        this->date=date;
        this->designation=designation;
        this->prix=prix;
        this->quantite=quantite;
        this->total=total;



    }

    int Facture::getid(){return id;}
    QDate Facture::getdate(){return date;}
    QString Facture::getdesignation(){return designation;}
    int Facture::getprix(){return prix;}
    int Facture::getquantite(){return quantite;}
    int Facture::gettotal(){return total;}

    void Facture::setid(int id){this->id=id;}
    void Facture::setdate(QDate date){this->date=date;}
    void Facture::setdesignation(QString designation){this->designation=designation;}
    void Facture::setprix(int prix){this->prix=prix;}
    void Facture::setquantite(int quantite){this->quantite=quantite;}
    void Facture::settotal(int total){this->total=total;}

    //*************************************************************************
    //*************************************************************************
    bool Facture::ajouter()
    {
        QString id_string= QString::number(id);
        QString prix_string= QString::number(prix);
        QString quantite_string= QString::number(quantite);
        QString total_string= QString::number(total);
        bool test=false;
        QSqlQuery query;
          query.prepare("INSERT INTO FACTURE (ID, DAT, DESIGNATION , PRIX , QUANTITE , TOTAL) "
                        "VALUES ( :ID , :DAT , :DESIGNATION , :PRIX , :QUANTITE , :TOTAL)");
          query.bindValue(":ID",id);
          query.bindValue(":DAT",date);
          query.bindValue(":DESIGNATION",designation);
          query.bindValue(":PRIX",prix_string);
          query.bindValue(":QUANTITE",quantite_string);
          query.bindValue(":TOTAL",total_string);
          query.exec();
          test =true;
        return test ;
    }

    QSqlQueryModel* Facture::afficher()
    {
         QSqlQueryModel* model=new  QSqlQueryModel();

         model->setQuery("SELECT * FROM FACTURE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESIGNATION"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("TOTAL"));

        return model;

    }

    bool Facture::supprimer(int id)
    {
     QSqlQuery query;
     QString res= QString::number(id);
     query.prepare("Delete from FACTURE where ID= :ID");
     query.bindValue(":ID",res);
     return query.exec();
    }

bool Facture::modifier()
    {
        bool test=false;
        QSqlQuery query;

        QString id_string= QString::number(id);
        QString prix_string= QString::number(prix);
        QString quantite_string= QString::number(quantite);
        QString total_string= QString::number(total);
        query.prepare("UPDATE FACTURE set ID=:ID ,DAT=:DAT,DESIGNATION=:DESIGNATION ,PRIX=:PRIX , QUANTITE=:QUANTITE, TOTAL=:TOTAL"
                      "  WHERE ID=:ID");
        query.bindValue(":ID",id);
        query.bindValue(":DAT",date);
        query.bindValue(":DESIGNATION",designation);
        query.bindValue(":PRIX",prix_string);
        query.bindValue(":QUANTITE",quantite_string);
        query.bindValue(":TOTAL",total_string);

         if( query.exec())
            test =true;


        return test ;
    }
int Facture::calcul_facture(int min, int max){

    QSqlQuery query;
    query.prepare("select *from FACTURE where PRIX between :min and :max");
    query.bindValue(":min",min);
    query.bindValue(":max",max);
    query.exec();

    int total=0;
    while(query.next()){
        total++;
    }

    return total;
}

QSqlQueryModel* Facture::chercher(QString text)
{
QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
   {
     query.prepare("SELECT * FROM FACTURE where ID like '"+text+"'");
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESIGNATION"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("TOTAL"));
     }

    return model;

}

QSqlQueryModel * Facture::tri_date()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FACTURE order by DAT asc ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESIGNATION"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("TOTAL"));


    return model;
}
QSqlQueryModel * Facture::tri_prix()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FACTURE order by PRIX asc ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESIGNATION"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("TOTAL"));


    return model;
}
