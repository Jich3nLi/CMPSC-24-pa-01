// card_list.h
// Author: Peter Li, 
// All class declarations related to defining a BST that represents a player's hand

#include "card.h"

#ifndef CARD_LIST_H
#define CARD_LIST_H
class CardBST {
    public:
        // ctor, dtor, insert and one print method already done in intbst.cpp:
        CardBST();                   // constructor
        ~CardBST();                  // destructor
        bool insert(Card card);     // insert value; return false if duplicate
        void printPreOrder() const; // prints tree data pre-order to cout

        // 8 METHODS YOU MUST IMPLEMENT in intbst.cpp:
        void printInOrder() const;       // print tree data in-order to cout
        void printPostOrder() const;     // print tree data post-order to cout
        int count() const;               // count of values
        bool contains(Card card) const;  // true if value is in tree

        // THESE ARE HARDER! DO THESE LAST
        Card getPredecessor(Card card) const;       // returns the predecessor value of the given value or 0 if there is none
        Card getSuccessor(Card card) const;         // returns the successor value of the given value or 0 if there is none
        bool remove(Card card);                    // deletes the Node containing the given value from the tree

    private:

        struct Node {
            Card info;
            Node *left, *right, * parent;
            // useful constructor:
            Node(Card card) : info(card), left(nullptr), right(nullptr), parent(nullptr) { }
        };

        // just one instance variable (pointer to root node):
        Node *root;

        // recursive utility functions for use by public methods above
        Node* getNodeFor(Card card, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
        void clear(Node *n); // for destructor
        bool insert(Card card, Node *n); // note overloading names for simplicity
        void printPreOrder(Node *n) const;
        void printInOrder(Node *n) const;
        void printPostOrder(Node *n) const;
        int sum(Node *n) const;
        int count(Node *n) const;

        // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
        Node* getSuccessorNode(Card card) const;   // returns the Node containing the successor of the given value
        Node* getPredecessorNode(Card card) const; // returns the Node containing the predecessor of the given value 
};

#endif