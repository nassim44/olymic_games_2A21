#ifndef GESTION_DES_STADES_H
#define GESTION_DES_STADES_H
#include"olympic_games.h"//perso fedi
#include "stade.h"
#include <QMainWindow>
#include "event.h"
#include "joueur.h"
//#include "affecterjoueur.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class gestion_des_stades;
}

class gestion_des_stades : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_des_stades(QWidget *parent = nullptr);
    ~gestion_des_stades();

private:
    Ui::gestion_des_stades *ui;
    Stade sta;
    Event EV;
    olympic_games og;

   // Event event;
    joueur jou;
    //Affecterjoueur pred;v
private slots :
    void on_pb_ajouter_clicked();

    void on_pushButton_clicked();

    void on_pb_modifier_clicked();

   // void on_radioButton_toggled(bool checked);

   // void on_radioButton_2_toggled(bool checked);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_4_currentIndexChanged(const QString &arg1);



    void on_comboBox_stadeaff_currentIndexChanged(const QString &arg1);

    void on_comboBox_jeuxaff_currentIndexChanged(const QString &arg1);



    void on_pb_affecterevent_clicked();



    void on_comboBox_idjoueur_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_comboBox_idevent_currentIndexChanged(const QString &arg1);

    void on_comboBox_predevent_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_Afficherevent_clicked();

    void on_pushButton_afficherprediction_clicked();

   // void on_radioButton_triertype_toggled(bool checked);

    void on_comboBox_mapidstade_currentIndexChanged(const QString &arg1);

    void on_pushButton_affichermap_2_clicked();

    void on_checkBox_trierparcapacite_toggled(bool checked);

    void on_checkBox_trirerparlettre_toggled(bool checked);

    void on_checkBox_triertypestade_toggled(bool checked);

    void on_pushButton_6_clicked();
    void on_pb_affecterjjjj_clicked();
};

#endif // GESTION_DES_STADES_H
