#ifndef JEUX_H
#define JEUX_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>

class Jeux
{
private:
    int ID_JEUX;
    int NBR_JEUX;
    QString TYPE_JEUX,NATION,DISCIPLINE;


public:
//constructeurs
Jeux();//par defaut
Jeux( int ID_JEUX,int NBR_JEUX,QString TYPE_JEUX,QString NATION,QString DISCIPLINE);

//Geters
int get_ID(){return ID_JEUX;}
int get_NBR(){return NBR_JEUX;}
QString get_type_jeu(){return TYPE_JEUX;}
QString get_nation(){return NATION;}
QString get_Discipline(){return DISCIPLINE;}

//Seters
void set_ID(int x){ID_JEUX=x;}
void set_nbr_jeux(int y){NBR_JEUX=y;}
void set_type_jeu(QString type){TYPE_JEUX=type;}
void set_nation(QString nation){NATION=nation;}
void set_discipline(QString discipline){DISCIPLINE=discipline;}

//CRUD
bool ajouter();
};

#endif // JEUX_H
