#ifndef AFFECTERJOUEUR_H
#define AFFECTERJOUEUR_H
#include "joueur.h"
#include "event.h"

class Affecterjoueur
{
private:
    int id_event;
    int id_jou;
    float prediction;
public:
    Affecterjoueur();
    Affecterjoueur(int,int);
    int getidev(){return id_event;}
    void setidev(int id_event ){this->id_event=id_event;}
    int getidjoue(){return id_jou;}
    void setidjoue(int id_jou ){this->id_jou=id_jou;}
    float getprediction(){return prediction;}
    void setprediction(float prediction ){this->prediction=prediction;}
    QString ajouterjoueurevent();
    //void modifierprediction(QString idEvent);
    void predictionExcel(QString idEvent);
    QSqlQueryModel* afficherprediction();
    QSqlQueryModel* afficherpredictionevnt(QString id);
};

#endif // AFFECTERJOUEUR_H
