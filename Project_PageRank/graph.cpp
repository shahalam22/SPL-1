#include <iostream>
#include <fstream>
#include <string>
#include "page.h"
using namespace std;


//creating relevent vectors
vector<vector<int>> matrix{};
vector<string> url{};
vector<string> id{};
//creating webpages
vector<Page> webPages{};
vector<vector<string>> inLinkVector;
vector<vector<string>> outLinkVector;


// UPDATE GRAPH
void updateGraph(){
    for(int i=0; i<url.size(); i++){
        Page tempPage;
        tempPage.initializeData(url.at(i), id.at(i), inLinkVector.at(i), outLinkVector.at(i));
        webPages.push_back(tempPage);
    }
}


// ADDNEW WEBPAGE FUNCTION
void addNewPage(string address, string idNo, vector<string> in, vector<string> out){
    //updating general values
    Page tempPage;
    tempPage.initializeData(address, idNo, in, out);
    webPages.push_back(tempPage);
    url.push_back(address);
    id.push_back(idNo);
}


// GRAPH INITIALIZE FUNCTION
void initialLoad(){
    //initializing URL vector
    fstream urlFile;
    urlFile.open("url.txt");
    if(!urlFile){
        cout << "Such URL file doesn't exist!" << endl;
    }else{
        for(int i=0; !urlFile.eof(); i++){
            string tempUrl;
            urlFile >> tempUrl;
            url.push_back(tempUrl);
        }
    }
    urlFile.close();

    //initializing ID vector
    fstream idFile;
    idFile.open("id.txt");
    if(!idFile){
        cout << "Such ID file doesn't exist!" << endl;
    }else{
        for(int i=0; !idFile.eof(); i++){
            string tempId;
            idFile >> tempId;
            id.push_back(tempId);
        }
    }
    idFile.close();

    //initializing INLINKS vector
    fstream inlinkFile;
    inlinkFile.open("inLinks.txt");
    if(!inlinkFile){
        cout << "Such outlink vector file doesn't exist!" << endl;
    }else{
        for(int i=0; !inlinkFile.eof(); i++){
            vector<string> temp{};
            string x;
            std::getline(inlinkFile, x);
            for(char &c : x){
                if(c != ','){
                    string s;
                    s = c;
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
            vector<string> temp{};
            string x;
            std::getline(outLinkFile, x);
            for(char &c : x){
                if(c != ','){
                    string s;
                    s = c;
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

void findById(string id){
    int flag = -1;
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).getId() == id){
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
    for(int i=0; i<url.size(); i++){
        webPages[i].printPage();
        cout << endl;
    }
}


// MAIN FUNCTION
int main (void){    
    int n = 6;
    // cout << "Enter the dimension of the matrix" << endl;
    // cin >> n;

    initialLoad();

    // // test print of URL, ID, MATRIX vectors
    // for(int i=0; i<url.size(); i++){
    //     cout << url[i] << endl;
    // }
    // for(int i=0; i<id.size(); i++){
    //     cout << id[i] << endl;
    // }
    // for(int i=0; i<inLinkVector.size(); i++){
    //     for(int j=0; j<inLinkVector.at(i).size(); j++){
    //         cout << inLinkVector.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i=0; i<outLinkVector.size(); i++){
    //     for(int j=0; j<outLinkVector.at(i).size(); j++){
    //         cout << outLinkVector.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // //adding new nodes in the graph
    // vector<string> newInLink1{"3", "5"};
    // vector<string> newOutLink1{"2","3","6"};
    // addNewPage("http://www.sample.org/sleep.html", "7", newInLink1, newOutLink1);

    // vector<string> newInLink2{"3", "4", "7"};
    // vector<string> newOutLink2{"2", "3", "5"};
    // addNewPage("http://www.sample.org/eating.html", "8", newInLink2, newOutLink2);


    // //printing web pages
    // printAllPagesDetails();


    // // printing neighbour pages function test
    // webPages.at(2).Neighbours(webPages);
    // webPages.at(3).Neighbours(webPages);
    // webPages.at(4).Neighbours(webPages);


    // // validSite() function test
    // findByUrl("http://www.sample.edu/plate");
    // findByUrl("habijabi");


    // //adding new Dangling Node
    // vector<string> newInLink2{};
    // vector<string> newOutLink2{"3", "4", "7"};
    // addNewPage("http://www.sample.org/eating.html", "7", newInLink2, newOutLink2);

    // printAllPagesDetails();

    // // printing dangling nodes
    // cout << "\nDangling Nodes are : \n";
    // vector<Page> Dpages = danglingNodes();
    // for(int i=0; i<Dpages.size(); i++){
    //     Dpages.at(i).printPage();
    // }

}