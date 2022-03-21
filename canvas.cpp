#include "canvas.h"

Canvas::Canvas()
{
    width_ = 700;
    height_ = 700;

    connect(&timer_, &QTimer::timeout, this, &Canvas::onTimerTimeout);
    timer_.setInterval(20);
    anim_state_ = PREPARE;
}


void Canvas::startAnimation() {
    anim_state_ = PLAY;
    timer_.start();
}


void Canvas::pauseAnimation() {
    anim_state_ = PAUSE;
    timer_.stop();
}


void Canvas::stopAnimation() {
    anim_state_ = PREPARE;
    update();
    timer_.stop();
}


QRectF Canvas::boundingRect() const {
    return QRectF(0, 0, width_, height_);
}


void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (anim_state_ == PREPARE || anim_state_ == DRAG) {
        painter->drawPixmap(0, 0, width_, height_, sys_.get_frame(false));
    } else {
        painter->drawPixmap(0, 0, width_, height_, sys_.get_frame(true));
    }

    auto earth_coords = sys_.get_earth_center();
    earth_coords *= {1, -1};
    earth_coords += QVector2D(width_ / 2, height_ / 2);
    if (anim_state_ == PREPARE){
        painter->setPen(Qt::white);
        painter->setBrush(Qt::green);
        painter->drawLine(earth_coords.toPointF(), (earth_coords + velocity_direction * 20).toPointF());
        painter->drawEllipse((earth_coords + velocity_direction * 20).toPointF(), 2, 2);
    }

    if (anim_state_ == DRAG) {
        if (dragmode_ == POS) {
            painter->setPen(Qt::white);
            painter->setBrush(Qt::gray);
            painter->drawEllipse(cur_point.toPointF(), 5, 5);
        } else {
            painter->setPen(Qt::white);
            painter->setBrush(Qt::red);
            painter->drawLine(press_point.toPointF(), cur_point.toPointF());
            painter->drawEllipse(cur_point.toPointF(), 2, 2);
        }
    }

}


void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    press_point = QVector2D(event->pos());
}


void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    cur_point = QVector2D(event->pos());
    auto earth_coords = sys_.get_earth_center();
    earth_coords *= {1, -1};
    earth_coords += QVector2D(width_ / 2, height_ / 2);
    if (anim_state_ == PREPARE && (press_point - earth_coords).length() < 10 && (QVector2D(event->pos()) - press_point).length() > 0.5) {
        anim_state_ = AnimationState::DRAG;
    }
    if (anim_state_ == AnimationState::DRAG) {
        update();
    }
}


void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (anim_state_ == DRAG) {
        if (dragmode_ == POS) {
            setEarthPosition(cur_point);
        } else {
            velocity_direction = (QVector2D(event->pos()) - press_point).normalized();
        }

        timer_.stop();
        anim_state_ = AnimationState::PREPARE;
        update();
    }
}


void Canvas::onTimerTimeout() {
    sys_.next_frame();
    update();

}


void Canvas::changeDragMode() {
    if (dragmode_ == POS) {
        dragmode_ = VEL;
    } else {
        dragmode_ = POS;
    }
}
