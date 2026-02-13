// card_list.h
// Author: Peter Li, 
// All class declarations related to defining a BST that represents a player's hand

#include "card.h"

#ifndef CARD_LIST_H
#define CARD_LIST_H
class CardList {
    private:
        struct Node {
            Card info;
            Node* left;
            Node* right;
            Node* parent;

            Node(const Card& c);
        };

        Node* root;

    public:
        CardList();
        ~CardList();
        void clear();
        void deleteTree(Node* n);

        CardList(const CardList& other); // deep copy 
        Node* copyTree(Node* node, Node* parent);

        CardList& operator=(const CardList& other);

        void insert(const Card& card);
        void remove(const Card& card);
        bool contains(const Card& card) const;

        class Iterator {
        private:
            Node* current;
            const CardList* tree;

        public:
            Iterator(Node* n, const CardList* t);

            const Card& operator*() const;
            Iterator& operator++();
            Iterator& operator--();

            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
        };

        Iterator begin() const;
        Iterator end() const;
        Iterator rbegin() const;
        Iterator rend() const;

    private:
        Node* findNode(const Card& card) const;
        Node* getMin(Node* n) const;
        Node* getMax(Node* n) const;
        Node* getSuccessor(Node* n) const;
        Node* getPredecessor(Node* n) const;
};

#endif