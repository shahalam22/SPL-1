#include <iostream>
#include <vector>
using namespace std;

//making page class
class Page{
    private: 
    string url;
    string id;
    bool isDanglingNode = true;
    vector<int> outLinks{};
    
    public:

    //initializing properties of an object of Page class
    void getdata(string address, string idNo, vector<int> arr){
        url = address;
        id = idNo;
        for(int i=0; i<arr.size(); i++){
            if(arr[i]==1) isDanglingNode = false;
            outLinks.push_back(arr[i]);
        }
    }

    //update properties of one page
    void updateUrl(string address){
        url = address;
    }
    void updateId(string idNo){
        id = idNo;
    }
    void updateOutLinks(vector<int> arr){
        outLinks.clear();
        isDanglingNode = true;
        for(int i=0; i<arr.size(); i++){
            if(arr[i]==1) isDanglingNode = false;
            outLinks.push_back(arr[i]);
        }
    }

    //find neighbours
    void Neighbours(string address, vector<Page> webPages, vector<vector<int>> matrix){
        int d = 0, j = 1;

        //finding index
        for(; d<webPages.size(); d++){
            string name = webPages.at(d).getName();
            if(name == address){
                break;
            }
        }
        // outlinks
        cout << "OutLink pages of this page are : " << endl;
        for(int i=0; i<matrix.size(); i++){
            if(matrix[d][i]){
                cout << j << ". ";
                webPages.at(i).printName();
                j++;
            }
        }
        cout << endl;
        // inlinks
        cout << "InLinks pages of this page are : " << endl;
        for(int i=0; i<matrix.size(); i++){
            if(matrix[i][d]){
                cout << j << ". ";
                webPages.at(i).printName();
                j++;
            }
        }
        cout << endl;
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
};