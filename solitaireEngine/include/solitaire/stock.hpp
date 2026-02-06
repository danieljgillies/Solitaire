#ifndef STOCK_HPP
#define STOCK_HPP

#include <solitaire/types.hpp>

//When a card leaves the stock we just say that it is now no card at that position. 
struct Stock {
    //For efficiency could change initial faceCard to 0.
    int stack[STOCK_SIZE];
    int cardsLeft = STOCK_SIZE;
    int faceCard = -1;

    void printStock();

    void printAllStock();

    bool turnStock();

    bool displayingCard();
};


#endif