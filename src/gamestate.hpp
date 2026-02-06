#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "types.hpp"
#include "pile.hpp"
#include "stock.hpp"
#include "foundation.hpp"


struct Gamestate {
    Foundation foundations[NUMBER_OF_SUITS];
    Stock stock;
    Pile piles[NUMBER_OF_PILES];
    int moves = 0;
    int gameResult = 0;

    Gamestate() {
        for (int i = 0; i < NUMBER_OF_PILES; i++) {
            piles[i].revealed = i;
            piles[i]. cardNumber = i + 1;
        }
    }

    void startGame();

    void printGameState(bool hidden = true);

    bool stockToFoundation();

    bool turnStock();

    bool pileToFoundation(int pileIndex);

    bool foundationToPile(int foundationIndex, int pileIndex);

    bool pileToPile(int pileFromIndex, int pileToIndex, int numberMoved);

    bool stockToPile(int pileToIndex);


};


#endif