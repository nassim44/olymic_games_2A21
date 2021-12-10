#ifndef FACTURE_H
#define FACTURE_H
#include<QString>
#include<QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include "qcustomplot.h"

class Facture
{
public:

     Facture();
     Facture(int, QDate, QString, int, int, int );
    int getid();
    QDate getdate();
    QString getdesignation();
    int getprix();
    int getquantite();
    int gettotal();

    void setid(int);
    void setdate(QDate);
    void setdesignation(QString);
    void setprix(int);
    void setquantite(int);
    void settotal(int);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
  bool  modifier();
  int calcul_facture(int,int);
  QSqlQueryModel*chercher(QString text);
  QSqlQueryModel * tri_date();
  QSqlQueryModel * tri_prix();

private:
    QString   designation;
    QDate date ;
    int id, prix, quantite, total;




};

#endif // FACTURE_H
