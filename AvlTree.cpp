//
//  AvlTree.cpp
//  FinalProject
//
//  Created by Mahmoud Mohamed on 11/26/22.
//

#include "AvlTree.hpp"
bool compareStrings(string s1, string s2){
    char c1;
    char c2;
    int minSize;
    if(s1.size()>s2.size()){
        minSize=int(s2.size());
    }
    else{
        minSize=int(s1.size());
    }
    for(int i=0;i<minSize;i++){
        c1=int(s1[i]);
        c2=int(s2[i]);
        if(c1>c2){
            return true;
        }
        else if(c2>c1){
            return false;
        }
    }
    if(minSize==s1.size() && minSize==s2.size()){
        return false;
    }
    if(minSize==s1.size()){
        return false;
    }
    else{
        return true;
    }
   
}


    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void AVLTree:: initializeNode(NodePtr node, string key) {
        node->data = key;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->bf = 0;
    }

    

    NodePtr AVLTree::searchTreeHelper(NodePtr node, string key) {
        if (node == nullptr || key == node->data) {
            return node;
        }

        if (compareStrings(node->data, key)) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    

    // update the balance factor the node
    void AVLTree::updateBalance(NodePtr node) {
        if (node->bf < -1 || node->bf > 1) {
            rebalance(node);
            return;
        }

        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->bf -= 1;
            }

            if (node == node->parent->right) {
                node->parent->bf += 1;
            }

            if (node->parent->bf != 0) {
                updateBalance(node->parent);
            }
        }
    }

    // rebalance the tree
void AVLTree::rebalance(NodePtr node) {
        if (node->bf > 0) {
            if (node->right->bf < 0) {
                rightRotate(node->right);
                leftRotate(node);
            } else {
                leftRotate(node);
            }
        } else if (node->bf < 0) {
            if (node->left->bf > 0) {
                leftRotate(node->left);
                rightRotate(node);
            } else {
                rightRotate(node);
            }
        }
    }


AVLTree::AVLTree() {
        root = nullptr;
    }


    // search the tree for the key k
    // and return the corresponding node
    NodePtr AVLTree::searchTree(string k) {
        return searchTreeHelper(this->root, k);
    }

    // rotate left at node x
    void AVLTree::leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        // update the balance factor
        x->bf = x->bf - 1 - max(0, y->bf);
        y->bf = y->bf - 1 + min(0, x->bf);
    }

    // rotate right at node x
    void AVLTree::rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        // update the balance factor
        x->bf = x->bf + 1 - min(0, y->bf);
        y->bf = y->bf + 1 + max(0, x->bf);
    }

    // insert the key to the tree in its appropriate position
    void AVLTree::insert(string key) {
        // PART 1: Ordinary BST insert
        NodePtr node = new Node;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->data = key;
        node->bf = 0;
        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != nullptr) {
            y = x;
            if (compareStrings(x->data, node->data)) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (compareStrings(y->data, node->data)) {
            y->left = node;
        } else {
            y->right = node;
        }

        // PART 2: re-balance the node if necessary
        updateBalance(node);

    }


vector<AVLTree> buildTrees(vector<vector<string>> keyWords){
    vector<AVLTree> treesForKeywords;
    for(int i=0;i<keyWords.size();i++){
        AVLTree tree;
        tree.insert(keyWords[i][0]);
        for(int j=1;j<keyWords[i].size();j++){
            tree.insert(keyWords[i][j]);
        }
        treesForKeywords.push_back(tree);
    }
    return treesForKeywords;
    
}
