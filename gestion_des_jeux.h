#ifndef GESTION_DES_JEUX_H
#define GESTION_DES_JEUX_H
#include<QSqlDatabase>
#include <QDialog>
#include"jeux.h"

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
    void on_pushButton_AJOUTER_clicked();

   // void on_lineEdit_IDjeux_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::Gestion_des_jeux *ui;
};

#endif // GESTION_DES_JEUX_H
