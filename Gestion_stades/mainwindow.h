#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stade.h"
#include <QMainWindow>
#include "jeux.h"
#include "event.h"
#include "joueur.h"
#include "affecterjoueur.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    //void on_pushButton_supprimer_clicked();

    void on_pb_ajouter_clicked();

    void on_pushButton_clicked();

    void on_pb_modifier_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

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

    void on_radioButton_triertype_toggled(bool checked);

    void on_comboBox_mapidstade_currentIndexChanged(const QString &arg1);

    void on_pushButton_affichermap_2_clicked();

private:
    Ui::MainWindow *ui;
    Stade sta;
    Jeux jeux;
    Event event;
    Joueur jou;
    Affecterjoueur pred;
};
#endif // MAINWINDOW_H
