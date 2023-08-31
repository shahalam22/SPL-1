#include <iostream>
#include <fstream>
#include <string>
#include "page.h"
using namespace std;


//creating relevent vectors
vector<string> urlList{};
vector<string> idList{};
vector<int> indexList{};
//creating webpages
vector<Page> webPages{};
vector<vector<int>> inLinkVector;
vector<vector<int>> outLinkVector;


// UPDATE GRAPH
void updateGraph(){
    for(int i=0; i<urlList.size(); i++){
        Page tempPage;
        tempPage.initializeData(urlList.at(i), idList.at(i), indexList.at(i), inLinkVector.at(i), outLinkVector.at(i));
        webPages.push_back(tempPage);
    }
}


// ADDNEW WEBPAGE FUNCTION
void addNewPage(string address, string idNo, int indexNO, vector<int> in, vector<int> out){
    //updating general values
    Page tempPage;
    tempPage.initializeData(address, idNo, indexNO, in, out);
    webPages.push_back(tempPage);
    urlList.push_back(address);
    idList.push_back(idNo);
    indexList.push_back(indexNO);
}


// GRAPH INITIALIZE FUNCTION
void initialLoad(){
    //initializing URL vector
    fstream urlFile;
    urlFile.open("urlList.txt");
    if(!urlFile){
        cout << "Such URL file doesn't exist!" << endl;
    }else{
        for(int i=0; !urlFile.eof(); i++){
            string tempUrl;
            urlFile >> tempUrl;
            urlList.push_back(tempUrl);
        }
    }
    urlFile.close();

    //initializing ID vector
    fstream idFile;
    idFile.open("idList.txt");
    if(!idFile){
        cout << "Such ID file doesn't exist!" << endl;
    }else{
        for(int i=0; !idFile.eof(); i++){
            string tempId;
            idFile >> tempId;
            idList.push_back(tempId);
        }
    }
    idFile.close();

    //initializing indexList vector
    fstream indexFile;
    indexFile.open("indexList.txt");
    if(!indexFile){
        cout << "Such ID file doesn't exist!" << endl;
    }else{
        for(int i=0; !indexFile.eof(); i++){
            int tempIndex;
            indexFile >> tempIndex;
            indexList.push_back(tempIndex);
        }
    }
    indexFile.close();

    //initializing INLINKS vector
    fstream inlinkFile;
    inlinkFile.open("inLinks.txt");
    if(!inlinkFile){
        cout << "Such outlink vector file doesn't exist!" << endl;
    }else{
        for(int i=0; !inlinkFile.eof(); i++){
            vector<int> temp{};
            string x;
            std::getline(inlinkFile, x);
            for(char &c : x){
                if(c != ','){
                    int s;
                    s = c-'0';
                    temp.push_back(s);
                }
            }
            inLinkVector.push_back(temp);
        }
    }
    inlinkFile.close();

    //initializing OUTLINKS vector
    fstream outLinkFile;
    outLinkFile.open("outLinks.txt");
    if(!outLinkFile){
        cout << "Such outlink vector file doesn't exist!" << endl;
    }else{
        for(int i=0; !outLinkFile.eof(); i++){
            vector<int> temp{};
            string x;
            std::getline(outLinkFile, x);
            for(char &c : x){
                if(c != ','){
                    int s;
                    s = c-'0';
                    temp.push_back(s);
                }
            }
            outLinkVector.push_back(temp);
        }
    }
    outLinkFile.close();

    updateGraph();
}


// VALID SITE FUNCTION - is a page exists in the graph or not
void findByUrl(string address){
    int flag = -1;
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).getName() == address){
            flag = i;
            break;
        }
    }

    if(flag==-1){
        cout << "Page not found." << endl;
    }else{
        webPages.at(flag).printPage();
        cout << endl;
    }
}

void findById(string idList){
    int flag = -1;
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).getId() == idList){
            flag = i;
            break;
        }
    }

    if(flag==-1){
        cout << "Page not found." << endl;
    }else{
        webPages.at(flag).printPage();
        cout << endl;
    }
}


// DANGLING NODE FUNCTION
vector<Page> danglingNodes(){
    vector<Page> Dpages{};
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).isDangling()){
            Dpages.push_back(webPages.at(i));
        }
    }
    return Dpages;
}


// PRINTING ALL THE WEBPAGES IN THE GRAPH
void printAllPagesDetails(){
    for(int i=0; i<urlList.size(); i++){
        webPages[i].printPage();
        cout << endl;
    }
}