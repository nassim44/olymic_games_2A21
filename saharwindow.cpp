#include "saharwindow.h"
#include "ui_saharwindow.h"
#include "joueur.h"
#include <QFileDialog>
#include <QtDebug>
#include <QFile>
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
saharwindow::saharwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::saharwindow)
{
    ui->setupUi(this);
         ui->tableViewja->setModel(j.afficherj());
         ui->combosupj->setModel(j.afficheroncomboj());
}

saharwindow::~saharwindow()
{
    delete ui;

}


void saharwindow::on_pushButtonajouterjou_clicked()
{
    joueur j(ui->lineEditja->text().toInt(),ui->lineEdit_nomja->text(),ui->dateEditja->text(),ui->combopaysja->currentText(),ui->combospja->currentText());
       bool test= j.ajouterj();
       ui->tableViewja->setModel(j.afficherj());
               ui->combosupj->setModel(j.afficheroncomboj());

}

void saharwindow::on_pushButtonajouterjou_2_clicked()
{
    bool    test=j.modifierj(ui->lineEditja->text().toInt(),ui->lineEdit_nomja->text(),ui->dateEditja->text(),ui->combopaysja->currentText(),ui->combospja->currentText()) ;
       ui->tableViewja->setModel(j.afficherj());
    if (test)
          {
                  ui->tableViewja->setModel(j.afficherj());
                  ui->combosupj->setModel(j.afficheroncomboj());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void saharwindow::on_combosupj_currentIndexChanged(int index)
{
    ui->combosupj->currentText();
}

void saharwindow::on_pushButton_4_clicked()
{
    bool test=j.supprimerj(ui->combospja->currentText().toInt());

    if(test)
    {ui->tableViewja->setModel(j.afficherj());//actualisation taa afficher
        ui->combosupj->setModel(j.afficheroncomboj());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                     QObject::tr("suppression succful .\n"),
                    QMessageBox::Cancel);
        }

        else
            QMessageBox::critical(nullptr,QObject::tr("supprimer not open"),
                                    QObject::tr("click cancel to exist"),
                                    QMessageBox::Cancel);
}
