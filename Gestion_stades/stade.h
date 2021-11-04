#ifndef STADE_H
#define STADE_H
#include <QString>
#include <QSqlQueryModel>

class Stade
{
private:
    QString nom,type;
    int id ,capacite;
public:
    Stade();
    Stade(int,int,QString,QString);
    int getid(){return id;}
    int getcapacite(){return capacite;}
    QString getnom(){return nom;}
    QString gettype(){return type;}

    void setid(int id ){this->id=id;}
    void setcapacite(int capacite ){this->capacite=capacite;}
    void setnom(QString n){nom=n;}
    void settype(QString t){type=t;}
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);

};

#endif // STADE_H
