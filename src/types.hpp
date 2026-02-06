#ifndef TYPES_HPP
#define TYPES_HPP

#define NUMBER_OF_DECKS 1
#define NUMBER_OF_PILES 7


#define NUMBER_OF_SUITS 4

#define SUIT_NAMES { "H", "D", "C", "S" }

static const char* suitNames[] = SUIT_NAMES;

static constexpr int providedSuitCount =
    sizeof(suitNames) / sizeof(suitNames[0]);



#define CARDS_IN_SUIT 13

#include <string>
#include <iostream>


static constexpr int DECK_SIZE = (NUMBER_OF_SUITS * CARDS_IN_SUIT);
static constexpr int ALL_DECK_SIZE = (NUMBER_OF_DECKS * DECK_SIZE);

//How many cards will be left after the table has been dealt.
static constexpr int STOCK_SIZE = (ALL_DECK_SIZE - (NUMBER_OF_PILES * (NUMBER_OF_PILES + 1)) / 2);

static constexpr int MAX_PILE_SIZE = (CARDS_IN_SUIT + NUMBER_OF_PILES);

//enum CARDS : int {
//    NO_CARD,
//    CA, C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ, CQ, CK,
//    SA, S2, S3, S4, S5, S6, S7, S8, S9, S10, SJ, SQ, SK,
//    DA, D2, D3, D4, D5, D6, D7, D8, D9, D10, DJ, DQ, DK,
//    HA, H2, H3, H4, H5, H6, H7, H8, H9, H10, HJ, HQ, HK   
//};

//enum PILES: int Not including for now...










static constexpr int getCardSuit(int card) {
    return ((card - 1) / CARDS_IN_SUIT);
}

static constexpr int getCardRank(int card) {
    return ((card - 1) % CARDS_IN_SUIT);
}

static std::string suitToString(int suit);

static std::string rankToString(int rank);


void printCard(int cardNumber);


        

//#define ENABLE_INCR_OPERATORS_ON(T)
//inline T& operator++(T& d) { return  d = T(int(d) + 1); }
//inline T& operator--(T& d) { return  d = T(int(d) - 1); }

//ENABLE_INCR_OPERATORS_ON(CARDS)
//ENABLE_INCR_OPERATORS_ON(SUITS)



#endif