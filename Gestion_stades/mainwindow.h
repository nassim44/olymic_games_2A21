#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stade.h"
#include <QMainWindow>
#include "jeux.h"
#include "event.h"
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

private:
    Ui::MainWindow *ui;
    Stade sta;
    Jeux jeux;
    Event event;
};
#endif // MAINWINDOW_H
