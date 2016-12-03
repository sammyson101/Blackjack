#include <iostream>
#include <Card.h>
#include <Pile.h>
#include <Deck.h>
#include <Hand.h>
#include <Game.h>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv){
    cout << "*****BLACKJACK*****" << endl << endl;
        Game game;
        Deck deck = game.initGame();
    while(cin){
        deck.init(deck.getNumDecks());
        deck.shuffle();
    //deck.printDeck();

        game.openingDeal(deck);

/* Hardcoding cards to test various hands

    Card card1('l', 0);
    Card card2('l', 1);

    game.hands[1].cards[0] = card1;
    game.hands[1].cards[1] = card2;
*/


        if(game.prePlayerActions(deck) == false){
            game.playerActions(deck);
        }
        game.postPlayerActions(deck);
        cout << "New game starting" << endl;
        game.pause(); game.pause();
        system("cls");
    }//end while loop
  return 0;
}
