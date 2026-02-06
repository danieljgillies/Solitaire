#ifndef DECK_HPP
#define DECK_HPP

#include <solitaire/types.hpp>


struct Deck {
    int cards[ALL_DECK_SIZE];
    int currentCard = 0;
    
    void fill();
    void shuffle();
    void print();

    private:

};




#endif