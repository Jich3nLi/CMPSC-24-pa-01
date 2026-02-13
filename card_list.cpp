// card_list.cpp
// Author: Peter Li, 
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
CardBST::CardBST() { 
    root = nullptr;
}

// destructor deletes all nodes
CardBST::~CardBST() {
    clear(root);
}

// recursive helper for destructor
void CardBST::clear(Node *n) {
    if (n == nullptr) {
        return;
    }

    clear(n -> left);
    clear(n -> right);
    delete n;
}

// insert value in tree; return false if duplicate
bool CardBST::insert(Card card) {
    if (root == nullptr) {
        root = new Node(card);
        return true;
    }
    return insert(card, root);
}

// recursive helper for insert (assumes n is never 0)
bool CardBST::insert(Card card, Node* n) {
    if (n -> info > card) {
        if (n -> left == nullptr) {
            n -> left = new Node(card);
            n -> left -> parent = n;
            return true;
        } else {
            return insert(card, n -> left);
        }
    } else if (n -> info < card) {
        if (n -> right == nullptr) {
            n -> right = new Node(card);
            n -> right -> parent = n;
            return true;
        } else {
            return insert(card, n -> right);
        }
    } else {
        return false;
    }
}

// print tree data pre-order
void CardBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void CardBST::printPreOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    cout << n -> info << " ";
    printPreOrder(n -> left);
    printPreOrder(n -> right);
}

// print tree data in-order, with helper
void CardBST::printInOrder() const {
    printInOrder(root);
}
void CardBST::printInOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    printInOrder(n -> left);
    cout << n -> info << " ";
    printInOrder(n -> right);
}

// prints tree data post-order, with helper
void CardBST::printPostOrder() const {
    printPostOrder(root);
}

void CardBST::printPostOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    printPostOrder(n -> left);
    printPostOrder(n -> right);
    cout << n -> info << " ";
}

// return count of values
int CardBST::count() const {
    return count(root);
}

// recursive helper for count
int CardBST::count(Node *n) const {
    if (n == nullptr) {
        return 0;
    } 
    return count(n -> left) + count(n -> right) + 1;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
CardBST::Node* CardBST::getNodeFor(Card card, Node* n) const{
    if (n == nullptr) {
        return nullptr;
    }
    if (n -> info > card) {
        return getNodeFor(card, n -> left);
    } else if (n -> info < card) {
        return getNodeFor(card, n -> right);
    } else {
        return n;
    }
}

// returns true if value is in the tree; false if not
bool CardBST::contains(Card card) const {
    return (getNodeFor(card, root) != nullptr); 
}

// returns the Node containing the predecessor of the given value
CardBST::Node* CardBST::getPredecessorNode(Card card) const{
    if (root == nullptr) {
        return nullptr;
    }

    Node* curr = getNodeFor(card, root);

    if (curr == nullptr) {
        return nullptr;
    }

    if (curr -> left != nullptr) {
        curr = curr -> left;
        while (curr -> right != nullptr) {
            curr = curr -> right;
        }
        return curr;
    } else {
        while (curr -> parent != nullptr && curr -> parent -> left == curr) {
            curr = curr -> parent;
        }
        curr = curr -> parent;
        return curr;
    }
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
Card CardBST::getPredecessor(Card card) const{
    Node* predecessor = getPredecessorNode(card);
    if (predecessor == nullptr) {
        return Card();
    }
    return predecessor -> info;
}

// returns the Node containing the successor of the given value
CardBST::Node* CardBST::getSuccessorNode(Card card) const{
    if (root == nullptr) {
        return nullptr;
    }

    Node* curr = getNodeFor(card, root);

    if (curr == nullptr) {
        return nullptr;
    }
    
    if (curr -> right != nullptr) {
        curr = curr -> right;
        while (curr -> left != nullptr) {
            curr = curr -> left;
        }
        return curr;
    } else {
        while (curr -> parent != nullptr && curr -> parent -> right == curr) {
            curr = curr -> parent;
        } 
        curr = curr -> parent;
        return curr;
    }
    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
Card CardBST::getSuccessor(Card card) const{
    Node* successor = getSuccessorNode(card);
    if (successor == nullptr) {
        return Card();
    }
    return successor -> info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardBST::remove(Card card){
    Node* nodeToDelete = getNodeFor(card, root);

    if (nodeToDelete == nullptr) {
        return false;
    }
    // Case 1: To delete node having two children, we can replace the value in nodeToDelete 
    // with the value of the successor, and then delete the successor (successors can't have
    // 2 children).
    if (nodeToDelete -> left != nullptr && nodeToDelete -> right != nullptr) {
        Node* successor = getSuccessorNode(card);
        nodeToDelete -> info = successor -> info;
        nodeToDelete = successor; 
    }
    // Case 2: Delete node with one or zero child
    Node* child = nullptr;
    if (nodeToDelete -> left != nullptr) {
        child = nodeToDelete -> left;
    } else {
        child = nodeToDelete -> right;
    }

    if (nodeToDelete -> parent == nullptr) {
        root = child;
        if (child != nullptr) {
            child->parent = nullptr;
        }
        delete nodeToDelete;
        return true;
    } else if (nodeToDelete == nodeToDelete -> parent -> left) {
        nodeToDelete -> parent -> left = child;
    } else {
        nodeToDelete -> parent -> right = child;
    }

    if (child != nullptr) {
        child -> parent = nodeToDelete -> parent;
    }

    delete nodeToDelete;
    return true;
}