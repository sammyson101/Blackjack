#ifndef GAME_H
#define GAME_H
#include <Deck.h>
#include <Card.h>
#include <Hand.h>

class Game{
    public:
        Game();
        ~Game();

        vector<Hand> hands;   //hands is a vector of Hand. Hand has a vector of Card called cards
                              //hands[0] always belongs to the dealer
                              //all hands[i] for i > 0 belong to the player
        Deck initGame();
        string validResponseTest(string);
        void openingDeal(Deck &deck);
        bool prePlayerActions(Deck &deck);
        void playerActions(Deck &deck);
        void postPlayerActions(Deck &deck);
        void printGameState();
        void printPostGameState();
        void pause();
        void clearHands();

        int getUserMoney();
        void setUserMoney(int);

    private:
        double userMoney;
};

#endif // GAME_H
