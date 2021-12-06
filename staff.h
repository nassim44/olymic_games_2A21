#ifndef STAFF_H
#define STAFF_H
#include <QString>
#include <QSqlQueryModel>
#include "qcustomplot.h"

class Staff
{
public:


    Staff();
Staff(int,QString,QString,QString);

int getCin();
QString getNom();
QString getPrenom();
QString getType();

void setCin(int);
void setNom(QString);
void setPrenom(QString);
void setType(QString);

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier();

QSqlQueryModel *afficher_tri_nom();
QSqlQueryModel *afficher_tri_prenom();
QSqlQueryModel* chercher_staff(QString text);

   private:


int CIN;
QString NOM;
QString PRENOM;
QString TYPES;



};
#endif // STAFF_H
