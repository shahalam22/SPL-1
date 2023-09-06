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
    webPages.clear();
    for(int i=0; i<urlList.size(); i++){
        Page tempPage;
        tempPage.initializeData(urlList.at(i), idList.at(i), indexList.at(i), inLinkVector.at(i), outLinkVector.at(i));
        webPages.push_back(tempPage);
    }
}


// // ADDNEW WEBPAGE FUNCTION
// void addNewPage(string address, string idNo, int indexNO, vector<int> in, vector<int> out){
//     //updating general values
//     Page tempPage;
//     tempPage.initializeData(address, idNo, indexNO, in, out);
//     webPages.push_back(tempPage);
//     urlList.push_back(address);
//     idList.push_back(idNo);
//     indexList.push_back(indexNO);
// }


// ADDING NEW PAGE FUNCTION
void addNewPage(){
    // Taking user input
    string newURL;
    string newId;
    int noOfInlinks, noOfOutlinks;
    vector<int> newInLinks{};
    vector<int> newOutLinks{};

    cout << "Enter URL of the new page - ";
    cin >> newURL;
    cout << "Enter ID of the new page - ";
    cin >> newId;
    cout << "Enter number of InLinks - ";
    cin >> noOfInlinks;
    cout << "Enter inlink nodes index - ";
    for(int i=0; i<noOfInlinks; i++){
        int a;
        cin >> a;
        newInLinks.push_back(a);
    }
    cout << "Enter number of OutLinks - ";
    cin >> noOfOutlinks;
    cout << "Enter outlink nodes index - ";
    for(int i=0; i<noOfOutlinks; i++){
        int a;
        cin >> a;
        newOutLinks.push_back(a);
    }

    //updating general values
    urlList.push_back(newURL);
    idList.push_back(newId);
    indexList.push_back(webPages.size()+1);
    inLinkVector.push_back(newInLinks);
    outLinkVector.push_back(newOutLinks);

    // Page tempPage;
    // tempPage.initializeData(newURL, newId, webPages.size()+1, newInLinks, newOutLinks);
    // webPages.push_back(tempPage);
    updateGraph();


    cout << endl;
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
vector<Page> danglingPages(){
    vector<Page> Dpages{};
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).isDangling()){
            Dpages.push_back(webPages.at(i));
        }
    }
    return Dpages;
}

vector<int> danglingNodes(){
    vector<Page> dPages = danglingPages();
    vector<int> dNodes{};
    for(int i=0; i<dPages.size(); i++){
        dNodes.push_back(dPages.at(i).getIndex());
    }
    return dNodes;
}

void printDanglingNodes(){
    vector<Page> dPages = danglingPages();
    if(dPages.size()==0){
        cout << "There is no dangling nodes in this graph.";
    }else{
        cout << "Dangling Nodes are -\n\n";
        for(int i=0; i<dPages.size(); i++){
            dPages.at(i).printPage();
            cout << endl;
        }
    }
}


// PRINTING ALL THE WEBPAGES IN THE GRAPH
void printAllPagesDetails(){
    cout << "All the webpages from this graph - " << endl;
    for(int i=0; i<urlList.size(); i++){
        webPages[i].printPage();
    }
}



// // MAIN FUNCTION
// int main (void){

/* graph.h test starts */

    // initialLoad();
    

    // // test print of URL, ID, MATRIX vectors
    // cout << "URL's of Webpages : " << endl;
    // for(int i=0; i<urlList.size(); i++){
    //     cout << "Webpage URL of " << i+1 << " (index) page is - ";
    //     cout << urlList[i] << endl;
    // }
    // cout << endl;

    // cout << "Id's of Webpages : " << endl;
    // for(int i=0; i<idList.size(); i++){
    //     cout << "Webpage id of " << i+1 << " (index) page is - ";
    //     cout << idList[i] << endl;
    // }
    // cout << endl;

    // cout << "InLinks for the Webpages : " << endl;
    // for(int i=0; i<inLinkVector.size(); i++){
    //     cout << "InLinks of " << i+1 << " (index) page - ";
    //     for(int j=0; j<inLinkVector.at(i).size(); j++){
    //         cout << inLinkVector.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // cout << "InLinks for the Webpages : " << endl;
    // for(int i=0; i<outLinkVector.size(); i++){
    //     cout << "InLinks of " << i+1 << " (index) page - ";
    //     for(int j=0; j<outLinkVector.at(i).size(); j++){
    //         cout << outLinkVector.at(i).at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // // //adding new nodes in the graph
    // // vector<int> newInLink1{3,5};
    // // vector<int> newOutLink1{2,3,6};
    // // addNewPage("http://www.sample.org/sleep.html", "o4Uypq", webPages.size()+1, newInLink1, newOutLink1);
    // addNewPage();

    // // vector<int> newInLink2{3,4,7};
    // // vector<int> newOutLink2{2,3,5};
    // // addNewPage("http://www.sample.org/eating.html", "0OF3nS", webPages.size()+1, newInLink2, newOutLink2);
    // addNewPage();

    // //printing web pages
    // // cout << "After adding new values - " << endl;
    // printAllPagesDetails();


    // // printing neighbour pages function test
    // // webPages.at(2).Neighbours(webPages);
    // // webPages.at(3).Neighbours(webPages);
    // cout << "Enter the index of the page: ";
    // int indexForNeighbour;
    // cin >> indexForNeighbour;
    // webPages.at(indexForNeighbour-1).Neighbours(webPages);


    // // // validSite() function test
    // // findByUrl("http://www.sample.edu/plate");
    // // findByUrl("habijabi");

    // // FIND VALIDITY BY URL
    // cout << "Enter the URL of the page : ";
    // string urlToFindPage;
    // cin >> urlToFindPage;
    // findByUrl(urlToFindPage);
    // // FIND VALIDITY BY ID
    // cout << "Enter the ID of the page : ";
    // string idToFindPage;
    // cin >> idToFindPage;
    // findByUrl(idToFindPage);


    // //adding new Dangling Node
    // vector<int> newInLink1{3,5};
    // vector<int> newOutLink1{};
    // addNewPage("http://www.sample.org/sleep.html", "o4Uypq", webPages.size(), newInLink1, newOutLink1);
    // addNewPage();

    // printAllPagesDetails();


    // // printing dangling nodes
    // vector<Page> Dpages = danglingPages();
    // if(Dpages.size()==0){
    //     cout << "No dangling node in this graph" << endl;
    // }else{
    //     cout << "\nDangling Nodes are : \n";
    //     for(int i=0; i<Dpages.size(); i++){
    //         Dpages.at(i).printPage();
    //     }
    // }


// /* graph.h test ends */


// }