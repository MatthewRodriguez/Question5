#include "BST.h"

class Nodes{
    public:
    int key;
    Nodes *left;
    Nodes *right;
    int height;
};

vector<int> list;
int max(int a, int b);
int height(Nodes *n);
int max(int a, int b);
Nodes* newNode(int key);
Nodes *rightRotate(Nodes *y);
Nodes *leftRotate(Nodes *x);
int getBalance(Nodes *n);
Nodes* insertRec(Nodes* node, int key);
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


Nodes* rec(Nodes* n, int item){
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
        
        int balance = getBalance(n);
        if (balance > 1 && item < n->left->key)
            return rightRotate(n);
        if (balance < -1 && item > n->right->key)
            return leftRotate(n);
        if (balance > 1 && item > n->left->key){
            node->left = leftRotate(n->left);
            return rightRotate(n);
        }
        if (balance < -1 && item < n->right->key){
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }
    }
    return n;
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

