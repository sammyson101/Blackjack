#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

Card::Card(char f, int s){
        setFace(f);
        setSuit(s);
        setCost();
}

void Card::setFace(char v){
    face = v;
}

string Card::getFace(){
       switch(face){
        case 'a':
            return "Ace";
            break;
        case 'b':
            return "2";
            break;
        case 'c':
            return "3";
            break;
        case 'd':
            return "4";
            break;
        case 'e':
            return "5";
            break;
        case 'f':
            return "6";
            break;
        case 'g':
            return "7";
            break;
        case 'h':
            return "8";
            break;
        case 'i':
            return "9";
            break;
        case 'j':
            return "10";
            break;
        case 'k':
            return "Jack";
            break;
        case 'l':
            return "Queen";
            break;
        case 'm':
            return "King";
            break;
        default:
            return "Error: Face value was invalid";
            break;
       }
}

void Card::setSuit(int s){
    if (s == 0){ //hearts
        suit = '\3';
    }
    else if(s == 1){ //diamonds
        suit = '\4';
    }
    else if (s == 2){ //clubs
        suit = '\5';
    }
    else if (s == 3){ //spades
        suit = '\6';
    }
}

char Card::getSuit(){
    return suit;
}

void Card::setCost(){
    switch(face){
        case 'a':
         cost = 11;
            break;
        case 'b':
            cost = 2;
            break;
        case 'c':
            cost = 3;
            break;
        case 'd':
            cost = 4;
            break;
        case 'e':
            cost = 5;
            break;
        case 'f':
            cost = 6;
            break;
        case 'g':
            cost = 7;
            break;
        case 'h':
            cost = 8;
            break;
        case 'i':
            cost = 9;
            break;
        case 'j':
            cost = 10;
            break;
        case 'k':
            cost = 10;
            break;
        case 'l':
            cost = 10;
            break;
        case 'm':
            cost = 10;
            break;
        default:
           cost = 0;
           cout << "error setting cost" << endl;
            break;
    }
}

void Card::setCost(int c){
        cost = c;
}

int Card::getCost(){
    return cost;
}

void Card::printCard(){
    cout << getFace() << getSuit() << /*" costing: " << getCost() <<*/ ' ' ;
}
