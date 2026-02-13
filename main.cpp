#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

// Convert a string to card value
int cardValue(const string& str) {
    if (str == "a") return 1;
    if (str == "j") return 11;
    if (str == "q") return 12;
    if (str == "k") return 13;
    return stoi(str);
}

// Print a player's hand
void printHand(const string& name, CardList& hand) {
    cout << name << "'s cards:\n";
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        cout << *it << endl;
    }
    cout << "\n";
}

// The main gameplay function
void playGame(CardList& alice, CardList& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;

        // Alice's turn: smallest → largest
        for (auto it = alice.begin(); it != alice.end(); ) {
            Card card = *it;  // copy card
            ++it;             // increment BEFORE removing

            if (bob.contains(card)) {
                cout << "Alice picked matching card " << card << endl;
                alice.remove(card);
                bob.remove(card);
                matchFound = true;
                break; // only one match per turn
            }
        }

        if (!matchFound) break;
        matchFound = false;

        // Bob's turn: largest → smallest
        for (auto it = bob.rbegin(); it != bob.rend(); ) {
            Card card = *it;
            --it;             // Decrement before removing

            if (alice.contains(card)) {
                cout << "Bob picked matching card " << card << endl;
                alice.remove(card);
                bob.remove(card);
                matchFound = true;
                break;
            }
        }
    }
    cout << endl;
}


int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide two card files (Alice and Bob)" << endl;
        return 1;
    }

    ifstream fileAlice(argv[1]);
    ifstream fileBob(argv[2]);
    if (!fileAlice.is_open() || !fileBob.is_open()) {
        cout << "Error opening files" << endl;
        return 1;
    }

    CardList alice, bob;
    string line;

    // Read Alice's cards
    while (getline(fileAlice, line)) {
        if (line.empty()) continue;
        char suit = line[0];
        string valStr = line.substr(2);
        alice.insert(Card(suit, cardValue(valStr)));
    }

    // Read Bob's cards
    while (getline(fileBob, line)) {
        if (line.empty()) continue;
        char suit = line[0];
        string valStr = line.substr(2);
        bob.insert(Card(suit, cardValue(valStr)));
    }

    fileAlice.close();
    fileBob.close();

    playGame(alice, bob);

    printHand("Alice", alice);
    printHand("Bob", bob);

    return 0;
}
