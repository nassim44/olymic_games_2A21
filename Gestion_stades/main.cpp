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
#include <QQmlEngine>
#include <QQmlContext>
#include "location.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    qmlRegisterType<Location>("Location",1,0,"Stade");
    Stade s;
    Location cppLocation;
    Location cppLocationCopy;
    c.createconnection();
    QObject::connect(&cppLocation, &Location::locationChanged, &cppLocationCopy, &Location::setLocation);

    cppLocation.setLocation(36.839448552924246);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("cppLocation", &cppLocation);
    engine.rootContext()->setContextProperty("cppLocationCopy", &cppLocationCopy);
    engine.load(QUrl(QStringLiteral("qrc:/Map.qml")));

    MainWindow w;
    w.show();

    return a.exec();
}
