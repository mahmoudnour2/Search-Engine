//
//  main.cpp
//  FinalProject
//
//  Created by Mahmoud Mohamed on 11/26/22.
//

#include "websiteClass.hpp"
#include "AvlTree.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
//Simulating Functions
void simulateProgram(string keywordsFile,string webgraphFile,string impressionsFile,string clicksFile);
int simulateOpeningMessage();
int simulateSecondPage();
int simulateThirdPage(int counter);
int simulateFourthPage();
int simulateSearchResults();

vector<int> getOrderOfAppearance(vector<website> web);

vector<website> Get_websites(string keywordsFileName, string webGraphFile, string ImpressionsFile,string clicksFile);
//loads all info from file and creates a vector of websites (calculates pagerank)
vector<int> outputSearchResults(vector<bool>present,int& counter,vector<website> websites);
vector<bool> searchAndResults(vector<website> websites,string impressionsFile);
vector<int> loadImpressions(vector<string> NamesOfWebsites, string fileName);
vector<int> loadClicks(vector<string> NamesOfWebsites, string fileName);
void updateImpressions(vector <website> websites,string fileName,vector<bool> present);
void updateClicks(vector <website> websites,string fileName,int key);
int main() {
    
    int decision=simulateOpeningMessage();
    if(decision == 2){
        return 1;
    }
    
    simulateProgram("/Users/mahmoudnour/Desktop/AUC/Fall 2022/Analysis Lab/FinalProject/FinalProject/Keywords.csv","/Users/mahmoudnour/Desktop/AUC/Fall 2022/Analysis Lab/FinalProject/FinalProject/Webgraph.csv","/Users/mahmoudnour/Desktop/AUC/Fall 2022/Analysis Lab/FinalProject/FinalProject/Impressions.csv","/Users/mahmoudnour/Desktop/AUC/Fall 2022/Analysis Lab/FinalProject/FinalProject/Clicks.csv");
    
}


void simulateProgram(string keywordsFile,string webgraphFile,string impressionsFile,string clicksFile){
    vector<website>
    websites=Get_websites(keywordsFile,webgraphFile,impressionsFile,clicksFile);
    
    int counter=1;
    
    vector<bool> present=searchAndResults(websites,impressionsFile);
    int k=0;
    while(k==0){
        k=1;
    vector<int> appearanceNum=outputSearchResults(present,counter,websites);//update Impressions
    int decision2=simulateSecondPage();
    if(decision2==3){
        return;
    }
    
    if(decision2==1){
        
        int choiceNum=simulateThirdPage(counter);
        int input;
        for(int i=0;i<appearanceNum.size();i++){
            if(appearanceNum[i]==choiceNum){
                cout<<"You are now viewing "<<websites[i].name<<endl;
                updateClicks(websites, clicksFile, i);
                //update clicks
                input=simulateFourthPage();
                if(input==3){
                    return;
                }
                if(input==1){
                    counter=1;
                    k=0;
                }
                if(input==2){
                    simulateProgram(keywordsFile,webgraphFile,impressionsFile,clicksFile);
                }
                
            }
        }
        
    }
    if (decision2==2){
        simulateProgram(keywordsFile, webgraphFile, impressionsFile, clicksFile);
    }
    counter=1;
    }
}
vector<bool> searchAndResults(vector<website> websites,string impressionsFile){
    bool quotations=false;
    string searchValue;
    cout<<"Search: ";
    cin.ignore();
    getline(cin,searchValue);
    if(searchValue[0]=='"' && searchValue[searchValue.size()-1]=='"'){
        quotations=true;
        searchValue=searchValue.substr(1,searchValue.size()-1);
    }
    stringstream inputString(searchValue);
    string word;
    vector<string> words;
    while(inputString>>word){
        words.push_back(word);
    }
    vector<bool> present(websites.size(),0);
    
    if(quotations==true){
        
        for(int i=0;i<websites.size();i++){
            if(websites[i].tree.searchTree(searchValue)){
                present[i]=true;
                
            }
        }
    }
    else if(words[1]=="and"){
        
        for(int i=0;i<websites.size();i++){
            if(websites[i].tree.searchTree(words[0])&&websites[i].tree.searchTree(words[2])){
                present[i]=true;
                
            }
        }
    }
    else if(words[1]=="or"){
        
        for(int i=0;i<websites.size();i++){
            if(websites[i].tree.searchTree(words[0]) || websites[i].tree.searchTree(words[2])){
                present[i]=true;
            }
        }
    }
    else{
        
        int numOfWords=int(words.size());
        if(numOfWords==1){
            
            for(int i=0;i<websites.size();i++){
                if(websites[i].tree.searchTree(words[0])){
                    present[i]=true;
                }
            }
        }
        else{
            for(int i=0;i<websites.size();i++){
                if(websites[i].tree.searchTree(words[0]) || websites[i].tree.searchTree(words[2])){
                    present[i]=true;
                }
            }
        }
    }
    updateImpressions(websites,impressionsFile,present);
    return present;
}
vector<int> outputSearchResults(vector<bool>present,int& counter,vector<website> websites){
    vector<int> order=getOrderOfAppearance(websites);
    vector<int> appearanceNum(websites.size(),0);
    
    for(int i=int(order.size())-1;i>=0;i--){
        int websiteKey=order[i];
        if(present[websiteKey]==true){
            appearanceNum[websiteKey]=counter;
            cout<<counter<<". "<<websites[websiteKey].name<<endl;
            counter++;
        }
    }
    counter--;
    return appearanceNum;
}
int simulateOpeningMessage(){
    cout<<"Welcome"<<endl<<"What would you like to do?"<<endl;
    int input;
    cout<<"1. New Search ";
    cout<<endl;
    cout<<"2. Exit "<<endl;
    cin>>input;
    while(input!=1 && input != 2){
        cout<<"Invalid Input, try again!"<<endl;
        cout<<"1. New Search ";
        cout<<endl;
        cout<<"2. Exit "<<endl;
        cin>>input;
    }
    return input;
}
int simulateSecondPage(){
    cout<<"Would you like to"<<endl;
    cout<<"1. Choose a webpage to open"<<endl<<"2. New search"<<endl<<"3. Exit"<<endl;
    int input;
    cout<<"Type in your choice: ";
    cin>>input;
    while(input!= 1 && input!=2 && input!=3){
        cout<<"Invalid input, try again!"<<endl;
        cin>>input;
    }
    return input;
}
int simulateThirdPage(int counter){
    cout<<"Which webpage do you want to open ";
    int input;
    cin>>input;
    while(input>counter){
        cout<<"Invalid input, try again!"<<endl;
        cin>>input;
    }
    return input;
}
int simulateFourthPage(){
    cout<<"Would you like to"<<endl;
    cout<<"1. Back to search results"<<endl<<"2. New search"<<endl<<"3. Exit"<<endl;
    int input;
    cout<<"Type in your choice: ";
    cin>>input;
    while(input!= 1 && input!=2 && input!=3){
        cout<<"Invalid input, try again!"<<endl;
        cin>>input;
    }
    return input;
}



vector<int> getOrderOfAppearance(vector<website> web ){
    vector<int> Order(web.size(),2);
    for(int i=0;i<web.size();i++){
        int rankOfWebsite=web[i].exactRank;
        int inter=rankOfWebsite-1;
        Order[inter]=i;
    }
    return Order;
}

vector<website> Get_websites(string keywordsFileName, string webGraphFile, string ImpressionsFile,string clicksFile){
    ifstream KeyWordsFile;
    KeyWordsFile.open(keywordsFileName);
    string line;
    vector<vector<string>> allKeyWords; //first vector is the strings of the first website,etc...
    vector<string> websiteNames;
    while(getline(KeyWordsFile, line)){
        stringstream inputString(line);
        string website;
        getline(inputString, website, ',');
        websiteNames.push_back(website);
        vector<string> keywords_for_website;
        string s1;
        while(getline(inputString, s1, ',')){
            keywords_for_website.push_back(s1);
        }
        allKeyWords.push_back(keywords_for_website);
        line="";
    }
    KeyWordsFile.close();
    //    for(int i=0;i<allKeyWords[2].size();i++){
    //        cout<<allKeyWords[2][i]<<" ";
    //    }
    vector<AVLTree> trees=buildTrees(allKeyWords);
    vector<vector<int>> webGraphEdgesMatrix=getGraphMatrix(webGraphFile,websiteNames);
    vector<float> ranks=getPageRank(webGraphEdgesMatrix);
    vector<int> impressions=loadImpressions(websiteNames,ImpressionsFile);
    vector<int> clicks=loadClicks(websiteNames, clicksFile);
    vector<int> exactRanks=getExactRank(ranks);
    vector<website> websites;
    for(int i=0;i<trees.size();i++){
        website w;
        w.tree=trees[i];
        w.pageRank=ranks[i];
        w.name=websiteNames[i];
        w.impressions=impressions[i];
        w.clicks=clicks[i];
        w.updateCtr();
        w.updateScore();
        w.exactRank=exactRanks[i];
        websites.push_back(w);
    }
    return websites;
}
vector<int> loadImpressions(vector<string> NamesOfWebsites, string fileName){
    unordered_map<string, int> u_map;
    for(int i=0;i<NamesOfWebsites.size();i++){
        u_map.insert({NamesOfWebsites[i],i});
    }
    vector<int> impressions(NamesOfWebsites.size(),0);
    //parse the file and update impressions string websiteName, int impression, impressions[u_map[websiteName]=impression;
    ifstream file;
    file.open(fileName);
    string lineIterator;
    while(getline(file, lineIterator)){
        stringstream line(lineIterator);
        string s1;
        line>>s1;
        string s2;
        line>>s2;
        int impression=stoi(s2);
        impressions[u_map[s1]]=impression;
    }
    
    return impressions;
}
vector<int> loadClicks(vector<string> NamesOfWebsites, string fileName){
    unordered_map<string, int> u_map;
    for(int i=0;i<NamesOfWebsites.size();i++){
        u_map.insert({NamesOfWebsites[i],i});
    }
    vector<int> clicks(NamesOfWebsites.size(),0);
    //parse the file and update impressions string websiteName, int impression, impressions[u_map[websiteName]=impression;
    ifstream file;
    file.open(fileName);
    string lineIterator;
    while(getline(file, lineIterator)){
        stringstream line(lineIterator);
        string s1;
        line>>s1;
        string s2;
        line>>s2;
        int clicksNo=stoi(s2);
        clicks[u_map[s1]]=clicksNo;
    }
    
    return clicks;
}

void updateImpressions(vector<website> websites,string fileName,vector<bool> present){
    ofstream file;
    file.open(fileName);
    for(int i=0;i<websites.size();i++){
        if(present[i]==true){
            websites[i].impressions++;
        }
        file<<websites[i].name<<" "<<websites[i].impressions<<endl;
        
    }
    file.close();
   
}
void updateClicks(vector<website> websites,string fileName,int key){
    ofstream file;
    file.open(fileName);
    websites[key].clicks++;
    for(int i=0;i<websites.size();i++){
        file<<websites[i].name<<" "<<websites[i].clicks<<endl;
    }
    file.close();
     
}
