// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int cardValue(const string& str) {
    if (str == "a") {
        return 1;
    } else if (str == "j") {
        return 11;
    } else if (str == "q") {
        return 12;
    } else if (str == "k") {
        return 13;
    } else {
        return stoi(str);
    }
}

void printHand(const string& name, CardBST& hand) {
    cout << name << "'s cards:\n";
    hand.printInOrder();
}

void playGame(CardBST& alice, CardBST& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;
        
        //Alice's turn:
        Card card = alice.getPredecessor(Card('z', 1000));
        while (card.getValue() != 0) {
            if (bob.contains(card)) {
                cout << "Alice picked matching card" << card << endl;
                alice.remove(card);
                bob.remove(card);
                matchFound = true;
                break;
            }
            card = alice.getSuccessor(card);
        }

        if (!matchFound) {
            break;
        }
        matchFound = false;

        //Bob's turn:
        card = bob.getSuccessor(Card('a', 0));
        while (card.getValue() != 0) {
            if (alice.contains(card)) {
                cout << "Bob picked matching card" << card << endl;
                alice.remove(card);
                bob.remove(card);
                matchFound = true;
                break;
            }
            card = bob.getPredecessor(card);
        }
    }
}

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardBST alice;
  CardBST bob;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    char suit = line[0];
    string str = line.substr(2);

    int val = cardValue(str);

    alice.insert(Card(suit, val));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    char suit = line[0];
    string str = line.substr(2);

    int val = cardValue(str);

    bob.insert(Card(suit, val));
  }
  cardFile2.close();
  
  playGame(alice, bob);

  printHand("Alice", alice);
  printHand("Bob", bob);
  
  return 0;
}