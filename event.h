#ifndef EVENT_H
#define EVENT_H
#include "stade.h"
#include "olympic_games.h"
#include <QDateTime>
class Event
{
private:
    int ID_EVENT,ID_STADE,ID_JEUX;
    QDateTime DATE;
    QString TYPE_EVENT;
public:
    Event();
    Event(int,int,int,QDateTime);
    int getidevent(){return ID_EVENT;}
    void setidevent(int id_event ){this->ID_EVENT=id_event;}
    int getidstadeevent(){return ID_STADE;}
    void setidstadeevent(int id_stade ){this->ID_STADE=id_stade;}
    int getidjeuxevent(){return ID_JEUX;}
    void setidjeuxevent(int id_jeux ){this->ID_JEUX=id_jeux;}
    QDateTime getDate(){return DATE;}
    void setdate(QDateTime t){DATE=t;}
    QString gettypeevent(){return TYPE_EVENT;}
    void settypeevent(QString type_event ){this->TYPE_EVENT=type_event;}
    QString ajouterevent();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trierdate();
    QSqlQueryModel* getidev();
    Event* getevent(int id);

};

#endif // EVENT_H
