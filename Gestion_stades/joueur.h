#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QSqlQueryModel>

class Joueur
{
private:
    QString Nom_joueur,Prenom_joueur,specialite,pays;
    int id_joueur;
public:
    Joueur();
        int getIdjoueur(){return id_joueur;}
        QString getNomjoueur(){return Nom_joueur;}
        QString getPrenomjoueur(){return Prenom_joueur;}
        QString getSpecialite(){return specialite;}
        QString getPays(){return pays;}

        void setIdjoueur(int id_joueur ){this->id_joueur=id_joueur;}
        void setNomjoueur(QString Nom_joueur ){this->Nom_joueur=Nom_joueur;}
        void setPrenomjoueur(QString Prenom_joueur){this->Prenom_joueur=Prenom_joueur;}
        void setSpecialite(QString specialite){this->specialite=specialite;}
        void setPays(QString pays){this->pays=pays;}
        QSqlQueryModel* getidjou();
        Joueur* getjoueur(int id);
        QByteArray verifier_code_bd(QByteArray);
};

#endif // JOUEUR_H
