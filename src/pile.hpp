#ifndef PILE_HPP
#define PILE_HPP

#include "types.hpp"

struct Pile {
    int pile[MAX_PILE_SIZE];
    int revealed;
    int cardNumber;

    void printPile(bool hidden);
    void updatePile();

};

#endif