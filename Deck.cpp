#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

Deck::Deck(){
    Deck::numDecks = 2;
}

Deck::Deck(int x){
    if(x <= 0){
        cout << "You can't play without any decks" << endl;
    }
    else if(x > 6){
        cout << "That's too many decks." << endl;
    }
    else{
        Deck::numDecks = x;
    }
}

void Deck::setNumDecks(int x){
    Deck::numDecks = x;
}

int Deck::getNumDecks(){
        return Deck::numDecks;
}

//usage: print the cards vector of the deck and then the cards vector size
void Deck::printDeck(){
    int i = 0;
    while (i < cards.size()){
        cards[i].printCard();
        i++;
    }
    cout << "Number of Cards in Deck: " << cards.size() << endl;
}

//usage: creates x decks of cards where x = numDecks and places them all into the same vector<Card> cards
void Deck::init(int numDecks){
    char face = 'a';
    int suit = 0;
    int decksMade = 0;

    while(decksMade < numDecks){
        while (suit < 4){
            while(face < 'n'){
                cards.push_back(Card(face,suit));
                face++;
            }
            suit++;
            face = 'a';
        }
        decksMade++;
        suit = 0;
    }
}

int shuffleRandom(int i){return rand()%i;}
//usage: Shuffles deck
void Deck::shuffle(){
    srand(unsigned(time(0)));
    random_shuffle(cards.begin(), cards.end(), shuffleRandom);
}
