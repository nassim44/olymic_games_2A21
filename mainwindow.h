#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "facture.h"
#include"statistiques.h"

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


    void on_ajout_clicked();

    void on_show_fact_activated(const QModelIndex &index);

    void on_Supprimer_clicked();

    void on_modifier_clicked();

    void on_stat_clicked();

    void on_ajout_2_clicked();

    void on_TRI_date_clicked();

    void on_TRI_prix_clicked();

    void on_PDF_clicked();

private:
    Ui::MainWindow *ui;
    Facture F;
    QStringList files;

};
#endif // MAINWINDOW_H
