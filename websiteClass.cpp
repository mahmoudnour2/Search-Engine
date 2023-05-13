//
//  websiteClass.cpp
//  FinalProject
//
//  Created by Mahmoud Mohamed on 11/26/22.
//

#include "websiteClass.hpp"

void  website :: updateScore(){
    float firstSmallBracket=1-((0.1*impressions)/(1+0.1*impressions));
    float secondSmallBracket=(0.1*impressions)/(1+0.1*impressions);
    float bigBracket=(firstSmallBracket*pageRank)+(secondSmallBracket*ctr);
    float total=0.4*pageRank+(bigBracket*0.4);
    score=total;
    //formula to update score using the impressions,ctr, and pageRank in the object
}
void website::updateCtr(){
    ctr=float(clicks)/impressions;
}
vector<float> getPageRank(vector<vector<int>> Matrix){
    vector<vector<float>> Page_rank;
    vector<float> InitialPageRank;
    for(int i=0;i<Matrix.size();i++){
        InitialPageRank.push_back(1/float(Matrix.size()));
    }
    Page_rank.push_back(InitialPageRank);
    
    vector<int> rowsSum; //element i is the sum of the i'th row in the matrix
    //i is the row num and j is the col num
    for(int i=0;i<Matrix.size();i++){
        int sum=0;
        for(int j=0;j<Matrix.size();j++){
            sum=sum+Matrix[i][j];
        }
        rowsSum.push_back(sum);
    }
    //getting the sum of each row
    int s=0;
    for(int k=0;k<1000;k++){
        vector<float> pageRank;
        for(int j=0;j<Matrix.size();j++){
            //getting the page rank of the j'th element
            float sum=0;
            for(int i=0;i<Matrix.size();i++){
                //traversing to check the parents of j
                if(Matrix[i][j]==1){
                    //if one is found we get the sum of its row (the number of nodes it is pointing to) from the vector rowsSum and divide the page rank of the parent (i) in the k'th iteration by the number of nodes it is ponting to
                    sum=sum+float(Page_rank[k][i])/rowsSum[i];
                }
            }
            pageRank.push_back(sum);
        }
        Page_rank.push_back(pageRank);
        if(s==Page_rank[k][0]){
            k=1000;
        }
        else{
            s=Page_rank[k][0];}
    }
    vector<float> FinalPageRank;
    FinalPageRank=Page_rank[Page_rank.size()-1];
    //sort FinalPageRank by ranking
    float max=-1;
    bool greaterThanOne=false;
    for(int i=0;i<FinalPageRank.size();i++){
        if(FinalPageRank[i]>max){
            max=FinalPageRank[i];
            if(max>1){
                greaterThanOne=true;
            }
        }
    }
    if(greaterThanOne==true){
        for(int i=0;i<FinalPageRank.size();i++){
            FinalPageRank[i]=FinalPageRank[i]/max;
        }
    }
    
    return FinalPageRank;
}

vector<int> getExactRank(vector<float> PageRank){
    float max=0;
    vector<int> exactRank(PageRank.size(),0);
    int rankCtr=int(PageRank.size());
    int maxIdx=0;
    for(int i=0;i<PageRank.size();i++){
        max=0;
        for(int j=0;j<PageRank.size();j++){
            if(PageRank[j]>=max){
                max=PageRank[j];
                maxIdx=j;
            }
        }
        PageRank[maxIdx]=-1;
        exactRank[maxIdx]=rankCtr;
        rankCtr--;
    }
    return exactRank;
}
vector<vector<int>> getGraphMatrix(string FileName,vector<string> websiteNames){
    unordered_map<string, int> u_map;
    for(int i=0;i<websiteNames.size();i++){
        u_map.insert({websiteNames[i],i});
    }
    //mapping websites to the indexes of the order they are written in the keywords file, the name of the website is the key. In the Matrix,each website name is represented by its index
    int NodesNum=int(websiteNames.size());
    vector<vector<int>> Matrix(NodesNum,vector<int> (NodesNum,0)); //initializing a 2D vector with size NodesNum*NodesNum to be all zeros
    ifstream webGraphFile;
    webGraphFile.open(FileName);
    string line2;
    while(getline(webGraphFile,line2)){
        stringstream inputString(line2);
        string s1;
        inputString>>s1;
        string s2;
        inputString>>s2;
        int edgeSrc=u_map[s1];
        int edgeDest=u_map[s2];
        Matrix[edgeSrc][edgeDest]=1;
    }//filling the 2D matrix
    webGraphFile.close();
    return Matrix;
}
