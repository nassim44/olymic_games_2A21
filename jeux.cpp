#include "jeux.h"
#include<iostream>
Jeux::Jeux(int ID,QString nation,QString nom_jeux,int nb_jeux)
{
    this->nation=nation;
    this->nom_jeux=nom_jeux;
    this->nb_jeux=nb_jeux;
    this->ID=ID;
}

/*bool Jeux::ajouter()
{
  //to do next
}

QSqlQueryModel * Jeux::afficher()
{
   //to do next
}
bool Jeux::supprimer(int)
{
   //to do next
}
*/
