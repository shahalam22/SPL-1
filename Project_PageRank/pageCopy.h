#include <iostream>
#include <vector>
#include "socket.h"
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
    void initializeData(string address, int indexNo){
        url = address;
        index = indexNo;
        outLinks = listOfOutgoingURLs(address);
        if(outLinks.size()==0){
            isDanglingNode = true;
        }else{
            isDanglingNode = false;
        }
    }


    //update properties of one page
    void updatePage(string address){
        url = address;
    }

    void updateOutLinks(vector<string> out){
        outLinks.clear();
        for(int i=0; i<out.size(); i++){
            outLinks.push_back(out.at(i));
        }
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
        if(outLinks.size() != 0){
            cout << "OutLinks of this page - ";
            for(int j=0; j<outLinks.size(); j++){
                cout << outLinks.at(j) << " ";
            }
            cout << endl;
        }else{
            cout << "This is a dangling node." << endl;
        }
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


    // //find neighbours
    // void Neighbours(){
    //     // outlinks
    //     cout << "OutLink neighbours of this page : \n\n";
    //     for(int i=0; i<outLinks.size(); i++){
    //         for(int j=0; j<webPages.size(); j++){
    //             if(outLinks.at(i) == webPages.at(j).getIndex()){
    //                 cout << "URL of the page is : " << webPages.at(j).getName() << endl;
    //                 cout << "Index of the page is : " << webPages.at(j).getIndex() << endl;
    //                 cout << endl;
    //             }
    //         }
    //     }
    //     cout << endl;
    // }   
};