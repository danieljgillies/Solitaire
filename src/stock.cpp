#include "stock.hpp"
#include "types.hpp"

#include <iostream>




void Stock::printStock() {
    std::cout << "faceCard: " << faceCard << std::endl;
    if (faceCard == -1 || faceCard == STOCK_SIZE) {
        std::cout << "Empty" << std::endl;
        return;
    }
    printCard(stack[faceCard]);

}


void Stock::printAllStock() {
    for (int card : stack) {
        printCard(card);
    }
}


bool Stock::turnStock() {

    if (cardsLeft == 0) {
        //Illegal Move
        return false;
    }
    while (true) {
        faceCard++;
        if (faceCard >= STOCK_SIZE) {
            faceCard = -1;
            return true;
        }
        if (stack[faceCard] != 0) {
            return true;
        }
    }
    return true;    

}

bool Stock::displayingCard() {
    return (faceCard != -1 && faceCard != STOCK_SIZE);
}
