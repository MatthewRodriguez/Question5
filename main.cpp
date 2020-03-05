#include "BST.h"

class Nodes{
    public:
    int key;
    Nodes *left;
    Nodes *right;
    int height;
};

int max(int a, int b);
int height(Nodes *n);
int max(int a, int b);
int getBalance(Nodes *n);
Nodes* newNode(int key);
Nodes *rightRotate(Nodes *y);
Nodes *leftRotate(Nodes *x);
Node* deleteIter(Node *n, int item);
Node* deleteFromTree(Node* &n);
Node* findMaxIter(Node *n);
Node* findMinIter(Node *n);
Node* findPrevIter(Node *n, int item);
Node* findNextIter(Node *n, int item);
Nodes* insertRec(Nodes *node, int item);
Nodes* insertIter(Nodes *n, int item);
void preOrder(Nodes *root);
void getRandomArray(int n);
void getSortedArray(int n);

int main(){
    getRandomArray(10);
    getSortedArray(10);

    return 0;
}

int height(Nodes *n){
    return n == nullptr ? 0 : n->height;
}
  
int max(int a, int b){
    return (a > b)? a : b;
}
  
Nodes* newNode(int key){
    Nodes* nod = new Nodes();
    nod->key = key;
    nod->left = NULL;
    nod->right = NULL;
    nod->height = 1;
    return(nod);
}
  
Nodes *rightRotate(Nodes *b){
    Nodes *a = b->left;
    Nodes *c = a->right;
    a->right = b;
    b->left = c;
    b->height = max(height(b->left), height(b->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;
    return a;
}
  
Nodes *leftRotate(Nodes *a){
    Nodes *b = a->right;
    Nodes *c = b->left;
    b->left = a;
    a->right = c;
    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;
    return b;
}
  
int getBalance(Nodes *n){
    return n == nullptr ? 0 : height(n->left) - height(n->right);
}

Nodes* balance(Nodes* n, int key){
    int bf = getBalance(n);
    if (bf > 1 && key < n->left->key)
      return rightRotate(n);

    if (bf < -1 && key > n->right->key)
      return leftRotate(n);

    if (bf > 1 && key > n->left->key)
    {
      n->left = leftRotate(n->left);
      return rightRotate(n);
    }

    if (bf < -1 && key < n->right->key)
    {
      n->right = rightRotate(n->right);
      return leftRotate(n);
    }
    return n;
}

Nodes* insertRec(Nodes* node, int key){
    if (node == NULL)
        return(newNode(key));
  
    if (key < node->key){
        node->left = insertRec(node->left, key);
    }
    else if (key > node->key){
        node->right = insertRec(node->right, key);
    }
    else
        return node;
  
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
   
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


Nodes* insertIter(Nodes* n, int item){
    Nodes *c, *p = nullptr, *node;
    int count = 0;
    node = newNode(item);
    
    if (n == nullptr)
       return n = node;
    else{
        n->height = 1 + max(height(n->left), height(n->right));
       c = n;
       while (c != nullptr){
           p = c;
           if (c->key == item)
               return n;
           else if (c->key > item){
               count++;
               c = c->left;
           }
           else{
               count++;
               c = c->right;
           }
       }
        node->height = 1 + max(height(node->left), height(node->right));
       if (p->key > item)
           p->left = node;
       else
           p->right = node;
    }
    balance(n, item);
    return n;
}

Node* deleteFromTree(Node* &n){
    Node *current, *prev, *temp;
    if (n == nullptr)
        return n;
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
    return n;
}

Node* deleteIter(Node *n, int item){
    Node *current, *prev;
    bool found = false;
    
    if (n == nullptr)
        return n;
    else{
        current = n;
        prev = n;
        
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
            return n;
        else if (found){
            if (current == n)
                deleteFromTree(n);
            else if (prev->info > item)
                deleteFromTree(prev->left);
            else
                deleteFromTree(prev->right);
        }
    }
    return n;
}

Node* findMaxIter(Node *n){
    if (n != nullptr)
        while(n->right != nullptr)
            n = n->right;
    return n;
}

Node* findMinIter(Node *n){
    if (n != nullptr)
        while (n->left != nullptr)
            n = n->left;
    return n;
}

Node* findPrevIter(Node *n, int item){
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
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
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

Node* findNextIter(Node *n, int item){
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
                if(current->left->right->left != nullptr)
                    return current->left->right->left;
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

void preOrder(Nodes *root){
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void getRandomArray(int n) {
    BST tree;
    Nodes *root = NULL;
    int arr[n], j, t;
    for (int i = 0; i < n; i++)
        arr[i] = i+1;

    for (int i = 0; i < n; i++) {
        j = rand()%n;

        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
    
    
    for (int j = 0; j < n; j++){
        tree.insertIter(j);
        root = insertRec(root, j);
    }
    cout << "GetRandomArray: " << endl;
    cout << "BSt output: " << endl;
    tree.preOrder();
    cout << endl;
    cout << "AVL output: " << endl;
    preOrder(root);
    cout << endl;
}

void getSortedArray(int n){
    BST tree;
    Nodes *r = NULL;
    int arr[n];
    int j = n-1;
    if (n % 2 == 0){
        for (int i = 0; i < n; i++){
            if (i != (n/2)){
                arr[i] = i;
                arr[j] = i;
            }
            else
                break;
            j--;
        }
    }
    else
        cout << "it's not even";
    for (int j = 0; j < n; j++){
        tree.insertIter(j);
        r = insertRec(r, j);
    }
    cout << "GetSortedArray: " << endl;
    cout << "BSt output: " << endl;
    tree.preOrder();
    cout << endl;
    cout << "AVL output: " << endl;
    preOrder(r);
    cout << endl;
}

