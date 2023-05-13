//
//  websiteClass.hpp
//  FinalProject
//
//  Created by Mahmoud Mohamed on 11/26/22.
//

#ifndef websiteClass_hpp
#define websiteClass_hpp

#include <stdio.h>
#include "AvlTree.hpp"
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class website{
private:
public:
    AVLTree tree;
    float pageRank;
    string name;
    float score;
    int impressions;
    int clicks;
    float ctr;
    int exactRank;
    void updateScore();
    void updateCtr();
};
vector<float> getPageRank(vector<vector<int>> Matrix);
vector<int> getExactRank(vector<float> PageRank);
vector<vector<int>> getGraphMatrix(string FileName,vector<string> websiteNames);
#endif /* websiteClass_hpp */
