#include <solitaire/foundation.hpp>

#include <iostream>

void Foundation::printFoundationCard() {
    if (cards == 0) {
        std::cout << "Empty" << std::endl;
        return;
    }

    printCard(stack[cards-1]);
    return;

}