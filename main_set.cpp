// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int cardValue(const string& str) {
    if (str == "a") return 1;
    if (str == "j") return 11;
    if (str == "q") return 12;
    if (str == "k") return 13;
    return stoi(str);
}

void printHand(const string& name, const set<Card>& hand) {
    cout << name << "'s cards:\n";
    for (const Card& c : hand) {
        cout << c << endl;
    }
}

#include <set>
#include <iostream>
#include "card.h"

void playGame(std::set<Card>& alice, std::set<Card>& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;

        // Alice's turn: forward iteration (smallest to largest)
        Card toRemove;
        bool aliceFound = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.find(*it) != bob.end()) {
                toRemove = *it;  // store matching card
                aliceFound = true;
                break;           // stop at first match
            }
        }

        if (aliceFound) {
            std::cout << "Alice picked matching card " << toRemove << std::endl;
            alice.erase(toRemove);
            bob.erase(toRemove);
            matchFound = true;
        }

        if (!matchFound) break; // no more matches

        matchFound = false;

        // Bob's turn: reverse iteration (largest to smallest)
        Card bobRemove;
        bool bobFound = false;
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            if (alice.find(*it) != alice.end()) {
                bobRemove = *it;
                bobFound = true;
                break;  // stop at first match
            }
        }

        if (bobFound) {
            std::cout << "Bob picked matching card " << bobRemove << std::endl;
            alice.erase(bobRemove);
            bob.erase(bobRemove);
            matchFound = true;
        }
    }
    cout << endl;
}



int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names\n";
        return 1;
    }

    ifstream fileAlice(argv[1]);
    ifstream fileBob(argv[2]);

    if (!fileAlice || !fileBob) {
        cout << "Error opening files\n";
        return 1;
    }

    set<Card> alice;
    set<Card> bob;
    string line;

    // Read Alice
    while (getline(fileAlice, line) && !line.empty()) {
        char suit = line[0];
        string valStr = line.substr(2);
        alice.insert(Card(suit, cardValue(valStr)));
    }

    // Read Bob
    while (getline(fileBob, line) && !line.empty()) {
        char suit = line[0];
        string valStr = line.substr(2);
        bob.insert(Card(suit, cardValue(valStr)));
    }

    playGame(alice, bob);

    printHand("Alice", alice);
    cout << endl;
    printHand("Bob", bob);

    return 0;
}
