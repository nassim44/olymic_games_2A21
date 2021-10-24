#ifndef JEUX_H
#define JEUX_H
#include<QSqlQuery>
#include<QSqlQueryModel>


class Jeux
{
private:
    QString nation,nom_jeux;
    int nb_jeux;
    int ID;
public:
    //constructeurs
    Jeux();//par defaut
    Jeux(int ID,QString nation,QString nom_jeux,int nb_jeux);//paramétré

    //Geters
    QString get_nom(){return nom_jeux;}
    QString get_nation(){return nation;}
    int get_ID(){return ID;}
    int get_nb_jeux(){return nb_jeux;}

    //Setters
    void set_nom(QString n){nom_jeux=n;}
    void set_nation(QString m){nation=m;}
    void set_ID(int x){ID=x;}
    void set_nb_jeux(int y){nb_jeux=y;}

    // les méthodes
    bool ajouter();//ajouter un jeu
    QSqlQueryModel * afficher();//afficher un jeu
    bool supprimer(int);//supprimer un jeu
};

#endif // JEUX_H

