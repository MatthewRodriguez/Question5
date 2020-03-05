//  BST.cpp
//  Created by Matt Rodriguez on 2/24/20.
//  Copyright © 2020 Matthew Rodriguez. All rights reserved.

#include "BST.h"

BST::BST(){
    root = nullptr;
}

void BST::preOrder(){
    preOrder(root);
}

void BST::preOrder(Node *n){
    if (n == nullptr)
        return;
    cout << n->info << " ";
    preOrder(n->left);
    preOrder(n->right);
}

void BST::insertIter(int item){
    Node *current, *prev = nullptr, *newNode;
    int count = 0;
    
    newNode = new Node;
    newNode->info = item;
    newNode->left = nullptr;
    newNode->right = nullptr;
       
    if (root == nullptr)
        root = newNode;
    else{
        current = root;
        
        while (current != nullptr){
            prev = current;
            if (current->info == item)
                return;
            else if (current->info > item){
                count++;
                current = current->left;
            }
            else{
                count++;
                current = current->right;
            }
        }
           
        if (prev->info > item)
            prev->left = newNode;
        else
            prev->right = newNode;
    }
    vec.push_back(count);
    //cout << "Total traversals BST: " << count << endl;
}


void BST::deleteFromTree(Node* &n){
    Node *current, *prev, *temp;
    if (n == nullptr)
        return;
    else if (n->left == nullptr && n->right == nullptr){
        temp = n;
        n = nullptr;
        delete temp;
    }
    else if (n->left == nullptr){
        temp = n;
        n = temp->left;
        delete temp;
    }
    else if (n->right == nullptr){
        temp = n;
        n = temp->right;
        delete temp;
    }
    else{
        current = n->left;
        prev = nullptr;
    
        while (current->right != nullptr){
            prev = current;
            current = current->right;
        }
        
        n->info = current->info;
        if (prev == nullptr)
            n->left = current->left;
        else
            prev->right = current->left;
            
        delete current;
    }
}

void BST::removeIter(int item){
    Node *current, *prev;
    bool found = false;
    
    if (root == nullptr)
        return;
    else{
        current = root;
        prev = root;
        
        while(current != nullptr && !found){
            if (current->info == item)
                found = true;
            else{
                prev = current;
                if (current->info > item)
                    current = current->left;
                else
                    current = current->right;
            }
        }
        if (current == nullptr)
            return;
        else if (found){
            if (current == root)
                deleteFromTree(root);
            else if (prev->info > item)
                deleteFromTree(prev->left);
            else
                deleteFromTree(prev->right);
        }
    }
}

Node* BST::findMaxIter(){
    return  findMaxIter(root);
}

Node* BST::findMaxIter(Node *n){
    if (n != nullptr)
        while(n->right != nullptr)
            n = n->right;
    return n;
}

Node* BST::findMinIter(){
    return findMinIter(root);
}

Node* BST::findMinIter(Node *n){
    if (n != nullptr)
        while (n->left != nullptr)
            n = n->left;
    return n;
}

Node* BST::findPrevIter(int item){
    return findPrevIter(item, root);
}

Node* BST::findPrevIter(int item, Node *n){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    while(current->right != nullptr){
        if (current->info == item){
            if (current->left != nullptr){
                if(current->left->right != nullptr)
                    return current->left->right;
                else
                    return current->left;
            }
            else if (n->left == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = current->right;
    }
    
    while(t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = t->left;
    }
    return nothing;
}

Node* BST::findNextIter(int item){
    return findNextIter(item, root);
}

Node* BST::findNextIter(int item, Node *n){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    while(current->right != nullptr){
        if (current->info == item){
            if (current->right != nullptr){
                if(current->right->left != nullptr)
                    return current->right->left;
                else
                    return current->right;
            }
            else if (n->right == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = current->right;
    }
    
    while(t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = t->left;
    }
    return nothing;
}

void BST::insertRec(int item){
    insertRec(item, root);
}

Node* BST::insertRec(int item, Node *n){
    if (n == nullptr){
        n = new Node;
        n->info = item;
        n->left = nullptr;
        n->right = nullptr;
    }
    else if (item < n->info)
        n->left = insertRec(item, n->left);
    else if (item > n->info)
        n->right = insertRec(item, n->right);
    else
        ;
    return n;
}


void BST::removeRec(int item){
    removeRec(item, root);
}

Node* BST::removeRec(int item, Node *n){
    Node *nothing = nullptr;
    if (n == nullptr)
        return nothing;
    if (item < n->info)
        n->left = removeRec(item, n->left);
    else if (item > n->info)
        n->right = removeRec(item, n->right);
    else if (n->left != nullptr && n->right != nullptr){
        n->info = findMinIter(n->right)->info;
        removeRec(n->info, n->right);
    }
    else{
        Node *temp = n;
        n = (n->left != nullptr) ? n->left : n->right;
        delete temp;
    }
    return n;
}

Node* BST::findMaxRec(){
    return  findMaxRec(root);
}

Node* BST::findMaxRec(Node *n){
    if (n != nullptr){
        if (n->right != nullptr)
            n = findMaxRec(n->right);
    }
    return n;
}

Node* BST::findMinRec(){
    return findMinRec(root);
}

Node* BST::findMinRec(Node *n){
    if (n != nullptr){
        if (n->left != nullptr)
            n = findMinRec(n->left);
    }
    return n;
}

Node* BST::findNextRec(int item){
    return findNextRec(item, root);
}

Node* BST::findNextRec(int item, Node *n){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    if (current->right != nullptr){
        if (current->info == item){
            if (current->right != nullptr){
                if(current->right->left != nullptr)
                    return current->right->left;
                else
                    return current->right;
            }
            else if (n->right == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = findNextRec(item, current->right);
    }
    
    if (t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = findNextRec(item, t->left);
    }
    return nothing;
}

Node* BST::findPrevRec(int item){
    return findPrevRec(item, root);
}

Node* BST::findPrevRec(int item, Node *n){
    Node *current = n, *t = n, *nothing = nullptr, *parent = nullptr;
    if (n == nullptr)
        return nothing;
    
    //while(current->right != nullptr){
    if (current->right != nullptr){
        if (current->info == item){
            if (current->left != nullptr){
                if(current->left->right != nullptr)
                    return current->left->right;
                else
                    return current->left;
            }
            else if (n->left == nullptr){
                if(parent->info > item)
                    return parent;
            }
        }
        else if (current->left->info == item){
            if (current->left->right != nullptr){
                if(current->left->right->left != nullptr)                    return current->left->right->left;
                else
                    return current->left->right;
            }
            else if (current->left->right == nullptr){
                if(current->info > item)
                    return current;
            }
        }
        parent = current;
        current = findPrevRec(item, current->right);
    }
    
    if (t->left != nullptr){
        if (t->info == item){
            if (t->right != nullptr){
                if(t->right->left != nullptr)
                    return t->right->left;
                else
                    return t->right;
            }
            else if (n->right == nullptr){
               
                if(parent->info > item)
                    return parent;
            }
        }
        parent = t;
        t = findPrevRec(item, t->left);
    }
    return nothing;
}
