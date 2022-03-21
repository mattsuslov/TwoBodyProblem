#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphicsview.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void startAnimation();
    void pauseAnimation();
    void stopAnimation();
    void changeDragMode();


private slots:
    void on_play_pause_btn_clicked();

    void on_stop_btn_clicked();

    void on_position_velosity_btn_clicked();

    void on_reset_btn_clicked();

private:
    enum AnimationState {
        PREPARE,
        PAUSE,
        PLAY
    };

    enum DragMode {
        POS,
        VEL
    };

    AnimationState anim_state_;
    DragMode dragmode_;

    Ui::MainWindow *ui;
    GraphicsView* gv;
};
#endif // MAINWINDOW_H
