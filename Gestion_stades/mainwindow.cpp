#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stade.h"
#include <QApplication>
#include <QMessageBox>
//#include "stade.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->tab_stade->setModel(sta.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{

        int id=ui->lineEdit_id->text().toInt();
        int capacite=ui->lineEdit_capacite->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString type=ui->comboBox->currentText();


        Stade S(id,capacite,nom,type);
        bool test=S.ajouter();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("Ajout non effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
    Stade S1; S1.setid(ui->lineEdit_id_supp->text().toInt());
    bool test=S1.supprimer(S1.getid());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Echec de supprission\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
