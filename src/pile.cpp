#include <solitaire/pile.hpp>
#include <iostream>


void Pile::printPile(bool hidden) {
    for (int i = 0; i < cardNumber; i++) {
        if (i >= revealed || !hidden) {
            printCard(pile[i]);
        } else {
            std::cout << "** ";
        }
    }
    std::cout << std::endl;
}


void Pile::updatePile() {
    if (revealed == cardNumber && revealed > 0) {
        revealed--;
    }
}