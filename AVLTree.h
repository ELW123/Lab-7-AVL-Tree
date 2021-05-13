#ifndef AVLTree_H_
#define AVLTree_H_

#include <string>
#include <fstream>
#include <iostream>
#include "Node.h"

using namespace std;

class AVLTree {  
 public :
    AVLTree();
    void insert(const string&);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string&);

 private:
    Node* root;  

    int height(Node*);
    Node* insert(Node*, const string&);
    Node* rotate(Node *, string, int);
    void printBalanceFactors(Node*);
    void visualizeTree(ofstream &, Node*);
    Node* rotateRight(Node*);
    Node* rotateLeft(Node*);
};

#endif