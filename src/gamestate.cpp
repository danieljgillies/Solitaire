#include "gamestate.hpp"

#include <iostream>
#include <random>
#include <algorithm>
#include "deck.hpp"
#include "types.hpp"

void Gamestate::printGameState(bool hidden) {
    std::cout << std::endl;

    std::cout << "Current Stock Card: ";
    stock.printStock();

    std::cout << std::endl;

    std::cout << "Foundations: " << std::endl;
    for (Foundation foundation : foundations) {
        foundation.printFoundationCard();
    }

    std::cout << std::endl;
    std::cout << std::endl;

    for (int pile = NUMBER_OF_PILES - 1; pile >= 0; pile--) {
        std::cout << std::endl << pile + 1 << ": ";
        piles[pile].printPile(hidden);
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


void Gamestate::startGame() {
    Deck deck;
    deck.fill();
    deck.shuffle();

    for (int pile = 0; pile < NUMBER_OF_PILES;) {
        //grab the pointer starting from the beginning of deck (deck.cards) + whatever our current card is
        int* start = (deck.cards + deck.currentCard);
        //We move up one pile
        pile++;
        //The end is the next index number of cards more
        deck.currentCard += (pile);
        //We reach the end 
        int* end = (deck.cards + deck.currentCard);
        std::copy(start, end, piles[pile - 1].pile);
    }
    int* start = (deck.cards + deck.currentCard);
    deck.currentCard += STOCK_SIZE;
    int* end = (deck.cards + deck.currentCard);
    std::copy(start, end, stock.stack);


    return;
}


bool Gamestate::stockToFoundation() {
    if (!stock.displayingCard()) {
        //No card to move
        return false;
    }
    
    int stockCard = stock.stack[stock.faceCard];
    int foundationIndex = getCardSuit(stockCard);
        
    if (getCardRank(stockCard) != foundations[foundationIndex].cards) {
            //Illegal move
            return false;
    }

    foundations[foundationIndex].stack[foundations[foundationIndex].cards] = stockCard;
    foundations[foundationIndex].cards++;

    stock.stack[stock.faceCard] = 0;
    //Want to change this to move back not forward...
    stock.turnStock();
    stock.cardsLeft--;
    return true;

}


bool Gamestate::turnStock() {
    return stock.turnStock();
}

bool Gamestate::pileToFoundation(int pileIndex) {
    if (piles[pileIndex].cardNumber == 0) {
        //No piles
        return false;
    }

    int pileCard = piles[pileIndex].pile[piles[pileIndex].cardNumber - 1];
    int foundationIndex = getCardSuit(pileCard);

    if (getCardRank(pileCard) != foundations[foundationIndex].cards) {
            //Illegal move
            return false;
    }

    foundations[foundationIndex].stack[foundations[foundationIndex].cards] = pileCard;
    foundations[foundationIndex].cards++;

    piles[pileIndex].cardNumber--;
    piles[pileIndex].pile[piles[pileIndex].cardNumber] = 0;
    piles[pileIndex].updatePile();

    return true;

}


bool Gamestate::foundationToPile(int foundationIndex, int pileIndex) {
    Foundation* foundation = &foundations[foundationIndex];
    Pile* pile = &piles[pileIndex];

    if (foundation -> cards == 0) {
        //No cards
        return false;
    }

    int foundationCard = foundation -> stack[foundation -> cards -1];

    if (pile -> cardNumber == 0) {
        if (getCardRank(foundationCard) == CARDS_IN_SUIT - 1) {
                pile -> pile[pile -> cardNumber] = foundationCard;
                pile -> cardNumber++;
                pile -> updatePile();

                foundation -> cards--;
                foundation -> stack[foundation -> cards] = 0;

                return true;
        }
        // Needs to be King to go on pile
        return false;
    }

    if ((foundationIndex >> 1) == (getCardSuit(pile -> pile[pile -> cardNumber - 1] >> 1))) {
        // The two suits are equal then do not place
        return false;
    }

    if (!(getCardRank(foundationCard) == getCardRank(pile -> pile[pile -> cardNumber - 1]) + 1)) {
        // Card is not one higher
        return false;
    }

    pile -> pile[pile -> cardNumber] = foundationCard;
    pile -> cardNumber++;
    pile -> updatePile();

    foundation -> cards--;
    foundation -> stack[foundation -> cards] = 0;

    return true;
}


bool Gamestate::pileToPile(int pileFromIndex, int pileToIndex, int numberMoved) {
    if (numberMoved < 1) {
        // move at least one card
        return false;
    }
    if (pileFromIndex == pileToIndex) {
        // Need to be different piles
        return false;
    }
    
    Pile* pileFrom = &piles[pileFromIndex];

    if (pileFrom -> cardNumber < 1) {
        // Need at least one card to move!
        return false;
    }

    int topCardMovedIndex = pileFrom -> cardNumber - numberMoved;

    if (topCardMovedIndex < pileFrom -> revealed) {
        //Moving too many cards.
        return false;
    }
    
    Pile* pileTo = &piles[pileToIndex];
    int cardFrom = pileFrom -> pile[topCardMovedIndex];
    int cardTo = pileTo -> pile[topCardMovedIndex];
    
    if (pileTo -> cardNumber == 0) {
        if (getCardRank(cardFrom) == CARDS_IN_SUIT - 1) {
            int moveToIndex = pileTo -> cardNumber;

            for (; numberMoved > 0; numberMoved--) {

                pileTo -> pile[moveToIndex] = cardFrom;
                pileTo -> cardNumber++;
                moveToIndex++;

                pileFrom -> pile[topCardMovedIndex] = 0;
                pileTo -> cardNumber--;
                topCardMovedIndex++;
                cardFrom = pileFrom -> pile[topCardMovedIndex];

            }
            pileFrom -> updatePile();
            pileTo -> updatePile();
            return true;
        }
        // Needs to be King to go on pile
        return false;
    }

    if ((getCardSuit(cardFrom) >> 1) == (getCardSuit(cardTo) >> 1)) {
        //Cards are the same colour.
        std::cout << "Card from: ";
        printCard(cardFrom);
        std::cout << std::endl; 
        std::cout << "Card to: ";
        printCard(cardTo);
        std::cout << "Suit from: " << getCardSuit(cardFrom) << std::endl;
        std::cout << "Binary from: " << (getCardSuit(cardFrom) >> 1) << std::endl;
        std::cout << "Suit to: " << getCardSuit(cardTo) << std::endl;
        std::cout << "Binary from: " << (getCardSuit(cardTo) >> 1) << std::endl;
        std::cout << "Cards are same colour" << std::endl;
        return false;
    }
    if (getCardRank(cardFrom) + 1 != getCardRank(cardTo)) {
        //Card must be one higher.
        std::cout << "Card from: ";
        printCard(cardFrom);
        std::cout << std::endl; 
        std::cout << "Card to: ";
        printCard(cardTo);
        std::cout << "From rank: " << getCardRank(cardFrom) << std::endl;
        std::cout << "To rank: " << getCardRank(cardTo) << std::endl;
        std::cout << "Card must be one higher" << std::endl;
        return false;
    }

    int moveToIndex = pileTo -> cardNumber;

    for (; numberMoved > 0; numberMoved--) {

        pileTo -> pile[moveToIndex] = cardFrom;
        pileTo -> cardNumber++;
        moveToIndex++;

        pileFrom -> pile[topCardMovedIndex] = 0;
        pileTo -> cardNumber--;
        topCardMovedIndex++;
        cardFrom = pileFrom -> pile[topCardMovedIndex];

    }
    pileFrom -> updatePile();
    pileTo -> updatePile();
    return true;
}



bool Gamestate::stockToPile(int pileFromIndex) {
    if (stock.faceCard == -1) {
        return false;
    }
    int cardFrom = stock.stack[stock.faceCard];
    Pile* pile = &piles[pileFromIndex];
    
    if (pile -> cardNumber == 0) {
        if (getCardRank(cardFrom) == CARDS_IN_SUIT - 1) {
            pile -> pile[pile -> cardNumber] = cardFrom;
            pile -> cardNumber++;
            //Unnecessaery?
            //pile -> updatePile();

            stock.stack[stock.faceCard] = 0;
            stock.turnStock();
            stock.cardsLeft--;

            return true;
        }
        // Needs to be King to go on pile
        return false;
    }

    int cardTo = pile -> pile[pile -> cardNumber - 1];

    if ((getCardSuit(cardFrom) >> 1) == (getCardSuit(cardTo) >> 1)) {
        //Cards are the same colour.
        std::cout << "Card from: ";
        printCard(cardFrom);
        std::cout << std::endl; 
        std::cout << "Card to: ";
        printCard(cardTo);
        std::cout << "Suit from: " << getCardSuit(cardFrom) << std::endl;
        std::cout << "Binary from: " << (getCardSuit(cardFrom) >> 1) << std::endl;
        std::cout << "Suit to: " << getCardSuit(cardTo) << std::endl;
        std::cout << "Binary from: " << (getCardSuit(cardTo) >> 1) << std::endl;
        std::cout << "Cards are same colour" << std::endl;
        return false;
    }
    if (getCardRank(cardFrom) + 1 != getCardRank(cardTo)) {
        //Card must be one higher.
        std::cout << "Card from: ";
        printCard(cardFrom);
        std::cout << std::endl; 
        std::cout << "Card to: ";
        printCard(cardTo);
        std::cout << std::endl; 
        std::cout << "From rank: " << getCardRank(cardFrom) << std::endl;
        std::cout << "To rank: " << getCardRank(cardTo) << std::endl;
        std::cout << "Card must be one higher" << std::endl;
        return false;
    }

     

    pile -> pile[pile -> cardNumber] = cardFrom;
    pile -> cardNumber++;
    //Unnecessaery?
    //pile -> updatePile();

    stock.stack[stock.faceCard] = 0;
    stock.turnStock();
    stock.cardsLeft--;

    return true;

}