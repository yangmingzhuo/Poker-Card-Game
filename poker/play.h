#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <map>
#include "poker.h"
#include "dialog.h"
#include <QMediaPlayer>

namespace Ui {
class play;
}

class play : public QWidget
{
    Q_OBJECT

public:
    explicit play(QWidget *parent = nullptr);
    ~play();
    void changeFigure(QPushButton* button, QString str);//改变卡牌图片
    void invisibleAllCards();
    void showCardsInHand(PokerCardsInHand *A);
    void invisibleCardsInShow();
    void gameOrder();//游戏进程
    void computerOperation(string);//电脑
    void plzhCards(PokerCardsInHand*, int&, int&);//排列组合

signals:
    void exitBack();

private slots:
    void on_exit_clicked();

    void on_restart_clicked();

    void on_cardsClicked();

    void on_deal_clicked();

    void on_pushButton_clicked();

    void on_prompt_clicked();

private:
    Ui::play *ui;
    PokerCardLibrary *a;//牌库
    PokerCardsInHand *A;//玩家手牌
    PokerCardsInHand *B;//电脑A
    PokerCardsInHand *C;//电脑B
    PokerCard symbolCard;//标记牌
    int order;//记录游戏进程
    int pass;//记录不出牌情况
    int deal;//判断是否是自由出牌
    int kind; //用于记录已打出的牌的种类
    int cardsNumberOut; //用于记录已打出的牌的张数
    bool flagForR;//用于判断是否排列组合成功
    bool finish;//游戏结束
    vector<PokerCard> hh;//用于排列组合
    vector<int> kindV;//电脑出牌类型优先级
    map<int, int> autoNum;//电脑出牌数量优先级
    QMediaPlayer *player;
};


#endif // PLAY_H
