#ifndef FOUNDATION_HPP
#define FOUNDATION_HPP

#include "types.hpp"


//This creates an object for each of the four foundations where the cards are placed at the end.
struct Foundation {
    int stack[CARDS_IN_SUIT];
    int cards = 0;

    void printFoundationCard();
};



#endif