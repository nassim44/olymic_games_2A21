#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    Stade s;
    bool test=c.createconnection();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Map.qml")));
    MainWindow w;
    w.show();

    return a.exec();
}
