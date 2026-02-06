#include <solitaire/types.hpp>

static std::string suitToString(int suit) {
    if (suit < providedSuitCount) return suitNames[suit];

    return "(Suit " + std::to_string(suit+1) + ")";
}

static std::string rankToString(int rank) {
    if (rank == 0) return "A";
    if (rank == CARDS_IN_SUIT - 1) return "K";
    if (rank == CARDS_IN_SUIT - 2) return "Q";
    if (rank == CARDS_IN_SUIT - 3) return "J";
    
    return std::to_string(rank + 1);
}

void printCard(int cardNumber) {
    int suit = getCardSuit(cardNumber);
    int rank = getCardRank(cardNumber);
    std::cout << suitToString(suit) << rankToString(rank);
    return;
}