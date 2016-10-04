#include "Game.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <stdlib.h>
#include <math.h>

using namespace std;
Game::Game(){}
Game::~Game(){}

/*Delays game's actions so that the game is readable*/
void Game::pause(){
    cout << ". ";
    _sleep(600);
    cout << ". ";
    _sleep(600);
    cout << ". ";
    _sleep(600);
}

/*Check if user's Input is valid for any Y/N question*/
string Game::validResponseTest(string question){
    bool validResponse = false;
    string response;
    cout << question;
    while (validResponse == false){
        cin >> response;
        if(response == "y" || response == "Y" || response == "n" || response == "N"){
            validResponse = true;
        }
        else{
            system("cls");
            cout << "Response not Understood" << endl;
            printGameState();
            cout << question;
        }
    }
    return response;
}

void Game::setUserMoney(int x){
    userMoney = x;
}

int Game::getUserMoney(){
    return userMoney;
}

/*Initialize the game and build the deck to be used*/
Deck Game::initGame(){
    int x = 0;
    bool valid = false;
    Deck deck;
    while (valid == false){
        cout << "How many decks would you like to play with? (1 - 5)" << endl;
        cin >> x;
        if(x > 0 && x < 6){
            deck.setNumDecks(x);
            valid = true;
        }//end if

        else{
            cin.clear();
            cin.ignore(1000,'\n');
            system("cls");
            cout << "That's not a valid number of decks" << endl;
        }//end else
    }//end while
    setUserMoney(1000);
    system("cls");
    return deck;
}//end initGame

/*Deal opening hand to player and dealer and get player's bet*/
void Game::openingDeal(Deck &deck){
    double bet = 0;
    bool valid = false;

    /*Get bet from the player*/
    while(valid == false){
        cout << "How much would you like to bet on this hand?" << endl;
        cout << "Current Money: " << getUserMoney() << endl;
        cin >> bet;

        //Check if bet was not a number
        if(cin.fail()){
            system("cls");
            cout << "That's not a number!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        //Check if bet was more than you have
        else if(bet > userMoney){
            system("cls");
            cout << "You can't bet more than you have!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        //Check if bet was in $0.50 increments
        else if(fmod(bet, 0.5)!= 0){
            system("cls");
            cout << "You can only bet in increments of $0.50!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        //Check that bet was not 0 or less
        else if(bet <= 0){
            system("cls");
            if(bet == 0){
                cout << "You must bet some amount of money!" << endl;
            }
            if(bet < 0){
                cout << "You can't bet a negative number!" << endl;
            }
            cin.clear();
            cin.ignore(1000, '\n');
        }

        //else bet is valid
        else{valid = true;}
    }//end while


    cout << "Good Luck" << endl;
    pause();
    userMoney -= bet;


    /*if the game has hands already, then we need to erase them before dealing game*/
    if(hands.size() > 0){
        hands.erase(hands.begin(), hands.end());
    }


    unsigned int i = 0;
    while(i < 2){ //magic number for 2 is the number of hands to deal: the dealer's and the player's
        Hand temp;
        temp.moveCard(deck);
        temp.moveCard(deck);
        hands.push_back(temp);
        temp.cards.clear();
        i++;
    }
    //set player's hand currentBet to be the given bet
    hands[1].currentBet = bet;
    system("cls");
}//end openingDeal

/*Prints Dealer's face-up card, all player hands and cost*/
void Game::printGameState(){
    cout << "Dealer's Hand:" << endl;
    hands[0].cards[0].printCard();
    cout << "[ * ]"<< endl;
    cout << endl << endl;
    cout << "Your Hand(s):" << endl;
    unsigned int i = 1;
    while(i < hands.size()){
        hands[i].printCards();
        cout << endl;
        i++;
    }
    cout << endl;
    cout << "Current Money: " << userMoney << endl;
}

/* A version of printGameState that will show the whole dealer's hand and compare the player's hand to the dealers*/
void Game::printPostGameState(){
    unsigned int i = 0;
    cout << "Dealer's Hand:" << endl;
    while(i < hands[0].cards.size()){
        hands[0].cards[i].printCard();
        cout << " ";
        i++;
    }
    cout << "Costing: " << hands[0].handCount();
    cout << endl << endl << endl;
    cout << "Your Hands:" << endl;
    i = 1;
    while(i < hands.size()){
        hands[i].printCards();
        cout << endl;
        i++;
    }
    cout << endl;
}

/*Pre-Player actions including: checking dealer and player blackjack and offering insurance*/
bool Game::prePlayerActions(Deck &deck){
    //look at first card in dealer's hand to see if it is an ace
        if(hands[0].cards[0].getFace() == "Ace"){
           //cout << "Ace detected" << endl;
           //offer insurance
        }
        //dealer or player has blackjack
        if(hands[0].handCount() == 21 || hands[1].handCount() == 21){
            return true;
        }
        return false;
}

/*Runs the player decisions based on stdin from user*/
void Game::playerActions(Deck &deck){
    unsigned int i = 1;
    bool stand = false;
    string response;
    bool validResponse;

    /*Master loop for player hand options*/
    while (i < hands.size()){
            //cout << "Total num of hands" << hands.size() <<endl;
            printGameState();
            cout << endl << "Options for Hand " << i << endl;
        while(stand == false){
            /*busted == true*/
            if(hands[i].checkBust(hands[i].handCount()) == true){
                stand = true; //this hand is over
                break; //break out of while since they can't hit after busting
            }

            /*busted == false. Check for split and that player has enough money to split*/
            if(hands[i].isPair() && getUserMoney() >= hands[i].currentBet){
                /*Ask if Player would like to split*/
                validResponse = false;
                response = validResponseTest("Would you like to split you hand?\nY N\n");

                    /*Player chooses to split*/
                    if(response == "Y" || response == "y"){
                        validResponse = true;

                        /*if you are splitting aces then reset both of aces value to 11*/
                        if(hands[i].cards[0].getCost() == 1 || hands[i].cards[1].getCost() == 1){
                            hands[i].cards[0].setCost();
                            hands[i].cards[1].setCost();
                        }

                        //make a second hand for player
                        Hand newHand;
                        newHand.currentBet = hands[i].currentBet;
                        setUserMoney(getUserMoney() - newHand.currentBet);

                        //grab the second card of hands[i] and place it into newHand
                        //then deal extra card to both hands
                        newHand.moveCard(hands[i]);
                        newHand.moveCard(deck);
                        hands[i].moveCard(deck);


                        //push newHand into hands
                        hands.push_back(newHand);
                        cout << endl << "SPLITTING" << endl;
                        pause();
                        system("cls");
                        printGameState();
                        //dec i so we re-look at the first hand made from the split
                        i--;
                        goto nexthand;

                    }//end if(response == y)

                    /*Player chooses not to split*/
                    else if(response == "N" || response == "n"){
                        cout << endl << "NOT SPLITTING";
                        pause();
                        system("cls");
                        validResponse = true;
                        printGameState();
                        cout << "Options for Hand: " << i << endl;
                    }//end else if(response == "n")

                    /*Player entered an invalid response for split*/
                   else{
                        system("cls");
                        cout << "Response not understood..." << endl;
                        printGameState();
                   }//end else
            }//end if(hands[i].isPair())


            /*Ask player if they would like to hit*/

            response = validResponseTest("Would you like to hit? \nY N \n");

                /*Player chooses to stand*/
                if(response == "n" || response == "N"){
                    validResponse = true;
                    stand = true;
                    cout << endl << "NOT HITTING";
                    pause();
                }//end if(response = n)

                /*Player chooses to hit*/
                else if(response == "y" || response == "Y"){
                    validResponse = true;
                    cout << endl << "HITTING" << endl;
                    pause();
                    system("cls");
                    hands[i].moveCard(deck);
                    printGameState();
                    cout << endl<< "Options for Hand: " << i << endl;
                }//end else if(response = y)

                /*Response not understood*/
                else{
                        system("cls");
                        cout << "Response not understood..." << endl;
                        printGameState();
                }//end else
        }//end while stand = false

        nexthand:
        i++; //go to next hand
        system("cls");
        stand = false; //reset hand's boolean
    }//end master while loop
}

/*Post player actions include: hitting the dealers hand, comparing player's hand to dealer's and paying out if required*/
void Game::postPlayerActions(Deck &deck){
    system("cls");
    cout << "Dealer Actions" << endl << endl;
    printPostGameState();

    /* Dealer hitting rules
        If all player's hands are busted game is over
        Dealer must hit on "hard" 17????? MAYBE??????
        Dealer must hit on anything under 16
        Else dealer must stand
    */
        bool stand = false;

        /*Check to see if all player's hands busted*/
        unsigned int i = 1;
        int handsBusted = 0;
        while (i < hands.size()){
            if(hands[i].handCount() > 21){
                handsBusted ++;
            }
            i++;
        }

       /*If all players hands busted dealer will stand since the game is over*/
        if(handsBusted == hands.size() - 1){
            //cout << "THEY ALL BUSTED";
            pause();
            stand = true;
            system("cls");
          }


    while (stand == false){

    /*
        "Hard 17 check
        if(hands[0].cards.size() == 2 && hands[0].handCount() == 17){
                cout << endl << "DEALER HITS ON A HARD 17" << endl;
                pause();
                system("cls");
                hands[0].moveCard(deck);
                cout << "Dealer Actions" << endl << endl;
                printPostGameState();
        }
    */
        /*Under 16 check*/
        /*else*/ if(hands[0].handCount() <= 16){
            cout << endl << "DEALER HITS WHILE UNDER 16" << endl;
            pause();
            system("cls");
            hands[0].moveCard(deck);
            cout << "Dealer Actions" << endl << endl;
            printPostGameState();
        }

        /*Else the Dealer stands*/
        else{
            stand = true;
            cout << endl << "DEALER STANDS WHILE 17 AND OVER" << endl;
            pause();
            cout << "Dealer Actions" << endl << endl;
            system("cls");
        }
    }//end while(stand == false)

    /*Steps for displaying end game
        Show dealer hand and cost
        loop
        show player's nth hand and cost and if it won or not
        end loop
    */
        cout << "RESULTS" << endl << endl;
        cout << "Dealer Hand:";
        /*Check if dealer has blackjack*/
        if(hands[0].cards.size() == 2 && hands[0].handCount() == 21){
            cout << "BLACKJACK";
        }
        cout << endl;

        i = 0;
        while(i < hands[0].cards.size()){
            hands[0].cards[i].printCard();
            cout << " ";
            i++;
        }

        cout << "Costing: " << hands[0].handCount();

        cout << endl << endl;

        cout << "Your Hand(s)" << endl;
        i = 1;
        unsigned int j = 0;
        //each hand
        while(i < hands.size()){
            //each card
            while(j < hands[i].cards.size()){
                hands[i].cards[j].printCard();
                j++;
            }

            /*print hand count and compare to dealer*/
            cout << "costing: " << hands[i].handCount();

            /*Hand Busts
            if (my hand has busted)*/
            if(hands[i].handCount() > 21){
                cout << "  Busted";
            }

            /*Hand is BlackJack
            payout 3:2*/
            else if(hands[i].handCount() == 21 && hands[i].cards.size() == 2){
                cout << "  BLACKJACK";
                setUserMoney(getUserMoney() + hands[i].currentBet * 2);
                setUserMoney(getUserMoney() + (hands[i].currentBet/2));
            }

             /*Hand Wins
            else if (my hand is greater than the dealers || dealer has busted
            Give user the hand's bet back time 2 since they win money*/
            else if(hands[i].handCount() > hands[0].handCount() || hands[0].handCount() > 21){
                cout << "  Wins";
                setUserMoney(getUserMoney() + hands[i].currentBet * 2);
            }

            /*Hand Loses
            else if(my hand is less than the dealer's)
            No update to userMoney as they have lost it*/
            else if(hands[i].handCount() < hands[0].handCount()){
                cout << "  Loses";
            }

            /*Hand Ties
            else we push
            Give player the hand's bet back*/
            else{
                cout << " Pushes";
                setUserMoney(getUserMoney() + hands[i].currentBet);
            }
            cout << endl;
        i++;
        j = 0;
    }//end while(i < cards.size())
    cout << endl << endl;
    //clearHands();
}
