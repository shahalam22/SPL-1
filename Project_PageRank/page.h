#include <iostream>
#include <vector>
using namespace std;

//making page class
class Page{
    private: 
    string url;
    string id;
    vector<int> outLinks{};
    
    public:

    //initializing properties of an object of Page class
    void getdata(string address, string idNo, vector<int> arr){
        url = address;
        id = idNo;
        for(int i=0; i<arr.size(); i++){
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
        for(int i=0; i<arr.size(); i++){
            outLinks.push_back(arr[i]);
        }
    }

    //data printing function of the Page class
    void printPage(){
        cout << "URL of the page is : " << url << endl;
        cout << "Id of the page is : " << id << endl;
        cout << "Out Links from the page is : ";
        for(int i=0; i<outLinks.size(); i++){
            cout << outLinks[i] << " ";
        }
        cout << endl;
    }
};