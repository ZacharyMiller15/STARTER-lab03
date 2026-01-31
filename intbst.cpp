// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (!n) return;

    if (n->left) {
        clear(n->left);
    } 
    
    if (n->right) {
        clear(n->right);
    } 
    
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    return insert(value, root, nullptr);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n, Node *parent) {
    if (!n) {
        if (!parent) {
            root = new Node(value);
            root->parent = nullptr;
        } else if (parent->info < value) {
            parent->right = new Node(value);
            parent->right->parent = parent;
        } else {
            parent->left = new Node(value);
            parent->left->parent = parent;
        }

        return true;
    }

    if (value == n->info) return false;

    if (value > n->info) {
        return insert(value, n->right, n);
    }

    if (value < n->info) {
        return insert(value, n->left, n);
    }

    return true;
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (!n) return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;

    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;

    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return nullptr;
    
    if (n->info == value) return n;

    if (value < n->info) return getNodeFor(value, n->left);
    if (value > n->info) return getNodeFor(value, n->right);

    return nullptr;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (!getNodeFor(value, root)) return false;

    return true;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    if (!getNodeFor(value, root)) return nullptr;
    
    Node* n = getNodeFor(value, root);
    if (n->left) {
        Node* curr = n->left;
        while (curr->right) {
            curr = curr->right;
        }
        return curr;
    }

    while (n->parent && n->info < n->parent->info) {
        n = n->parent;
    }

    if (n->parent) return n->parent;

    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    return getPredecessorNode(value)->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    if (!getNodeFor(value, root)) return nullptr;
    
    Node* n = getNodeFor(value, root);
    if (n->right) {
        Node* curr = n->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    while (n->parent && n->info > n->parent->info) {
        n = n->parent;
    }

    if (n->parent) return n->parent;

    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return getSuccessorNode(value)->info;
}

// helper function for remove - inserts new node before deletion
void IntBST::transplant(Node* original, Node* new_node) {
    if (original == root) {
        root = new_node;
    } else if (original == original->parent->left) {
        original->parent->left = new_node;
    } else if (original == original->parent->right) {
        original->parent->right = new_node;
    }

    if (new_node) {
        new_node->parent = original->parent;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* removal = getNodeFor(value, root);

    if (!removal) return false;

    if (!removal->left && !removal->right) {
        transplant(removal, nullptr);
        delete removal;
        return true;
    } else if (!removal->left && removal->right) {
        transplant(removal, removal->right);
        delete removal;
        return true;
    } else if (!removal->right && removal->left) {
        transplant(removal, removal->left);
        delete removal;
        return true;
    }

    Node* pred = getPredecessorNode(value);

    if (pred->parent != removal) {
        transplant(pred, pred->left);
        pred->left = removal->left;
        pred->left->parent = pred;
    }

    transplant(removal, pred);
    pred->right = removal->right;
    pred->right->parent = pred;

    delete removal;
    return true;
}
