#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "olympic_games.h"
#include <QMainWindow>
#include<QVariant>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_supprimer_clicked();

    void on_pushButton_supprimer_clicked();

private:
    Ui::MainWindow *ui;
    olympic_games game;

  signals:
    void setCenter(QVariant,QVariant);
};

#endif // MAINWINDOW_H
