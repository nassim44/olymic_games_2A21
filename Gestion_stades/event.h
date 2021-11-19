#ifndef EVENT_H
#define EVENT_H
#include "stade.h"
#include "jeux.h"
#include <QDateTime>
class Event
{
private:
    int id_event,id_stade,id_jeux;
    QDateTime date;
    QString type_event;
public:
    Event();
    Event(int,int,int,QDateTime);
    int getidevent(){return id_event;}
    void setidevent(int id_event ){this->id_event=id_event;}
    int getidstadeevent(){return id_stade;}
    void setidstadeevent(int id_stade ){this->id_stade=id_stade;}
    int getidjeuxevent(){return id_jeux;}
    void setidjeuxevent(int id_jeux ){this->id_jeux=id_jeux;}
    QDateTime getDate(){return date;}
    void setdate(QDateTime t){date=t;}
    QString gettypeevent(){return type_event;}
    void settypeevent(QString type_event ){this->type_event=type_event;}
    QString ajouterevent();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trierdate();
    QSqlQueryModel* getidev();
    Event* getevent(int id);
};

#endif // EVENT_H
