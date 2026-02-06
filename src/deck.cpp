#include "deck.hpp"

#include <random>
#include <algorithm>
#include <iostream>


void Deck::fill() {
    int index = 0;
    for (int currentDeck = 0; currentDeck < NUMBER_OF_DECKS; currentDeck++) {
        // 1 is first card ..
        for (int card = 1; card < (DECK_SIZE + 1); card++){
            cards[index] = card;
            index++;
        }
    }

}

void Deck::shuffle() {
    std::mt19937 rng(std::random_device{}());
    std::shuffle(cards, cards + ALL_DECK_SIZE, rng);
}

void Deck::print() {
    for (int card : cards) {
        printCard(card);
    }
}
