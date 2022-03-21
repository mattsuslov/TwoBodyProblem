#include "system.h"
#include <QDebug>

System::System()
{

}

System::System(long double sun_mass, long double earth_mass, QVector2D velocity) {
    sun_mass_ = sun_mass;
    earth_mass_ = earth_mass;
    earth_speed_ = velocity;
    sun_center_ = {0, 0};
    sun_speed_ = {0, 0};
}

void System::next_frame() {
   QVector2D r =  sun_center_ - earth_center_;
   QVector2D ac_sun = r.normalized() * G * earth_speed_ / r.lengthSquared();
   QVector2D ac_earth = r.normalized() * G * sun_mass_ / r.lengthSquared();
   earth_speed_ += ac_earth * dt_;
   earth_center_ += earth_speed_ * dt_;

   sun_speed_ += ac_sun * dt_;
   sun_center_ += sun_speed_ * dt_;
}


QPixmap System::get_frame(bool dynamic_zoom) {
    QPixmap pixmap;
    if (dynamic_zoom) {
        int MAX_R = std::max(350.0f, std::max(earth_center_.length(), sun_center_.length()));
        pixmap = QPixmap(MAX_R * 2, MAX_R * 2);
    } else {
        pixmap = QPixmap(700, 700);
    }
    QPainter painter(&pixmap);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, pixmap.width(), pixmap.height());

    QMatrix m;
    m.translate(pixmap.width() / 2, pixmap.height() / 2);
    m.scale(1, -1);

    painter.setTransform(QTransform(m));

    painter.setBrush(Qt::white);
    painter.setPen(Qt::yellow);
    painter.drawEllipse(sun_center_.toPointF(), 10, 10);
    painter.drawEllipse(earth_center_.toPointF(), 5, 5);

    return pixmap;
}
