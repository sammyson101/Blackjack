#include "Hand.h"
#include "Card.h"
#include "Deck.h"

using namespace std;


Hand::Hand(){}
Hand::~Hand(){}

/*Print the individual cards and the total cost of the hand */
void Hand::printCards(){
    unsigned int i = 0;
    while(i < cards.size()){
        cards[i].printCard();
        i++;
    }
    /*Before printing the cost of the hand check ifBust so Aces are updated as needed*/
    if(checkBust(handCount())){
        cout << " Busted" << endl;
        return;
    }
    cout << "   Costing: " << handCount() << "     Bet: " << currentBet;
}

/*Returns the total count of a hand*/
int Hand::handCount(){
    unsigned int i = 0;
    int handCount = 0;
    while(i<cards.size()){
        handCount = handCount + cards[i].getCost();
        i++;
    }
    return handCount;
}

/*Checks whether or not a hand has busted.
Called via hand.checkBust(hand.handCount())*/
bool Hand::checkBust(int c){
    if (c > 21){
        //check for ace
        unsigned int i = 0;
        while(i < cards.size()){
                //if Ace is found AND its not already a 1 : change its cost to a 1
            if (cards[i].getFace() == "Ace" && cards[i].getCost() != 1){
                cards[i].setCost(1);
                break;
            }
            i++;
        }
        //recheck handCost with new ace value
        if(handCount() > 21){
            //cout << "You busted" << endl;
            return true;
        }
    }
    //cout << "You didn't bust" << endl;
    return false;

}


/*Check if a hand is able to be split*/
bool Hand::isPair(){
    if(cards[0].getFace() == cards[1]. getFace() && cards.size() == 2){
        return true;
    }
    return false;
    }
