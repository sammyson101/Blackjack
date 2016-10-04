#ifndef PILE_H
#define PILE_H
#include <vector>
#include <Card.h>

/*Pile is a parent class for: Deck and Hand*/


using namespace std;

class Pile{
    public:
        Pile(){};
        ~Pile(){};
        vector<Card> cards;
        void moveCard(Pile &source);

    private:

};
#endif
