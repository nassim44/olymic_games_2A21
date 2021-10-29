#ifndef SAHARWINDOW_H
#define SAHARWINDOW_H

#include <QMainWindow>
#include "joueur.h"
QT_BEGIN_NAMESPACE
namespace Ui { class saharwindow; }
QT_END_NAMESPACE

class saharwindow : public QMainWindow
{
    Q_OBJECT

public:
    saharwindow(QWidget *parent = nullptr);
    ~saharwindow();

private slots:
    void on_pushButtonajouterjou_clicked();

    void on_pushButtonajouterjou_2_clicked();

    void on_comboBox_8_currentIndexChanged(int index);

    void on_combosupj_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

private:
    Ui::saharwindow *ui;
    joueur j;
};
#endif // SAHARWINDOW_H
