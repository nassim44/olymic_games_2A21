#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include "stade.h"
class Location : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double location READ location WRITE setLocation NOTIFY locationChanged);
public:
    explicit Location(QObject *parent = nullptr);

    double location() const
    {
        return M_stade.location;
    }

signals:
    void locationChanged(double location);
public slots:
    void setLocation(double location)
    {
        /*if(M_stade.location == location)
            return;**/
        M_stade.location=location;
        emit locationChanged(location);
    }

private:
    Stade M_stade;
};

#endif // LOCATION_H
