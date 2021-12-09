#ifndef GESTION_DES_JEUX_H
#define GESTION_DES_JEUX_H
#include<QSqlDatabase>
#include <QDialog>
#include"olympic_games.h"
#include<QCompleter>
#include <QMediaPlayer>
#include<QPropertyAnimation>
namespace Ui {
class Gestion_des_jeux;
}

class Gestion_des_jeux : public QDialog
{
    Q_OBJECT

public:
    explicit Gestion_des_jeux(QWidget *parent = nullptr);
    ~Gestion_des_jeux();

private slots:

    void on_pushButton_AJOUTER_clicked();//bouton ajouter
    void on_pushButton_supprimer_clicked();//bouton supprimer
    //void on_pushButton_13_clicked();//bouton afficher
    // void on_pushButton_authentifier_clicked();//s'authentifier


    void on_pushButton_afficher_supp_clicked();

    void on_pushButton_Modifier_clicked();

    void on_CHERCHER_clicked();

    void on_pushButton_chercher_type_clicked();

    void on_chercher_discipline_clicked();

    void on_CHERCHER_NATION_clicked();

    void showTime();
    void showDate();

   // void on_pushButton_chercher_clicked();
   // void on_pushButton_chercher_clicked();
    //void on_pushButton_32_clicked();






    void on_pushButton_trier_clicked();

    void on_pushButton_tri_type_clicked();

    void on_pushButton_TRI_dis_clicked();

    void on_pushButton_TRI_Nation_clicked();

    // boton mailing
    void on_browseBtn_clicked();
    void  browse();
    void  mailSent(QString status);
    void on_sendBtn_clicked();






    //void on_tableView_modifier_activated(const QModelIndex &index);

    void on_pushButton_Modifier_2_clicked();


    void on_tableView_modifier_clicked(const QModelIndex &index);

    void on_pushButton_32_clicked();

   // void on_Stat_clicked();

    void on_statistique_clicked();

    void on_localisation_clicked();

private:
    Ui::Gestion_des_jeux *ui;
    olympic_games olg; //olg est une instance de olympic_games
    //QCompleter* Model_Completer2;
    QCompleter* Model_Completer;
    QStringList files;
    QMediaPlayer *player;
    QPropertyAnimation *animation;
    QPropertyAnimation *animation1;

};

#endif // GESTION_DES_JEUX_H
