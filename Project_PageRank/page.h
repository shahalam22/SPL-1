#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>
#include "socketRAW.h"
using namespace std;

//making page class
class Page{

    private: 

    string url;
    int index;
    bool isDanglingNode = true;
    vector<string> outLinks;
    
    public:

    //initializing properties of an object of Page class
    void initializeData(string address, int indexNo, vector<string> out){
        url = address;
        index = indexNo;
        outLinks = out;
        if(outLinks.size()==0){
            isDanglingNode = true;
        }else{
            isDanglingNode = false;
        }
    }
    
    //data printing function of the Page class
    void printPage(){
        cout << "URL of the page is : " << url << endl;
        cout << "Index of the page is : " << index << endl;
        // if(outLinks.size() != 0){
        //     cout << "OutLinks of this page - ";
        //     for(int j=0; j<outLinks.size(); j++){
        //         cout << outLinks.at(j) << endl;
        //     }
        //     cout << endl;
        // }else{
        //     cout << "This is a dangling node." << endl;
        // }
        cout << endl;
    }


    // Returns this node is dangling or not
    bool isDangling(){
        return isDanglingNode;
    }


    //print name function
    void printName(){
        cout << url << endl;
    }

    string getName(){
        return url;
    }

    int getIndex(){
        return index;
    }

    vector<string> getOutLinks(){
        return outLinks;
    }

    vector<int> getOutLinksIndex(vector<Page> webPages){
        vector<int> outLinksIndex;
        for(int i=0; i<outLinks.size(); i++){
            for(int j=0; j<webPages.size(); j++){
                if(outLinks.at(i) == webPages.at(j).getName()){
                    outLinksIndex.push_back(webPages.at(j).getIndex());
                }
            }
        }
        return outLinksIndex;
    }
};


#endif