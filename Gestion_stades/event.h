#ifndef EVENT_H
#define EVENT_H
#include "stade.h"
#include "jeux.h"
#include <QDateTime>
class Event
{
private:
    int id_stade,id_jeux;
    Stade stade;
    Jeux jeux;
    QDateTime date;
public:
    Event();
    Event(int,int,QDateTime);
    int getidevent(){return id_stade;}
    void setidevent(int id_stade ){this->id_stade=id_stade;}
    QDateTime getDate(){return date;}
    void setdate(QDateTime t){date=t;}
    QString ajouterevent();
    QSqlQueryModel* afficher();
};

#endif // EVENT_H
