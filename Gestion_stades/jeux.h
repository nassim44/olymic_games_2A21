#ifndef JEUX_H
#define JEUX_H
#include <QString>
#include <QSqlQueryModel>
class Jeux
{
private:
    QString discipline,type_jeux,nation;
    int id_jeux ,nbr_jeux;
public:
    Jeux();
    int getIdjeux(){return id_jeux;}
    int getNombrejeux(){return nbr_jeux;}
    QString getTypejeux(){return type_jeux;}
    QString getDiscipline(){return discipline;}
    QString getNation(){return nation;}

    void setIdjeux(int id_jeux ){this->id_jeux=id_jeux;}
    void setNombrejeux(int nbr_jeux ){this->nbr_jeux=nbr_jeux;}
    void setTypejeux(QString discipline){this->discipline=discipline;}
    void setDiscipline(QString t){type_jeux=t;}
    void setNation(QString n){nation=n;}
    QSqlQueryModel* getidj();
    Jeux* getjeux(int id);
};

#endif // JEUX_H
