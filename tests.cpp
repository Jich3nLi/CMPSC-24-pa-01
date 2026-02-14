#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include "card_list.h"
#include "card.h"

using namespace std;

// Forward declarations of game functions
int cardValue(const string& str) {
    if (str == "a") return 1;
    if (str == "j") return 11;
    if (str == "q") return 12;
    if (str == "k") return 13;
    return stoi(str);
}

void playGame(CardList& alice, CardList& bob) {
    while (true) {
        bool alicePicked = false;
        bool bobPicked = false;

        // Alice's turn: forward iteration (smallest to largest)
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                Card matchingCard = *it;
                std::cout << "Alice picked matching card " << matchingCard << std::endl;

                // Remove from both hands
                alice.remove(matchingCard);
                bob.remove(matchingCard);

                alicePicked = true;
                break;  // stop after first match
            }
        }

        // Bob's turn: reverse iteration (largest to smallest)
        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.contains(*it)) {
                Card matchingCard = *it;
                std::cout << "Bob picked matching card " << matchingCard << std::endl;

                // Remove from both hands
                alice.remove(matchingCard);
                bob.remove(matchingCard);

                bobPicked = true;
                break;  // stop after first match
            }
        }
        // If neither picked a card, game ends
        if (!alicePicked && !bobPicked) break;
    }
    cout << endl;
}


void printHand(const string& name, CardList& hand) {
    cout << name << "'s cards:\n";
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        cout << *it << endl;
    }
}

using namespace std;

// test card.h card.cpp
void testOperatorLess() {
    cout << "Testing operator< ...\n";

    Card c1{'c', 2};
    Card c2{'c', 5};
    Card c3{'d', 1};
    Card c4{'s', 13};
    Card c5{'h', 7};

    // 5 test cases
    assert(c1 < c2);  // same suit, lower value
    assert(c2 < c3);  // suit c < d
    assert(c3 < c4);  // suit d < s
    assert(c4 < c5);  // suit s < h (based on suitRank)
    assert(!(c5 < c1)); // reverse check

    cout << "Passed operator< tests\n";
}

void testOperatorGreater() {
    cout << "Testing operator> ...\n";

    Card c1{'c', 2};
    Card c2{'c', 5};
    Card c3{'d', 1};
    Card c4{'s', 13};
    Card c5{'h', 7};

    // 5 test cases
    assert(c2 > c1);  // same suit, higher value
    assert(c3 > c2);  // suit d > c
    assert(c4 > c3);  // suit s > d
    assert(c5 > c4);  // suit h > s
    assert(!(c1 > c5)); // reverse check

    cout << "Passed operator> tests\n";
}

void testOperatorEqual() {
    cout << "Testing operator== ...\n";

    Card c1{'c', 2};
    Card c2{'c', 2};
    Card c3{'c', 5};
    Card c4{'d', 2};
    Card c5{'h', 7};

    // 5 test cases
    assert(c1 == c2); // same suit & value
    assert(!(c1 == c3)); // different value
    assert(!(c1 == c4)); // different suit
    assert(!(c1 == c5)); // different suit & value
    assert(c2 == c1); // symmetric

    cout << "Passed operator== tests\n";
}

void testOutputOperator() {
    cout << "Testing operator<< ...\n";

    Card c1{'c', 1};   // ace
    Card c2{'d', 11};  // jack
    Card c3{'s', 12};  // queen
    Card c4{'h', 13};  // king
    Card c5{'c', 7};   // number

    stringstream ss;

    ss << c1;
    assert(ss.str() == "c a");

    ss.str(""); ss.clear();
    ss << c2;
    assert(ss.str() == "d j");

    ss.str(""); ss.clear();
    ss << c3;
    assert(ss.str() == "s q");

    ss.str(""); ss.clear();
    ss << c4;
    assert(ss.str() == "h k");

    ss.str(""); ss.clear();
    ss << c5;
    assert(ss.str() == "c 7");

    cout << "Passed operator<< tests\n";
}

// test card_list.h card_list.cpp

void testInsertAndContains() {
    cout << "Testing insert & contains...\n";
    CardList list;

    Card c1{'c', 5};
    Card c2{'d', 3};
    Card c3{'s', 10};

    list.insert(c1);
    list.insert(c2);
    list.insert(c3);

    assert(list.contains(c1));
    assert(list.contains(c2));
    assert(list.contains(c3));
    assert(!list.contains(Card{'h', 1}));

    cout << "Passed insert & contains\n";
}

void testMinMax() {
    cout << "Testing getMin & getMax...\n";
    CardList list;

    list.insert({'s', 10});
    list.insert({'c', 2});
    list.insert({'h', 13});
    list.insert({'d', 5});

    assert(list.begin() != list.end());
    assert((*list.begin()).getSuit() == 'c');

    CardList::Iterator it = list.rbegin();
    assert((*it).getSuit() == 'h');

    cout << "Passed getMin & getMax\n";
}

void testRemoveLeaf() {
    cout << "Testing remove leaf node...\n";
    CardList list;
    list.insert({'c', 2});
    list.insert({'d', 3});
    list.insert({'s', 4});

    list.remove({'s', 4});
    assert(!list.contains({'s', 4}));

    cout << "Passed remove leaf\n";
}

void testRemoveOneChild() {
    cout << "Testing remove node with one child...\n";
    CardList list;
    list.insert({'c', 2});
    list.insert({'d', 3});
    list.insert({'s', 4});
    list.insert({'h', 5});

    list.remove({'s', 4});
    assert(!list.contains({'s', 4}));
    assert(list.contains({'h', 5}));

    cout << "Passed remove one child\n";
}

void testRemoveTwoChildren() {
    cout << "Testing remove node with two children...\n";
    CardList list;
    list.insert({'d', 5});
    list.insert({'c', 3});
    list.insert({'h', 7});
    list.insert({'s', 6});
    list.insert({'h', 9});

    list.remove({'d', 5});
    assert(!list.contains({'d', 5}));
    assert(list.contains({'s', 6}));

    cout << "Passed remove two children\n";
}

void testCopyConstructor() {
    cout << "Testing copy constructor...\n";
    CardList list;
    list.insert({'c', 1});
    list.insert({'d', 2});

    CardList copy(list);

    assert(copy.contains({'c',1}));
    assert(copy.contains({'d',2}));

    cout << "Passed copy constructor\n";
}

void testAssignmentOperator() {
    cout << "Testing assignment operator...\n";
    CardList list1;
    list1.insert({'c', 1});
    list1.insert({'d', 2});

    CardList list2;
    list2 = list1;

    assert(list2.contains({'c',1}));
    assert(list2.contains({'d',2}));

    cout << "Passed assignment operator\n";
}

void testIteratorForward() {
    cout << "Testing forward iterator...\n";
    CardList list;
    list.insert({'c', 1});
    list.insert({'d', 2});
    list.insert({'s', 3});

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        cout << *it << " ";
        count++;
    }
    cout << endl;

    assert(count == 3);
    cout << "Passed forward iterator\n";
}

void testIteratorBackward() {
    cout << "Testing reverse iterator...\n";
    CardList list;
    list.insert({'c', 1});
    list.insert({'d', 2});
    list.insert({'s', 3});

    int count = 0;
    for (auto it = list.rbegin(); it != list.rend(); --it) {
        cout << *it << " ";
        count++;
    }
    cout << endl;

    assert(count == 3);
    cout << "Passed reverse iterator\n";
}

void testClear() {
    cout << "Testing clear...\n";
    CardList list;
    list.insert({'c',1});
    list.insert({'d',2});

    list.clear();
    assert(list.begin() == list.end());

    cout << "Passed clear\n";
}

void testCardOperators() {
    cout << "Testing Card operators...\n";

    Card c1{'c', 5};
    Card c2{'d', 5};
    Card c3{'c', 5};

    assert(c1 < c2);
    assert(c2 > c1);
    assert(c1 == c3);

    cout << "Passed Card operators\n";
}

// Game Function TESTS

void testPlayGameCommonCards() {
    CardList alice, bob;
    alice.insert(Card('c', 4));
    alice.insert(Card('d', 5));
    bob.insert(Card('c', 4));
    bob.insert(Card('h', 7));

    stringstream captured;
    streambuf* oldCout = cout.rdbuf(captured.rdbuf());

    playGame(alice, bob);
    printHand("Alice", alice);
    printHand("Bob", bob);

    cout.rdbuf(oldCout);

    string output = captured.str();
    assert(output.find("Alice picked matching card c 4") != string::npos);
    assert(!alice.contains(Card('c', 4)));
    assert(!bob.contains(Card('c', 4)));

    cout << "testPlayGameCommonCards passed\n";
}

void testPlayGameEmptyHand() {
    CardList alice, bob;
    alice.insert(Card('c', 4));
    // Bob's hand empty

    stringstream captured;
    streambuf* oldCout = cout.rdbuf(captured.rdbuf());

    playGame(alice, bob);
    printHand("Alice", alice);
    printHand("Bob", bob);

    cout.rdbuf(oldCout);

    // Alice's hand should remain unchanged
    assert(alice.contains(Card('c', 4)));
    assert(bob.begin() == bob.end());

    cout << "testPlayGameEmptyHand passed\n";
}

void testPlayGameNoCommonCards() {
    CardList alice, bob;
    alice.insert(Card('c', 4));
    bob.insert(Card('d', 5));

    stringstream captured;
    streambuf* oldCout = cout.rdbuf(captured.rdbuf());

    playGame(alice, bob);
    printHand("Alice", alice);
    printHand("Bob", bob);

    cout.rdbuf(oldCout);

    // Hands should remain unchanged
    assert(alice.contains(Card('c', 4)));
    assert(bob.contains(Card('d', 5)));

    cout << "testPlayGameNoCommonCards passed\n";
}

int main() {
    testOperatorLess();
    testOperatorGreater();
    testOperatorEqual();
    testOutputOperator();

    cout << "\nALL Card TESTS PASSED!\n\n";

    testInsertAndContains();
    testMinMax();
    testRemoveLeaf();
    testRemoveOneChild();
    testRemoveTwoChildren();
    testCopyConstructor();
    testAssignmentOperator();
    testIteratorForward();
    testIteratorBackward();
    testClear();
    testCardOperators();

    cout << "\nALL CARD_LIST TESTS PASSED SUCCESSFULLY!\n\n";

    testPlayGameCommonCards();
    testPlayGameEmptyHand();
    testPlayGameNoCommonCards();

    cout << "\nAll tests passed!\n";

    return 0;
}