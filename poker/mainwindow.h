#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "play.h"
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeW();//关闭窗口

private slots://槽函数
    void on_start_clicked();
    void on_endGame_clicked();
    void on_action_changed();

private:
    Ui::MainWindow *ui;
    play w;
    QMediaPlayer *myPlayer;//音效
};

#endif // MAINWINDOW_H
