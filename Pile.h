#include "Pile.h"

using namespace std;

/*move a single card from the source pile's card vector to the function caller's cards vector*/
void Pile::moveCard(Pile &source){
    cards.push_back(source.cards.back());
    source.cards.pop_back();
}
