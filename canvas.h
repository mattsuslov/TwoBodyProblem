#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "system.h"
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class Canvas : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Canvas();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void setSystem(const System& sys) { sys_ = sys; }
    void setEarthPosition(const QVector2D& pos) { sys_.set_earth_center((pos - QVector2D(width_ / 2, height_ / 2)) * QVector2D(1, -1)); }
    QVector2D get_velocity() { return velocity_direction * QVector2D(1, -1); }

public slots:
    void onTimerTimeout();
    void startAnimation();
    void pauseAnimation();
    void stopAnimation();
    void changeDragMode();

private:
    enum AnimationState {
        PREPARE,
        PAUSE,
        PLAY,
        DRAG
    };

    enum DragMode {
        POS,
        VEL
    };


    DragMode dragmode_;
    AnimationState anim_state_;
    System sys_;
    QTimer timer_;
    int width_, height_;

    //DRAG AND DRO PARAMS
    QVector2D press_point, cur_point;
    QVector2D velocity_direction{1, 0};
};

#endif // CANVAS_H
