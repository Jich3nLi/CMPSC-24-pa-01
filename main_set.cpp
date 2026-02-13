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
    cout << endl;
}

void playGame(set<Card>& alice, set<Card>& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;

        // Alice's turn
        Card toRemove;
        bool found = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.count(*it)) {
                toRemove = *it;
                found = true;
                break;
            }
        }
        if (found) {
            cout << "Alice picked matching card " << toRemove << "\n";
            alice.erase(toRemove);
            bob.erase(toRemove);
            matchFound = true;
        }

        if (!matchFound) break;

        matchFound = false;

        //Bob's turn:
        Card toRemove;
        bool found = false;
        for (auto it = prev(bob.end()); ; --it) {
            if (alice.count(*it)) {
                toRemove = *it;
                found = true;
                break;
            }
            if (it == bob.begin()) break;
        }
        if (found) {
            cout << "Bob picked matching card " << toRemove << "\n";
            alice.erase(toRemove);
            bob.erase(toRemove);
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
    printHand("Bob", bob);

    return 0;
}
