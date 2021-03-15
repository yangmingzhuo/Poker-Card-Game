#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&w, &play::exitBack, this, [=]()
    {
        this ->show();
    });
    myPlayer = new QMediaPlayer;
    myPlayer->setMedia(QUrl("qrc:/music/begin.mp3"));
    myPlayer->setVolume(5);
    myPlayer->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeW()
{
    w.hide();
    this->show();
}

void MainWindow::on_start_clicked()
{
    this->hide();
    w.show();
    myPlayer->pause();

    myPlayer = new QMediaPlayer;
    myPlayer->setMedia(QUrl("qrc:/music/gaming.mp3")); //循环播放
    myPlayer->setVolume(5);
    myPlayer->play();

}

void MainWindow::on_endGame_clicked()
{
    this->close();
}

void MainWindow::on_action_changed()
{
    this->showMinimized();
    ui->action->setChecked(0);
}
