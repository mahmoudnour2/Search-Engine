//
//  AvlTree.hpp
//  FinalProject
//
//  Created by Mahmoud Mohamed on 11/26/22.
//

#ifndef AvlTree_hpp
#define AvlTree_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
bool compareStrings(string s1, string s2);
struct Node {
    string data;
    Node *parent;
    Node *left;
    Node *right;
    int bf;
};
typedef Node *NodePtr;
class AVLTree {
private:
    NodePtr root;
    void initializeNode(NodePtr node, string key);
    NodePtr searchTreeHelper(NodePtr node, string key);
    void updateBalance(NodePtr node);
    void rebalance(NodePtr node);
public:
    AVLTree();
    NodePtr searchTree(string k);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);
    void insert(string key);

};
vector<AVLTree> buildTrees(vector<vector<string>> keyWords);

#endif /* AvlTree_hpp */
