#ifndef CARD_H_INCLUDED__
#define CARD_H_INCLUDED__
#include <string>
using namespace std;

class Card{
public:
    Card();
    Card(char f,int s);
    ~Card(){};

    string getFace();
    void setFace(char);
    char getSuit();
    void setSuit(int);
    int getCost();
    void setCost();
    void setCost(int);
    void printCard();

private:

//Card has 3 private values:
//face will be a char between a - m that will correspond to a string that will read ace to king with ace being a and king being m
//suit is the card's suit
//cost is how much that card is worth in the game i.e. the Two of Hearts has a cost of 2. the King of Diamonds has a cost of 10

    char face;
    char suit;
    int cost;
};
#endif
