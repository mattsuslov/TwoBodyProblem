#ifndef SYSTEM_H
#define SYSTEM_H


#include <QVector2D>
#include <QVector3D>
#include <QPixmap>
#include <QPainter>
#include <cmath>


class System
{
public:
    System();
    System(long double sun_mass, long double earth_mass, QVector2D velocity);
    void next_frame();
    QPixmap get_frame(bool dynamic_zoom = false);
    QVector2D get_earth_center() {return earth_center_;}
    void set_earth_center(const QVector2D& pos) { earth_center_ = pos;}

    void sun_reset(const QVector2D& pos) { earth_center_ = pos;}

    void operator=(const System& sys) {
        sun_mass_ = sys.sun_mass_;
        earth_mass_ = sys.earth_mass_;
        earth_speed_ = sys.earth_speed_;
    }

private:
    long double G = 100;
    long double sun_mass_{100}, earth_mass_{1};
    QVector2D earth_speed_{-5, 10};
    QVector2D sun_speed_{0, 0};
    QVector2D sun_center_{0, 0}, earth_center_{30, 30};
    long double dt_{0.1};
};

#endif // SYSTEM_H
