//
//  BST.h
//  a
//
//  Created by Matt Rodriguez on 2/24/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.
//

#ifndef BST_h
#define BST_h
#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int info;
    struct Node *right, *left;
};

class BST{
        Node *root;
        void deleteFromTree(Node* &n);
        void preOrder(Node *n);
        Node* insertRec(int item, Node *n);
        Node* removeRec(int item, Node *n);
        Node* findMaxIter(Node *n);
        Node* findMinIter(Node *n);
        Node* findMaxRec(Node *n);
        Node* findMinRec(Node *n);
        Node* findPrevIter(int item, Node *n);
        Node* findNextIter(int item, Node *n);
        Node* findPrevRec(int item, Node *n);
        Node* findNextRec(int item, Node *n);
    public:
        vector<int> vec;
        BST();
        void insertIter(int item);
        void removeIter(int item);
        void insertRec(int item);
        void removeRec(int item);
        void preOrder();
        void traversals(vector<int> &list);
        Node* findNextIter(int item);
        Node* findPrevIter(int item);
        Node* findNextRec(int item);
        Node* findPrevRec(int item);
        Node* findMaxIter();
        Node* findMinIter();
        Node* findMaxRec();
        Node* findMinRec();
};
#endif /* BST_h */
