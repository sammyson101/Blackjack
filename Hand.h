#ifndef HAND_H
#define HAND_H
#include <Pile.h>

/*Hand inherits public of Pile*/
class Hand: public Pile{
public:
    Hand();
    ~Hand();

    int handCount();
    bool isPair();
    void printCards();
    bool checkBust(int);
    int currentBet;

private:

};

#endif // HAND_H
