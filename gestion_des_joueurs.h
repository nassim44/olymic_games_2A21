#ifndef GESTION_DES_JOUEURS_H
#define GESTION_DES_JOUEURS_H

#include <QMainWindow>
#include "joueur.h"
#include"statj.h"

namespace Ui {
class Gestion_des_joueurs;
}

class Gestion_des_joueurs : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gestion_des_joueurs(QWidget *parent = nullptr);
    ~Gestion_des_joueurs();


private:
    Ui::Gestion_des_joueurs *ui;
    joueur j;



private slots:
    void on_pushButtonajouterjou_clicked();

    void on_pushButtonajouterjou_2_clicked();

    void on_comboBox_8_currentIndexChanged(int index);

    void on_combosupj_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_recherhche_textChanged(const QString &arg1);

    void on_pushButton_tri_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_historique_clicked();
};

#endif // GESTION_DES_JOUEURS_H
