#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::height(Node *node) {
   if (node == nullptr)
       return 0;
   return node->getHeight();
}

void AVLTree::insert(const string& newString) {
    root = insert(root, newString);
}

Node* AVLTree::insert(Node* node, const string& data) {    
    // base case: node is nullptr
    if (node == nullptr) {
        Node* nodeInsert = new Node(data);
        return nodeInsert;
    }
    
    if (data < node->getData()) {
        node->setLeft(insert(node->getLeft(), data));
    }

    else if (data > node->getData()) {
        node->setRight(insert(node->getRight(), data));
    }

    // strings are equal
    else {
        node->incrementCount();
        return node;
    }
    
    node->setHeight(1 + max(height(node->getLeft()),
       height(node->getRight())));

    //node->setHeight(1 + max(node->getLeft()->getHeight(), node->getRight()->getHeight()));

    // checks for imbalances and rotates if needed
    int balance = balanceFactor(node);

    if (balance < -1 || balance > 1)
        return rotate(node, data, balance);
    
    return node;
}

Node* AVLTree::rotate(Node* node, string data, int balance) {

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && data < node->getLeft()->getData()) {
        return rotateRight(node); 
    }

    // Right Right Case
    if (balance < -1 && data > node->getRight()->getData()) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->getLeft()->getData()) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->getRight()->getData()) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node;
}

Node* AVLTree::rotateRight(Node* n2) {
    Node *n1 = n2->getLeft();
    Node *T2 = n1->getRight();
    
    n1->setRight(n2);
    n2->setLeft(T2);

    n2->setHeight(max(height(n2->getLeft()),
           height(n2->getRight())) + 1);
   n1->setHeight(max(height(n1->getLeft()),
           height(n1->getRight())) + 1);

    return n1;
}

Node* AVLTree::rotateLeft(Node* n1) {
    Node *n2 = n1->getRight();
    Node *T2 = n2->getLeft();
    
    n2->setLeft(n1);
    n1->setRight(T2);

    n1->setHeight(max(height(n1->getLeft()),
               height(n1->getRight())) + 1);
   n2->setHeight(max(height(n2->getLeft()),
               height(n2->getRight())) + 1);

    return n2;
}

int AVLTree::balanceFactor(Node* node) {
    if (node == nullptr)
       return 0;

   return height(node->getLeft())
       - height(node->getRight());
    
    /* OLD CODE
    if(node == nullptr)
        return 0;
    
    int leftHeight = 0;
    int rightHeight = 0;
    bool moved = false;
    Node* temp = node;

    while (temp->getLeft() != nullptr) {
        leftHeight++;
        moved = true;
        temp = temp->getLeft();
    }
    if (moved)
        leftHeight++;

    moved = false;
    temp = node;

    while (temp->getRight() != nullptr) {
        rightHeight++;
        moved = true;
        temp = temp->getRight();
    }
    if (moved)
        rightHeight++;
    
    return leftHeight - rightHeight; */
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* node) {
    if (node != nullptr) {
        printBalanceFactors(node->getLeft());
        cout << node->getData() << "("
             << balanceFactor(node) << "), ";
        printBalanceFactors(node->getRight());
    }
}

// Below functions are given, do not touch!
void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->getLeft()){
            visualizeTree(outFS,n->getLeft());
            outFS<<n->getData() <<" -> " <<n->getLeft()->getData()<<";"<<endl;    
        }

        if(n->getRight()){
            visualizeTree(outFS,n->getRight());
            outFS<<n->getData() <<" -> " <<n->getRight()->getData()<<";"<<endl;    
        }
    }
}