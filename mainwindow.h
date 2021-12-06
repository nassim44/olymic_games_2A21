#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "staff.h"
#include <QMainWindow>
#include "todolist.h"
#include "smtp.h"

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

    void on_show_staff_activated(const QModelIndex &index);

    void on_Supprimer_clicked();

    void on_modifier_clicked();

    void on_Vider_clicked();

    void on_tri_nom_clicked();

    void on_tri_prenom_clicked();

    void on_chercher_clicked();

    void on_todo_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();

    void on_pdf_clicked();

    void on_XL_clicked();

    void on_qr_2_clicked();

private:
    Ui::MainWindow *ui;
    QStringList files;
    CToDoList *app;
      Staff S ;
};
#endif // MAINWINDOW_H
