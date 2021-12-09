#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>
#include<QPdfWriter>
#include <QSqlQuery>
#include <QSqlQueryModel>
//#include<QPrintDialog>
//#include<QPrinter>

class joueur
{
    QString nom,nais,pays,specialite;
    int idj;
public:
    joueur(){}
    joueur(int,QString,QString,QString,QString);
    bool ajouterj();
    QSqlQueryModel * afficherj();
    bool modifierj(int idj,QString nom, QString nais,QString pays,QString specialite);
    QSqlQueryModel * afficheroncomboj();
    bool  rechercherj(int idj  );
    bool supprimerj(int);
    void genererPDFj();
    bool  ajfichehisto(int);
    QSqlQueryModel * trides();
       QSqlQueryModel * triasc();
       QSqlQueryModel * tridesnom();
          QSqlQueryModel * triascnom();
          QSqlQueryModel * tridesnais();
             QSqlQueryModel * triascnais();
             QSqlQueryModel *   tridespays();
QSqlQueryModel *   triascpays();
void pdf();
QSqlQueryModel* getidjou();
joueur* getjoueur(int id);
};




#endif // JOUEUR_H
