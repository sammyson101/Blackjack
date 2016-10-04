#ifndef DECK_H
#define DECK_H
#include <Pile.h>
#include <iostream>

/*Deck inherits Public of Pile*/
class Deck: public Pile{
public:
    Deck();
    Deck(int n);
    ~Deck() {};

    int getNumDecks();
    void setNumDecks(int);
    void printDeck();
    void init(int);
    void shuffle();

private:
    int numDecks;

};

#endif // DECK_H
