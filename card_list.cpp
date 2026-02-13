// card_list.cpp
// Author: Peter Li, 
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"

#include <iostream>
using namespace std;

CardList::Node::Node(const Card& c) {
    info = c;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

// constructor sets up empty tree
CardList::CardList() { 
    root = nullptr;
}

// destructor deletes all nodes
CardList::~CardList() {
    clear();
}

// clear the entire tree
void CardList::clear() {
    deleteTree(root);
    root = nullptr;
}

// clear helper function
void CardList::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


// deep copy 
CardList::CardList(const CardList& other) : root(nullptr) {
    root = copyTree(other.root, nullptr);
}

// deep copy helper function
CardList::Node* CardList::copyTree(Node* node, Node* parent) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->info);
    newNode->parent = parent;

    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);

    return newNode;
}

CardList& CardList::operator=(const CardList& other) {
    if (this == &other) return *this;

    clear();  // delete existing tree

    root = copyTree(other.root, nullptr);

    return *this;
}

// insert card in tree
void CardList::insert(const Card& card) {
    Node* newNode = new Node(card);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (card < current -> info)
            current = current -> left;
        else if (card > current -> info)
            current = current -> right;
        else {
            delete newNode;
            return;
        }
    }

    newNode -> parent = parent;

    if (card < parent -> info)
        parent -> left = newNode;
    else
        parent -> right = newNode;
}

// find node in tree
CardList::Node* CardList::findNode(const Card& card) const {
    Node* current = root;

    while (current) {
        if (card < current -> info)
            current = current -> left;
        else if (card > current -> info)
            current = current -> right;
        else
            return current;
    }

    return nullptr;
}

// check if node in tree; return true if yes, otherwise false
bool CardList::contains(const Card& card) const {
    return findNode(card) != nullptr;
}


// find minimum card in tree
CardList::Node* CardList::getMin(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }

    while (n -> left != nullptr) {
        n = n -> left;
    }

    return n;
}

// find maximum card in tree
CardList::Node* CardList::getMax(Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }

    while (n -> right != nullptr) {
        n = n -> right;
    }

    return n;
}


// returns the Node containing the successor of the given value
CardList::Node* CardList::getSuccessor(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node -> right != nullptr) {
        return getMin(node->right);
    }

    Node* parent = node -> parent;
    while (parent && node == parent -> right) {
        node = parent;
        parent = parent -> parent;
    }

    return parent;
}

// returns the Node containing the predecessor of the given value
CardList::Node* CardList::getPredecessor(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node -> left) {
        return getMax(node -> left);
    }

    Node* parent = node -> parent;
    while (parent && node == parent -> left) {
        node = parent;
        parent = parent -> parent;
    }

    return parent;
}

// deletes the Node containing the given value from the tree
void CardList::remove(const Card& card) {
    Node* node = findNode(card);
    if (!node) {
        return;
    }

    // Case 1: No children
    if (!node->left && !node->right) {
        if (!node->parent) {
            root = nullptr;
        } else if (node == node->parent->left) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete node;
    }
    // Case 2: One child
    else if (!node->left || !node->right) {
        Node* child = node->left ? node->left : node->right;

        if (!node->parent) {
            root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        child->parent = node->parent;
        delete node;
    }
    // Case 3: Two children
    else {
        Node* succ = node->right;
        while (succ->left) {
            succ = succ->left;
        }

        node->info = succ->info;

        Node* child = succ->right;  // successor never has left child

        if (succ == succ->parent->left) {
            succ->parent->left = child;
        } else {
            succ->parent->right = child;
        }

        if (child) {
            child->parent = succ->parent;
        }

        delete succ;
    }
}

// Iterator constructor
CardList::Iterator::Iterator(Node* n, const CardList* t) : current(n), tree(t) {}

// Dereference operator
const Card& CardList::Iterator::operator*() const {
    return current -> info;
}

// ++ operator
CardList::Iterator& CardList::Iterator::operator++() {
    if (current == nullptr) {
        return *this;
    }

    current = tree -> getSuccessor(current);
    return *this;
}

// -- operator
CardList::Iterator& CardList::Iterator::operator--() {
    if (current == nullptr) {
        current = tree -> getMax(tree -> root);
    } else {
        current = tree -> getPredecessor(current);
    }

    return *this;
}

// == operator
bool CardList::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

// != operator
bool CardList::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

CardList::Iterator CardList::begin() const {
    return Iterator(getMin(root), this);
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr, this);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(getMax(root), this);
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr, this);
}


