// card.cpp
// Author: Peter Li, 
// Implementation of the classes defined in card.h

#include "card.h"

int suitRank(char s) {
    if (s == 'c') {
        return 0;
    } else if (s == 'd') {
        return 1;
    } else if (s == 's') {
        return 2;
    } else {
        return 3;
    }
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {  
        suit = other.suit;
        value = other.value;
    }
    return *this;
}

bool Card::operator<(const Card& other) const {
    if (suitRank(suit) != suitRank(other.suit)) {
        return suitRank(suit) < suitRank(other.suit);
    }

    return value < other.value;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

bool Card::operator>(const Card& other) const {
    if (suitRank(suit) != suitRank(other.suit)) {
        return suitRank(suit) > suitRank(other.suit);
    }

    return value > other.value;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.suit << " ";

    if (card.value == 1) os << "a";
    else if (card.value == 11) os << "j";
    else if (card.value == 12) os << "q";
    else if (card.value == 13) os << "k";
    else os << card.value;

    return os;
}