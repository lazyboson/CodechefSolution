/*Problem -  https://www.codechef.com/problems/BSTOPS*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

struct BSTnode {
    long long  key;
    long long position;
    BSTnode* parent;
    BSTnode* left;
    BSTnode* right;
};

class BST {
public:
    BSTnode* root;
    BST() {
        root = nullptr;
    }
    long long insertion(BSTnode* current);
    BSTnode* TreeMinimum(BSTnode* current);
    void deletion(BSTnode* current);
    void Transplant(BSTnode* u, BSTnode* v);
    BSTnode* Search(long long key);
    void InorderTraversal(BSTnode*);
};


long long BST::insertion(BSTnode *current) {
    BSTnode* y = nullptr;
    //traverse using this pointer
    BSTnode* x = root;
    long long cnt = 1;
    while (x!= nullptr) {
        y = x;
        if(current->key < x->key) {
            cnt *= 2LL;
            x = x->left;
        }
        else {
            x = x->right;
            cnt = 2*cnt +1LL;
        }
    }
    current->parent = y;
    if(y == nullptr) {
        root = current;  //tree was empty
        root->position = 1LL;
        return 1LL;
    }
    else if (current->key < y->key) {
        //insert
        y->left = current;
        current->position = cnt;
    }
    else {
        y->right = current;
        current->position = cnt;
    }
    return cnt;
}

void BST::Transplant(BSTnode *u, BSTnode *v) {
    if(u->parent == nullptr)
        root  = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v != nullptr)
        v->parent = u->parent;
}

BSTnode *BST::TreeMinimum(BSTnode *current) {
    while (current->left != nullptr)
        current = current->left;
    return current;
}


void BST::deletion(BSTnode *current) {
    BSTnode *y = nullptr;
    if(current->left == nullptr)
        Transplant(current, current->right);
    else if (current->right == nullptr)
        Transplant(current, current->left);
    else {
        y = TreeMinimum(current->right);
        if(y->parent != current) {
            Transplant(y, y->right);
            y->right = current->right;
            y->right->parent = y;
        }
        Transplant(current, y);
        y->left = current->left;
        y->left->parent = y;
    }
}

BSTnode *BST::Search(long long key) {
    BSTnode* x = root;
    while ( x!= nullptr && key != x->key) {
        if(key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return  x;
}

void BST::InorderTraversal(BSTnode* current) {
    if(current == nullptr)
        return;
    InorderTraversal(current->left);
    cout << "Key: "<< current->key << "  Position: " << current->position << "\n";
    InorderTraversal(current->right);

}


int main() {
    ios_base::sync_with_stdio(false);
    int Q;
    char ope;
    long long data;
    cin>>Q;
    BST _bst;
    while (Q--) {
        cin >> ope >> data;
        if(ope == 'i') {
            BSTnode* node = new BSTnode;
            node->key = data;
            node->left = node->right = node->parent = nullptr;
            node->position = 1LL;
            long long ans= _bst.insertion(node);
            cout << ans << endl;
        }
        else {
            BSTnode* node = _bst.Search(data);
            //printing position data
            cout << node->position << endl;
            _bst.deletion(node);
        }
    }

//     BSTnode* n = _bst.root;
//    _bst.InorderTraversal(n);
    return 0;
}


