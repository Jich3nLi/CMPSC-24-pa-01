// card.h
// Author: Peter Li, 
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
    private: 
        char suit;
        int value;
        
    public: 
        Card() : suit(0), value(0) {};
        Card(char s, int v) : suit(s), value(v) {};

        char getSuit() const {return suit;};
        int getValue() const {return value;};

        bool operator<(const Card& other) const;
        bool operator==(const Card& other) const;
        bool operator>(const Card& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

#endif