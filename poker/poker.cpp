#include "poker.h"
#include <qdebug.h>

vector<QString> figures = {"3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2",  "SMALLJOKER", "BIGJOKER"};
vector<QString> patterns = {"Spake", "Heart", "Diamond", "Club", "Blank"}; //黑桃 红桃 方块 梅花

PokerCard::PokerCard ()
{
    figure = "";
    pattern = "";
}

PokerCard::PokerCard (QString fig, QString pat)
{
    figure = fig;
    pattern = pat;
}

PokerCard::~PokerCard ()
{
    figure = "";
    pattern = "";
}

void PokerCard::setFigure(QString str)
{
    this->figure = str;
}

QString PokerCard::getFigure ()
{
    return figure;
}

QString PokerCard::getPattern ()
{
    return pattern;
}

int PokerCard::getFigureLarge()
{
    for(size_t i = 0; i < figures.size(); ++i)
    {
        if(this->getFigure() == figures[i]) return i;
    }
    return 0;
}

bool PokerCard::ifSamePattern (PokerCard &a)
{
    if (a.pattern == this->pattern) return true;
    return false;
}

bool PokerCard::ifSameFigure (PokerCard &a)
{
    if (a.figure == this->figure) return true;
    return false;
}

void swapCards (PokerCard &a, PokerCard &b)
{
    PokerCard c;
    c=a;
    a=b;
    b=c;
}

PokerCard& PokerCard::operator=(const PokerCard &p)
{
    this->figure = p.figure;
    this->pattern = p.pattern;
    return *this;
}

bool PokerCard::operator>(PokerCard &a)
{
    if(this->getFigureLarge() > a.getFigureLarge()) return true;
    if(this->figure == a.figure && this->pattern > a.pattern) return true;
    return false;
}

bool PokerCard::operator<(PokerCard &a)
{
    if(this->getFigureLarge() < a.getFigureLarge()) return true;
    if(this->figure == a.figure && this->pattern < a.pattern) return true;
    return false;
}

bool PokerCard::operator==(PokerCard &a)
{
    if(this->figure == a.figure && this->pattern == a.pattern) return true;
    return false;
}


//Poker card library
PokerCardLibrary::PokerCardLibrary(int num)
{
    for (int i = 0; i < num-2; ++i)
    {
        cards.push_back(PokerCard(figures[i/4], patterns[i%4]));
    }
    cards.push_back(PokerCard("SMALLJOKER", "Blank"));
    cards.push_back(PokerCard("BIGJOKER", "Blank"));
    cardsNum = num;
}

PokerCardLibrary::~PokerCardLibrary()
{
    cards.clear();
    cardsNum = 0;
}

void PokerCardLibrary::shuffleCards()
{
    vector<PokerCard> cardsRam;
    cardsRam = this->cards;
    random_shuffle(cardsRam.begin(), cardsRam.end());
    this->cards = cardsRam;
}

vector<PokerCard> PokerCardLibrary::getCards (int start, int number)
{
    if (start + number > cardsNum) perror("out of index!");
    vector<PokerCard> cardsRet;
    for (int i = 0; i< number; ++i)
    {
        cardsRet.push_back(cards[start+i]);
    }
    return cardsRet;
}

PokerCardLibrary& PokerCardLibrary::operator=(const PokerCardLibrary &pl)
{
    if (this->cards.size() != 0)
    {
        cards.clear();
    }
    this->cardsNum = pl.cardsNum;
    this->cards = pl.cards;
    return *this;
}

QString PokerCardLibrary::showCards (int n)
{
    PokerCard a = this->getCards(n, 1)[0];
    return a.getFigure()+a.getPattern()+".jpg";
}

//Poker Card In Hand
PokerCardsInHand::PokerCardsInHand(int num, vector<PokerCard> drawCards)
{
    cardsNum = num;
    cards = drawCards;
}

PokerCardsInHand::~PokerCardsInHand()
{
    cardsNum = 0;
    cards.clear();
}

void PokerCardsInHand::orderCards()
{
    for (int i = 0; i < cardsNum - 1; ++i)
    {
        for (int j = 0; j < cardsNum - i - 1; ++j)
        {
            if (cards[j] > cards[j+1]) swapCards (cards[j], cards[j+1]);
        }
    }
}

int PokerCardsInHand::getCardsNum()
{
    return cardsNum;
}

vector<PokerCard> PokerCardsInHand::getCards (int start, int number)
{
    if (start + number > cardsNum) perror("out of index!");
    vector<PokerCard> cardsRet;
    for (int i = 0; i< number; ++i)
    {
        cardsRet.push_back(cards[start+i]);
    }
    return cardsRet;
}

vector<PokerCard> PokerCardsInHand::getAndRemoveCards (int start, int number)
{
    if (start + number > cardsNum) perror("out of index!");
    vector<PokerCard> cardsRem;
    for (int i = 0; i < number; ++i)
    {
        cardsRem.push_back(cards[start+i]);
    }

    //remove
    cards.erase(cards.begin() + start, cards.begin() + start + number);
    cardsNum = cardsNum - number;
    return cardsRem;
}

QString PokerCardsInHand::showCards (int n)
{
    PokerCard a = this->getCards(n, 1)[0];
    return a.getFigure()+a.getPattern()+".jpg";
}

PokerCardsOut::PokerCardsOut(vector<PokerCard> outCards)
{
    num = 0;
    cards = outCards;
}
PokerCardsOut::~PokerCardsOut()
{
    num = 0;
    cards.clear();
}

bool PokerCardsOut::ifValid()
{
    bool flag = false;
    if(this->ifInSingle()) flag = 1;
    else if(this->ifInPair()) flag = 1;
    else if(this->ifInEvenPair()) flag = 1;
    else if(this->ifInFulsh()) flag = 1;
    else if(this->ifInAAA()) flag = 1;
    else if(this->ifInAAAB()) flag = 1;
    else if(this->ifInAAABB()) flag = 1;
    else if(this->ifInPlane()) flag = 1;
    else if(this->ifInPlanePair()) flag = 1;
    else if(this->ifInBomb()) flag = 1;
    else if(this->ifInAAAABC()) flag = 1;
    else if(this->ifInAAAABBCC()) flag = 1;
    if(flag) num = cards.size();
    return flag;
}

bool PokerCardsOut::ifValid(PokerCard symbolCard, int kind)
{
    if(kind == 20) return ifValid();
    else {
        bool flag = false;
        if(kind == 0) flag = this->ifInSingle();
        else if(kind == 1) flag = this->ifInPair();
        else if(kind == 2) flag = this->ifInEvenPair();
        else if(kind == 3) flag = this->ifInFulsh();
        else if(kind == 4) flag = this->ifInAAA();
        else if(kind == 5) flag = this->ifInAAAB();
        else if(kind == 6) flag = this->ifInAAABB();
        else if(kind == 7) flag = this->ifInPlane();
        else if(kind == 8) flag = this->ifInPlanePair();
        else if(kind == 9) flag = this->ifInBomb();
        else if(kind == 10) flag = this->ifInAAAABC();
        else if(kind == 11) flag = this->ifInAAAABBCC();
        if(flag && this->ifLarger(symbolCard)) num = cards.size();
        return flag && this->ifLarger(symbolCard);
    }
}

int PokerCardsOut::getKind()
{
    return this->kinder;
}

PokerCard PokerCardsOut::getSymbolCard()
{
    return this->symCard;
}

int PokerCardsOut::getCardsNum()
{
    return this->num;
}

bool PokerCardsOut::ifLarger(PokerCard symbolCard)
{
    return symCard.getFigureLarge() > symbolCard.getFigureLarge();
}

bool PokerCardsOut::ifInSingle()
{
    if(cards.size() == 1)
    {
        kinder = 0;
        symCard = cards[0];
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInPair()
{
    if(cards.size() == 2 && cards[0].ifSameFigure(cards[1]))
    {
        kinder = 1;
        symCard = cards[0];
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInEvenPair()
{
    if(cards.size() < 6 || cards.size()%2 != 0) return false;
    for(size_t i = 0; i < cards.size()-1; ++i)
    {
        if(i%2 == 0)
        {
            if(!cards[i].ifSameFigure(cards[i+1])) return false;
        }
        else
        {
            if(cards[i].getFigureLarge() != cards[i+1].getFigureLarge() - 1) return false;
        }
    }
    kinder = 2;
    symCard = cards[0];
    return true;
}

bool PokerCardsOut::ifInFulsh()
{
    if(cards.size() < 5) return false;
    for(size_t i = 0; i < cards.size(); ++i)
    {
        if(cards[i].getFigure() == "2" ||
           cards[i].getFigure() == "SMALLJOKER" ||
           cards[i].getFigure() == "BIGJOKER") return false;
    }
    for(size_t i = 0; i < cards.size() - 1; ++i)
    {
        if(cards[i].getFigureLarge() != cards[i+1].getFigureLarge() - 1) return false;
    }
    kinder = 3;
    symCard = cards[0];
    return true;
}

bool PokerCardsOut::ifInAAA()
{
    if(cards.size() != 3) return false;
    else if(cards[0].getFigure() == cards[1].getFigure() && cards[1].getFigure() == cards[2].getFigure())
    {
        kinder = 4;
        symCard = cards[0];
        return true;
    }
    return false;
}
bool PokerCardsOut::ifInAAAB()
{
    if(cards.size() != 4) return false;
    else if(cards[0].getFigure() == cards[1].getFigure() && cards[1].getFigure() == cards[2].getFigure() && cards[2].getFigure() != cards[3].getFigure())
    {
        symCard = cards[0];
        kinder = 5;
        return true;
    }
    else if(cards[0].getFigure() != cards[1].getFigure() && cards[1].getFigure() == cards[2].getFigure() && cards[2].getFigure() == cards[3].getFigure())
    {
        symCard = cards[1];
        kinder = 5;
        return true;
    }
    return false;
}
bool PokerCardsOut::ifInAAABB()
{
    if(cards.size() != 5) return false;
    else if(cards[0].getFigure() == cards[1].getFigure() && cards[1].getFigure() == cards[2].getFigure() && cards[3].getFigure() == cards[4].getFigure())
    {
        symCard = cards[0];
        kinder = 6;
        return true;
    }
    else if(cards[0].getFigure() == cards[1].getFigure() && cards[2].getFigure() == cards[3].getFigure() && cards[3].getFigure() == cards[4].getFigure())
    {
        symCard = cards[2];
        kinder = 6;
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInPlane()
{
    if(cards.size() != 8) return false;

    else if(cards[2].getFigure() == cards[3].getFigure()
            && cards[3].getFigure() == cards[4].getFigure()
            && cards[4].getFigureLarge() + 1 == cards[5].getFigureLarge()
            && cards[5].getFigure() == cards[6].getFigure()
            && cards[6].getFigure() == cards[7].getFigure()
            && cards[7].getFigure() != "2")
    {
        symCard = cards[2];
        kinder = 7;
        return true;
    }
    else if(cards[1].getFigure() == cards[2].getFigure()
            && cards[2].getFigure() == cards[3].getFigure()
            && cards[3].getFigureLarge() + 1 == cards[4].getFigureLarge()
            && cards[4].getFigure() == cards[5].getFigure()
            && cards[5].getFigure() == cards[6].getFigure()
            && cards[6].getFigure() != "2")
    {
        symCard = cards[1];
        kinder = 7;
        return true;
    }
    else if(cards[0].getFigure() == cards[1].getFigure()
            && cards[1].getFigure() == cards[2].getFigure()
            && cards[2].getFigureLarge() + 1 == cards[3].getFigureLarge()
            && cards[3].getFigure() == cards[4].getFigure()
            && cards[4].getFigure() == cards[5].getFigure()
            )
    {
        symCard = cards[0];
        kinder = 7;
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInPlanePair()
{
    if(cards.size() != 10) return false;

    else if(cards[0].getFigure() == cards[1].getFigure()
            && cards[2].getFigure() == cards[3].getFigure()
            && cards[4].getFigure() == cards[5].getFigure()
            && cards[5].getFigure() == cards[6].getFigure()
            && cards[6].getFigureLarge() + 1 == cards[7].getFigureLarge()
            && cards[7].getFigure() == cards[8].getFigure()
            && cards[8].getFigure() == cards[9].getFigure()
            && cards[9].getFigure() != "2")
    {
        symCard = cards[4];
        kinder = 8;
        return true;
    }
    else if(cards[0].getFigure() == cards[1].getFigure()
            && cards[2].getFigure() == cards[3].getFigure()
            && cards[3].getFigure() == cards[4].getFigure()
            && cards[4].getFigureLarge() + 1 == cards[5].getFigureLarge()
            && cards[5].getFigure() == cards[6].getFigure()
            && cards[6].getFigure() == cards[7].getFigure()
            && cards[8].getFigure() == cards[9].getFigure())
    {
        symCard = cards[2];
        kinder = 8;
        return true;
    }
    else if(cards[0].getFigure() == cards[1].getFigure()
            && cards[1].getFigure() == cards[2].getFigure()
            && cards[2].getFigureLarge() + 1 == cards[3].getFigureLarge()
            && cards[3].getFigure() == cards[4].getFigure()
            && cards[4].getFigure() == cards[5].getFigure()
            && cards[6].getFigure() == cards[7].getFigure()
            && cards[8].getFigure() == cards[9].getFigure())
    {
        symCard = cards[0];
        kinder = 8;
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInBomb()
{
    if(cards.size() != 4)
    {
        if(cards.size() != 2) return false;
        else if(cards[0].getFigure() != "SMALLJOKER" || cards[1].getFigure() !="BIGJOKER") return false;
        symCard = cards[0];
        kinder = 9;
        return true;
    }
    else if (cards[0].getFigure() == cards[1].getFigure() &&
             cards[1].getFigure() == cards[2].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure())
    {
        symCard = cards[0];
        kinder = 9;
        return true;
    }
    return false;
}
bool PokerCardsOut::ifInAAAABC()
{
    if(cards.size() != 6) return false;

    else if (cards[0].getFigure() == cards[1].getFigure() &&
             cards[1].getFigure() == cards[2].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure())
    {
        symCard = cards[0];
        kinder = 10;
        return true;
    }
    else if (cards[1].getFigure() == cards[2].getFigure() &&
             cards[3].getFigure() == cards[4].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure())
    {
        symCard = cards[1];
        kinder = 10;
        return true;
    }
    else if (cards[2].getFigure() == cards[3].getFigure() &&
             cards[3].getFigure() == cards[4].getFigure() &&
             cards[4].getFigure() == cards[5].getFigure())
    {
        symCard = cards[2];
        kinder = 10;
        return true;
    }
    return false;
}

bool PokerCardsOut::ifInAAAABBCC()
{
    if(cards.size() != 8) return false;
    else if (cards[0].getFigure() == cards[1].getFigure() &&
             cards[1].getFigure() == cards[2].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure() &&
             cards[4].getFigure() == cards[5].getFigure() &&
             cards[6].getFigure() == cards[7].getFigure())
    {
        symCard = cards[0];
        kinder = 11;
        return true;
    }
    else if (cards[0].getFigure() == cards[1].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure() &&
             cards[3].getFigure() == cards[4].getFigure() &&
             cards[4].getFigure() == cards[5].getFigure() &&
             cards[6].getFigure() == cards[7].getFigure())
    {
        symCard = cards[2];
        kinder = 11;
        return true;
    }
    else if (cards[0].getFigure() == cards[1].getFigure() &&
             cards[2].getFigure() == cards[3].getFigure() &&
             cards[4].getFigure() == cards[5].getFigure() &&
             cards[5].getFigure() == cards[6].getFigure() &&
             cards[6].getFigure() == cards[7].getFigure())
    {
        symCard = cards[4];
        kinder = 11;
        return true;
    }
    return false;
}
