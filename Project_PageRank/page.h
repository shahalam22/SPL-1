#include <iostream>
#include <vector>
using namespace std;

//making page class
class Page{

    private: 

    string url;
    string id;
    bool isDanglingNode = true;
    vector<string> outLinks{};
    vector<string> inLinks{};
    
    public:

    //initializing properties of an object of Page class
    void initializeData(string address, string idNo, vector<string> in, vector<string> out){
        url = address;
        id = idNo;
        for(int i=0; i<in.size(); i++){
            inLinks.push_back(in.at(i));
        }
        for(int i=0; i<out.size(); i++){
            outLinks.push_back(out.at(i));
        }
        if(outLinks.size()==0 || inLinks.size()==0){
            isDanglingNode = true;
        }else{
            isDanglingNode = false;
        }
    }


    //update properties of one page
    void updateUrl(string address){
        url = address;
    }

    void updateId(string idNo){
        id = idNo;
    }

    void updateInLinks(vector<string> in){
        inLinks.clear();
        for(int i=0; i<in.size(); i++){
            inLinks.push_back(in.at(i));
        }
        if(inLinks.size()==0){
            isDanglingNode = true;
        }else{
            isDanglingNode = false;
        }
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
        cout << "Id of the page is : " << id << endl;
        // cout << "Out Links from the page is : ";
        // for(int i=0; i<outLinks.size(); i++){
        //     cout << outLinks[i] << " ";
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


    string getId(){
        return id;
    }


    //find neighbours
    void Neighbours(vector<Page> webPages){
        // outlinks
        cout << "OutLink pages of this page are : \n\n";
        for(int i=0; i<outLinks.size(); i++){
            for(int j=0; j<webPages.size(); j++){
                if(outLinks.at(i) == webPages.at(j).getId()){
                    webPages.at(j).printPage();
                }
            }
        }
        cout << endl;
        // inlinks
        cout << "InLink pages of this page are : \n\n";
        for(int i=0; i<inLinks.size(); i++){
            for(int j=0; j<webPages.size(); j++){
                if(outLinks.at(i) == webPages.at(j).getId()){
                    webPages.at(j).printPage();
                }
            }
        }
        cout << endl;
    }   
};