#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
#include <set>

using namespace std;

// Helper to convert string to card value
int cardValue(const string& str) {
    if (str == "a") return 1;
    if (str == "j") return 11;
    if (str == "q") return 12;
    if (str == "k") return 13;
    return stoi(str);
}

// Print a hand stored in a std::set
void printSetHand(const string& name, const set<Card>& hand) {
    cout << name << "'s hand:\n";
    for (const auto& c : hand) {
        cout << c << endl;
    }
    cout << "\n";
}

// Print a hand stored in a CardList (BST)
void printBSTHand(const string& name, CardList& hand) {
    cout << name << "'s hand:\n";
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        cout << *it << endl;
    }
    cout << "\n";
}

int main() {
    // --- Test std::set implementation ---
    cout << "=== Testing std::set implementation ===\n";

    set<Card> aliceSet;
    set<Card> bobSet;

    ifstream aliceFile("alice_cards.txt");
    ifstream bobFile("bob_cards.txt");
    string line;

    while (getline(aliceFile, line)) {
        char suit = line[0];
        string valStr = line.substr(2);
        aliceSet.insert(Card(suit, cardValue(valStr)));
    }

    while (getline(bobFile, line)) {
        char suit = line[0];
        string valStr = line.substr(2);
        bobSet.insert(Card(suit, cardValue(valStr)));
    }

    // Print initial hands
    printSetHand("Alice", aliceSet);
    printSetHand("Bob", bobSet);

    // Play game using set
    bool match = true;
    while (match) {
        match = false;

        // Alice's turn (smallest → largest)
        for (auto it = aliceSet.begin(); it != aliceSet.end(); ++it) {
            if (bobSet.count(*it)) {
                cout << "Alice picked matching card " << *it << "\n";
                bobSet.erase(*it);
                aliceSet.erase(it);
                match = true;
                break;
            }
        }
        if (!match) break;

        match = false;
        // Bob's turn (largest → smallest)
        for (auto it = prev(bobSet.end()); ; --it) {
            if (aliceSet.count(*it)) {
                cout << "Bob picked matching card " << *it << "\n";
                aliceSet.erase(*it);
                bobSet.erase(it);
                match = true;
                break;
            }
            if (it == bobSet.begin()) break;
        }
    }

    printSetHand("Alice", aliceSet);
    printSetHand("Bob", bobSet);

    // --- Test BST implementation ---
    cout << "\n=== Testing BST implementation ===\n";

    CardList aliceBST;
    CardList bobBST;

    // Reset file streams
    aliceFile.clear(); aliceFile.seekg(0);
    bobFile.clear(); bobFile.seekg(0);

    while (getline(aliceFile, line)) {
        char suit = line[0];
        string valStr = line.substr(2);
        aliceBST.insert(Card(suit, cardValue(valStr)));
    }

    while (getline(bobFile, line)) {
        char suit = line[0];
        string valStr = line.substr(2);
        bobBST.insert(Card(suit, cardValue(valStr)));
    }

    // Print initial hands
    printBSTHand("Alice", aliceBST);
    printBSTHand("Bob", bobBST);

    // Play game using iterators
    match = true;
    while (match) {
        match = false;

        // Alice's turn (smallest → largest)
        for (auto it = aliceBST.begin(); it != aliceBST.end(); ++it) {
            if (bobBST.contains(*it)) {
                cout << "Alice picked matching card " << *it << "\n";
                bobBST.remove(*it);
                aliceBST.remove(*it);
                match = true;
                break;
            }
        }
        if (!match) break;

        match = false;
        // Bob's turn (largest → smallest)
        for (auto it = bobBST.rbegin(); it != bobBST.rend(); --it) {
            if (aliceBST.contains(*it)) {
                cout << "Bob picked matching card " << *it << "\n";
                aliceBST.remove(*it);
                bobBST.remove(*it);
                match = true;
                break;
            }
        }
    }

    printBSTHand("Alice", aliceBST);
    printBSTHand("Bob", bobBST);

    aliceFile.close();
    bobFile.close();
    return 0;
}
