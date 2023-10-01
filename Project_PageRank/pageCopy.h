#include <iostream>
#include <vector>
using namespace std;

//making page class
class Page{

    private: 

    string url;
    string id;
    int index;
    bool isDanglingNode = true;
    vector<int> outLinks{};
    
    public:

    //initializing properties of an object of Page class
    void initializeData(string address, string idNo, int indexNo, vector<int> out){
        url = address;
        id = idNo;
        index = indexNo;
        for(int i=0; i<out.size(); i++){
            outLinks.push_back(out.at(i));
        }
        if(outLinks.size()==0){
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

    void updateOutLinks(vector<int> out){
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
        cout << "Index of the page is : " << index << endl;
        cout << "OutLinks of this page - ";
        for(int j=0; j<outLinks.size(); j++){
            cout << outLinks.at(j) << " ";
        }
        cout << endl;
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

    int getIndex(){
        return index;
    }

    vector<int> getOutLinks(){
        return outLinks;
    }


    //find neighbours
    void Neighbours(vector<Page> webPages){
        // outlinks
        cout << "OutLink neighbours of this page : \n\n";
        for(int i=0; i<outLinks.size(); i++){
            for(int j=0; j<webPages.size(); j++){
                if(outLinks.at(i) == webPages.at(j).getIndex()){
                    cout << "URL of the page is : " << webPages.at(j).getName() << endl;
                    cout << "Id of the page is : " << webPages.at(j).getId() << endl;
                    cout << "Index of the page is : " << webPages.at(j).getIndex() << endl;
                    cout << endl;
                }
            }
        }
        cout << endl;
    }   
};