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

        // Alice's turn: forward iteration (smallest to largest)
        Card toRemove;
        bool aliceFound = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                toRemove = *it;          // store matching card
                aliceFound = true;
                break;                   // stop at first match
            }
        }

        if (aliceFound) {
            cout << "Alice picked matching card " << toRemove << endl;
            alice.remove(toRemove);
            bob.remove(toRemove);
            matchFound = true;
        }

        if (!matchFound) break; // no match left, game ends

        matchFound = false;

        // Bob's turn: reverse iteration (largest to smallest)
        Card bobRemove;
        bool bobFound = false;

        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.contains(*it)) {
                bobRemove = *it;
                bobFound = true;
                break;                  // stop at first match
            }
        }

        if (bobFound) {
            cout << "Bob picked matching card " << bobRemove << endl;
            alice.remove(bobRemove);
            bob.remove(bobRemove);
            matchFound = true;
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
