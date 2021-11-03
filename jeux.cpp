#include "jeux.h"
#include "connection.h"

Jeux::Jeux(int ID_JEUX,int NBR_JEUX,QString TYPE_JEUX,QString NATION,QString DISCIPLINE)
{
this->ID_JEUX=ID_JEUX;
this->NBR_JEUX=NBR_JEUX;
this->TYPE_JEUX=TYPE_JEUX;
this->NATION=NATION;
this->DISCIPLINE=DISCIPLINE;
}

bool Jeux::ajouter()
{
    QSqlQuery query;
    //QString res = QString ::number(ID_JEUX);

    query.prepare("inserer dans jeu (ID_JEUX,NBR_JEUX,NATION,DISCIPLINE,TYPE_JEUX)""values(:ID_JEUX,:NBR_JEUX,:NATION,:DISCIPLINE,:TYPE_JEUX)");
    //Créer les variables  liées
    query.bindValue(":id",ID_JEUX);
    query.bindValue(":type de jeu",TYPE_JEUX);
    query.bindValue(":nation",NATION);
    query.bindValue(":discipline",DISCIPLINE);
    query.bindValue(":NBR_JEUX",NBR_JEUX);

    return  query.exec();//envoyer la requete pour l'exécuter

}
