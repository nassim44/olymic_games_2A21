#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

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


};




#endif // JOUEUR_H
