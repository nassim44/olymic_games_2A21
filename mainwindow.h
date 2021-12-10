#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
#include "spectateurs.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_QR_clicked();

    void verification();

private:
    Ui::MainWindow *ui;
    QCamera *mCamera;
        QCameraViewfinder * mCameraViewfinder;
        QCameraImageCapture *mCameraImageCapture;
        QVBoxLayout *m;
        QMenu *mOpcionesMenu;
        QAction *mEncenderAction; // ouvrir
        QAction *mApagarAction; //stop
        QAction *mCapturarAction; //capture
        QByteArray data ;
        arduino A;

        spectateurs s;
};
#endif // MAINWINDOW_H
