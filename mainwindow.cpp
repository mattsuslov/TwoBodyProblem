#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gv = new GraphicsView;
    ui->GVLayout->addWidget(gv);

    connect(this, &MainWindow::startAnimation, gv->getCanvas(), &Canvas::startAnimation);
    connect(this, &MainWindow::stopAnimation, gv->getCanvas(), &Canvas::stopAnimation);
    connect(this, &MainWindow::pauseAnimation, gv->getCanvas(), &Canvas::pauseAnimation);
    connect(this, &MainWindow::changeDragMode, gv->getCanvas(), &Canvas::changeDragMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_play_pause_btn_clicked()
{
    if (anim_state_ == PREPARE) {
        gv->getCanvas()->setSystem(System(ui->sun_mass->value(), ui->earth_mass->value(),
                                          ui->earth_speed->value() * gv->getCanvas()->get_velocity()));
    }
    if (anim_state_ == PREPARE || anim_state_ == PAUSE) {
        emit startAnimation();
        anim_state_ = PLAY;
        ui->play_pause_btn->setText("Pause");

        ui->position_velosity_btn->setDisabled(true);
        ui->sun_mass->setDisabled(true);
        ui->earth_mass->setDisabled(true);
        ui->earth_speed->setDisabled(true);
        ui->reset_btn->setDisabled(true);
    } else {
        emit pauseAnimation();
        anim_state_ = PAUSE;
        ui->play_pause_btn->setText("Play");
    }
}


void MainWindow::on_stop_btn_clicked()
{
    gv->getCanvas()->setSystem(System(ui->sun_mass->value(), ui->earth_mass->value(),
                                      ui->earth_speed->value() * gv->getCanvas()->get_velocity()));
    emit stopAnimation();
    anim_state_ = PREPARE;
    ui->play_pause_btn->setText("Start");

    ui->position_velosity_btn->setDisabled(false);
    ui->sun_mass->setDisabled(false);
    ui->earth_mass->setDisabled(false);
    ui->earth_speed->setDisabled(false);
    ui->reset_btn->setDisabled(false);
}


void MainWindow::on_position_velosity_btn_clicked()
{
    emit changeDragMode();
    if (dragmode_ == POS) {
        dragmode_ = VEL;
        ui->position_velosity_btn->setText("VELOCITY");
    } else {
        dragmode_ = POS;
        ui->position_velosity_btn->setText("POSITION");
    }
}


void MainWindow::on_reset_btn_clicked()
{
    gv->getCanvas()->setEarthPosition({10, 10});
//    gv->getCanvas()->({10, 10});
    gv->getCanvas()->update();
}
