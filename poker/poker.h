#ifndef POKER_H
#define POKER_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <array>
#include <ctime>
#include <errno.h>
#include <iomanip>
#include <algorithm>
#include <QString>

using namespace std;

namespace poker {
class PokerCard;
class PokerCardLibrary;
class PokerCardsInHand;
}

class PokerCard//单张牌
{
public:
    PokerCard ();
    PokerCard (QString fig, QString pat);
    ~PokerCard ();
    void setFigure(QString);
    QString getFigure ();//得到点数
    QString getPattern ();//得到花色
    int getFigureLarge();//得到点数的大小
    bool ifSamePattern (PokerCard &a);//判断两张牌的点数是否相同
    bool ifSameFigure (PokerCard &a);//判断两张牌的花色是否相同
    PokerCard& operator=(const PokerCard &p);
    bool operator>(PokerCard &p);//比大小，排序使用
    bool operator<(PokerCard &p);//
    bool operator==(PokerCard &p);//
private:
    QString figure;//点数
    QString pattern;//花色
};

class PokerCardLibrary//牌库
{
public:
    PokerCardLibrary (int num = 54);//初始化
    ~PokerCardLibrary ();
    void shuffleCards ();//打乱卡牌
    vector<PokerCard> getCards (int start, int number);//得到一组牌，从start开始抽取number张牌
    PokerCardLibrary& operator=(const PokerCardLibrary &pl);
    QString showCards(int n);//返回第n张牌图片地址，用于显示图片
private:
    vector<PokerCard> cards;
    int cardsNum;
};

class PokerCardsInHand//手牌
{
public:
    PokerCardsInHand (int num = 0, vector<PokerCard> drawCards = vector<PokerCard> ());//初始化
    ~PokerCardsInHand ();
    void orderCards ();//给手牌排序
    int getCardsNum ();//返回手牌张数
    vector<PokerCard> getCards (int start, int number);//得到一组牌，从start开始抽取number张牌
    vector<PokerCard> getAndRemoveCards (int start, int number);//打出牌
    QString showCards(int n);//返回第n张牌图片地址，用于显示图片
private:
    vector<PokerCard> cards;
    int cardsNum;
};


class PokerCardsOut//出牌
{
public:
    PokerCardsOut(vector<PokerCard> outCards = vector<PokerCard> ());//初始化
    ~PokerCardsOut();
    int getCardsNum();//得到出牌数量
    bool ifValid();//判断是否合法（无上家出牌）
    bool ifValid(PokerCard symbolCard, int kind);//判断是否合法（上家出牌）
    int getKind();//出牌类型
    PokerCard getSymbolCard();//出牌的大小

private:
    vector<PokerCard> cards;
    PokerCard symCard;
    int kinder;
    int num;
    bool ifLarger(PokerCard symbolCard);//判断是否比上家牌大
    bool ifInSingle();//规则
    bool ifInPair();
    bool ifInEvenPair();
    bool ifInFulsh();
    bool ifInAAA();
    bool ifInAAAB();
    bool ifInAAABB();
    bool ifInPlane();
    bool ifInPlanePair();
    bool ifInBomb();
    bool ifInAAAABC();
    bool ifInAAAABBCC();
};
#endif
