#include "play.h"
#include "ui_play.h"
#include "time.h"
#include "windows.h"
#include "mainwindow.h"
#include <QTimer>

play::play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::play)
{
    ui->setupUi(this);
    ui->computer_1->setVisible(0);
    ui->computer_2->setVisible(0);
    ui->pushButton->setVisible(0);
    this->setWindowTitle("play");
    invisibleAllCards();
    invisibleCardsInShow();
    for(int i = 0; i < 20; ++i)
    {
        connect(this->findChild<QPushButton *>("button_" + QString::number(i)), SIGNAL(clicked()), this, SLOT(on_cardsClicked()));//按下卡牌的动作
    }
    kindV = {11, 10, 9 ,8 ,7 ,6 ,5 ,4 ,3 ,2 ,1 ,0 };//电脑出牌类型优先级
    autoNum[0] = 1;
    autoNum[1] = 2;
    autoNum[2] = 6;
    autoNum[3] = 5;
    autoNum[4] = 3;
    autoNum[5] = 4;
    autoNum[6] = 5;
    autoNum[7] = 8;
    autoNum[8] = 10;
    autoNum[9] = 4;
    autoNum[10] = 6;
    autoNum[11] = 8;
    pass = 0;
    cardsNumberOut = 0;
    ui->deal->setVisible(0);
    ui->prompt->setVisible(0);
}

play::~play()
{
    delete ui;
}

void play::changeFigure(QPushButton* button, QString str)//改变ui界面卡牌的图片
{
    button->setStyleSheet("QPushButton{border-image:url(:/PokerCardsPhoto/"+str+")}");
}

void play::invisibleAllCards()
{
    for (int i = 0; i < 20; ++i)
    {
        QPushButton* card = this->findChild<QPushButton *>("button_" + QString::number(i));
        card->setVisible(0);
        card->setGeometry(card->x(), 680, card->width(), card->height());
    }
}

void play::invisibleCardsInShow()
{
    for (int i = 0; i < 20; ++i)
    {
        QPushButton* card = this->findChild<QPushButton *>("button_" + QString::number(i+20));
        card->setVisible(0);
    }
}

void play::showCardsInHand(PokerCardsInHand *A)
{
    for (int i = 0; i < A->getCardsNum(); ++i){
        QPushButton* card = this->findChild<QPushButton *>("button_" + QString::number(i));
        card->setVisible(1);
        card->setGeometry(card->x(), 680, card->width(), card->height());
        changeFigure(this->findChild<QPushButton *>("button_" + QString::number(i)), A->showCards(i));
    }
}

void play::on_exit_clicked()
{
    emit exitBack();
    this->close();
}

void play::on_restart_clicked()//全部设为初始值且重新发牌
{
    player = new QMediaPlayer;
    pass = 0;
    order = 0;
    kind = 20;
    finish = 0;
    deal = 0;
    cardsNumberOut = 0;
    symbolCard.setFigure("");
    ui->deal->setEnabled(1);
    ui->computer_1->setVisible(1);
    ui->computer_2->setVisible(1);
    ui->pushButton->setVisible(1);
    ui->label_remind->setText("");
    ui->com_remind1->setText("");
    ui->com_remind2->setText("");
    invisibleAllCards();
    invisibleCardsInShow();
    PokerCardLibrary *cards = new PokerCardLibrary(54);
    cards->shuffleCards();
    A = new PokerCardsInHand(20, cards->getCards(0,20));
    B = new PokerCardsInHand(17, cards->getCards(20, 17));
    C = new PokerCardsInHand(17, cards->getCards(37, 17));
    ui->computer_1->setText(QString(to_string(B->getCardsNum()).c_str()));
    ui->computer_2->setText(QString(to_string(C->getCardsNum()).c_str()));
    A->orderCards();
    B->orderCards();
    C->orderCards();
    showCardsInHand(A);
    ui->deal->setVisible(1);
    ui->prompt->setVisible(1);
    gameOrder();
}

void play::gameOrder()//游戏进程
{
    if(finish) return;
    if(A->getCardsNum() == 0)//牌是否打完
    {
        finish = 1;
        Dialog *a = new Dialog("YOU WIN!!!");
        a->show();
        connect(a, &Dialog::again,this,[=](){
            a->close();
            on_restart_clicked();
        });
        connect(a, &Dialog::back,this,[=](){
            a->close();
            on_exit_clicked();
        });
    }

    if(B->getCardsNum() == 0)
    {
        finish = 1;
        Dialog *a = new Dialog("YOU LOSE!!!");
        a->show();
        this->hide();
        connect(a, &Dialog::again,this,[=](){
            a->close();
            this->show();
            on_restart_clicked();
        });
        connect(a, &Dialog::back,this,[=](){
            a->close();
            on_exit_clicked();
        });
    }

    if(C->getCardsNum() == 0)
    {
        finish = 1;
        Dialog *a = new Dialog("YOU LOSE!!!");
        a->show();
        connect(a, &Dialog::again,this,[=](){
            a->close();
            on_restart_clicked();
        });
        connect(a, &Dialog::back,this,[=](){
            a->close();
            on_exit_clicked();
        });
    }

    if(pass == 6)
    {
        pass = 0;
        order = 0;
        kind = 20;
        cardsNumberOut = 0;
        symbolCard.setFigure("");
        invisibleCardsInShow();
        deal = 1;
    }

    if(order%3 == 0)
    {
        ui->prompt->setEnabled(1);
        if(deal == 0) ui->pushButton->setEnabled(1);
        ui->deal->setEnabled(1);
        ui->label_remind->setText("该你了！！！");
        deal = 0;
    }

    //延时
    QEventLoop loop;
    QTimer::singleShot(2000, &loop, SLOT(quit()));
    loop.exec();

    if(pass == 5)
    {
        pass = 0;
        order = 1;
        kind = 20;
        cardsNumberOut = 0;
        symbolCard.setFigure("");
        invisibleCardsInShow();
    }

    if(order%3 == 1)
    {
        computerOperation("C");
    }

    //延时
    QEventLoop loop2;
    QTimer::singleShot(2000, &loop2, SLOT(quit()));
    loop2.exec();

    if(pass == 3)
    {
        pass = 0;
        order = 2;
        kind = 20;
        cardsNumberOut = 0;
        symbolCard.setFigure("");
        invisibleCardsInShow();
    }

    if(order%3 == 2)
    {
        computerOperation("B");
    }

}


void play::on_cardsClicked()
{
    QPushButton *card = (QPushButton*) sender();
    if(card->y()==680)
    card->setGeometry(card->x(), 660, card->width(), card->height());
    else
    card->setGeometry(card->x(), 680, card->width(), card->height());
}


void play::on_deal_clicked()//出牌，检测是否符合规则
{
    int n = 0;
    vector<PokerCard> cardsClicked;
    for(int i = 0; i < 20; ++i)
    {
        QPushButton *card = this->findChild<QPushButton *>("button_" + QString::number(i));
        if(card->y()==660){
            cardsClicked.push_back(A->getCards(i, 1)[0]);
        }
    }
    PokerCardsOut cardsAboutOut(cardsClicked);
    if(cardsAboutOut.ifValid(symbolCard, kind))
    {
        symbolCard = cardsAboutOut.getSymbolCard();
        kind = cardsAboutOut.getKind();
        cardsNumberOut = cardsAboutOut.getCardsNum();
        invisibleCardsInShow();
        ui->label_remind->setText("");
        for(int i = 0; i < 20; ++i)
        {
            QPushButton *card = this->findChild<QPushButton *>("button_" + QString::number(i));
            //出牌
            if(card->y()==660){
                A->getAndRemoveCards(i-n, 1);
                QPushButton *but = this->findChild<QPushButton *>("button_" + QString::number(39 - n));
                but->setVisible(1);
                but->setStyleSheet(card->styleSheet());
                n = n + 1;
            }
        }
        player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/out.mp3"));
        player->setVolume(15);
        player->play();
        pass = 0;
        invisibleAllCards();
        showCardsInHand(A);
        ui->deal->setEnabled(0);
        ui->prompt->setEnabled(0);
        ui->pushButton->setEnabled(0);
        order+=1;
        gameOrder();
    }
    else
    {
        ui->label_remind->setText("你的出牌不符合规则");
        invisibleAllCards();
        showCardsInHand(A);
    }
}

void play::computerOperation(string a)
{
    if (a == "B")
    {
        ui->com_remind2->setText("");
        int m = 0;
        int n = 0;
        hh.clear();
        flagForR = 0;

        if(kind == 20)
        {
            invisibleCardsInShow();
            for(size_t t = 0; t < kindV.size(); ++t)
            {
                hh.clear();
                kind = kindV[t];
                symbolCard.setFigure("");
                cardsNumberOut = autoNum[kind];
                m = 0;
                n = 0;
                plzhCards(B, m, n);
                if(flagForR)
                {
                    invisibleCardsInShow();
                    PokerCardsOut outC(hh);
                    symbolCard.setFigure("");
                    outC.ifValid(symbolCard, kind);
                    symbolCard = outC.getSymbolCard();
                    kind = outC.getKind();
                    cardsNumberOut = outC.getCardsNum();
                    for(int i = 0; i < B->getCardsNum(); ++i)
                    {
                        for(size_t j = 0; j < hh.size(); ++j)
                        {
                            if(B->getCards(i, 1)[0] == hh[j])
                            {
                                QPushButton *but = this->findChild<QPushButton *>("button_" + QString::number(39 - j));
                                but->setVisible(1);
                                changeFigure(but, B->showCards(i));
                                PokerCard card = B->getAndRemoveCards(i, 1)[0];
                            }
                        }
                    }
                    player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/music/out.mp3"));
                    player->setVolume(15);
                    player->play();
                    break;
                }
            }
        }
        else
        {
            plzhCards(B, m, n);
            if(flagForR)
            {
                invisibleCardsInShow();
                PokerCardsOut outC(hh);
                outC.ifValid(symbolCard, kind);
                symbolCard = outC.getSymbolCard();
                kind = outC.getKind();
                cardsNumberOut = outC.getCardsNum();
                for(int i = 0; i < B->getCardsNum(); ++i)
                {
                    for(size_t j = 0; j < hh.size(); ++j)
                    {
                        if(B->getCards(i, 1)[0] == hh[j])
                        {
                            QPushButton *but = this->findChild<QPushButton *>("button_" + QString::number(39 - j));
                            but->setVisible(1);
                            changeFigure(but, B->showCards(i));
                            PokerCard card = B->getAndRemoveCards(i, 1)[0];
                        }
                    }
                }
                player = new QMediaPlayer;
                player->setMedia(QUrl("qrc:/music/out.mp3"));
                player->setVolume(15);
                player->play();
                pass = 0;
            }
            else
            {
                ui->com_remind2->setText("不出！");
                pass += 4;
            }

        }
        hh.clear();
        ui->computer_1->setText(QString(to_string(B->getCardsNum()).c_str())); //电脑手牌张数改变
        order += 1;
        gameOrder();
    }

    else if(a == "C")
    {
        ui->com_remind1->setText("");
        int m = 0;
        int n = 0;
        hh.clear();
        flagForR = 0;
        if(kind == 20)
        {
            invisibleCardsInShow();
            for(size_t t = 0; t < kindV.size(); ++t)
            {
                m = 0;
                n = 0;
                hh.clear();
                kind = kindV[t];
                symbolCard.setFigure("");
                cardsNumberOut = autoNum[kind];
                plzhCards(C, m, n);
                if(flagForR == 1)
                {
                    invisibleCardsInShow();
                    PokerCardsOut outC(hh);
                    symbolCard.setFigure("");
                    outC.ifValid(symbolCard, kind);
                    symbolCard = outC.getSymbolCard();
                    kind = outC.getKind();
                    cardsNumberOut = outC.getCardsNum();
                    for(int i = 0; i < C->getCardsNum(); ++i)
                    {
                        for(size_t j = 0; j < hh.size(); ++j)
                        {
                            if(C->getCards(i, 1)[0] == hh[j])
                            {
                                QPushButton *but = this->findChild<QPushButton *>("button_" + QString::number(39 - j));
                                but->setVisible(1);
                                changeFigure(but, C->showCards(i));
                                PokerCard card = C->getAndRemoveCards(i, 1)[0];
                            }
                        }
                    }
                    player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/music/out.mp3"));
                    player->setVolume(15);
                    player->play();
                    break;
                }
            }
        }
        else
        {
            plzhCards(C, m, n);
            if(flagForR)
            {
                invisibleCardsInShow();
                PokerCardsOut outC(hh);
                outC.ifValid(symbolCard, kind);
                symbolCard = outC.getSymbolCard();
                kind = outC.getKind();
                cardsNumberOut = outC.getCardsNum();
                for(int i = 0; i < C->getCardsNum(); ++i)
                {
                    for(size_t j = 0; j < hh.size(); ++j)
                    {
                        if(C->getCards(i, 1)[0] == hh[j])
                        {
                            QPushButton *but = this->findChild<QPushButton *>("button_" + QString::number(39 - j));
                            but->setVisible(1);
                            changeFigure(but, C->showCards(i));
                            PokerCard card = C->getAndRemoveCards(i, 1)[0];
                        }
                    }
                }
                player = new QMediaPlayer;
                player->setMedia(QUrl("qrc:/music/out.mp3"));
                player->setVolume(15);
                player->play();
                pass = 0;
            }
            else
            {
                ui->com_remind1->setText("不出！");
                pass += 2;
            }
        }
        hh.clear();
        ui->computer_2->setText(QString(to_string(C->getCardsNum()).c_str()));
        order += 1;
        gameOrder();
    }
}

void play::on_pushButton_clicked()
{
    invisibleAllCards();
    showCardsInHand(A);
    ui->label_remind->setText("");
    invisibleAllCards();
    showCardsInHand(A);
    ui->deal->setEnabled(0);
    ui->prompt->setEnabled(0);
    ui->pushButton->setEnabled(0);
    if(order%3==0) order += 1;  //不出牌 过
    pass += 1;
    gameOrder();
}

void play::on_prompt_clicked() //提示 已知卡牌数量 标志卡牌 用排列组合
{
    if(kind != 20)
    {
        invisibleAllCards();
        showCardsInHand(A);
        flagForR = 0;
        int index = 0;
        int num = 0;
        hh.clear();
        plzhCards(A, index, num);

        if(flagForR == 1)
        {
            //输出提示
            for(int i = 0; i <A->getCardsNum(); ++i)
            {
                for(int k = 0; k < cardsNumberOut; ++k)
                {
                    if(A->getCards(i, 1)[0] == hh[k])
                    {
                        QPushButton *card = this->findChild<QPushButton *>("button_" + QString::number(i));
                        card->setGeometry(card->x(), 660, card->width(), card->height());
                    }
                }
            }
        }

        else ui->label_remind->setText("没有合适的出牌");
    }
    else ui->label_remind->setText("自己想!!!");
}

void play::plzhCards(PokerCardsInHand *X, int& index, int& num)
{
    for(int i = index; i < X->getCardsNum(); ++i)
    {
        if(flagForR) break;

        else if (num < cardsNumberOut)
        {
            hh.push_back(X->getCards(i, 1)[0]);  //添加卡牌
            num = num + 1;
        }

        if(num == cardsNumberOut)
        {
            PokerCardsOut outC(hh);
            if(outC.ifValid(symbolCard, kind)) flagForR = 1;  //合法
            else
            {
                hh.pop_back(); //不合法则移除最后一张牌 进入下一个循环
                num = num - 1;
            }
        }
        else
        {
            index = i + 1;
            plzhCards(X, index, num);  //进入下一层递归 递归的层数和要出的牌数相同
        }
    }
    if(flagForR) return;
    if(hh.size() != 0)
    {
        hh.pop_back();  //退出该层递归 移除一张牌
        num = num - 1;
    }
}
