#include <bits/stdc++.h>
#include "pageCopy.h"
using namespace std;

vector<string> urlList{};
vector<Page> webPages{};


int getIndexbyURL(string URL){
    for(int i=0; i<urlList.size(); i++){
        if(urlList.at(i) == URL){
            return i;
        }
    }
    return -1;
}


bool hasPage(string URL){
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).getName() == URL){
            return true;
        }
    }
    return false;
}


void createNewNode(string URL, string mustContain){
    if(urlList.size() > 250 || hasPage(URL)){
        return;
    }

    cout << "Creating new node for " << URL << endl;

    vector<string> outLinks = listOfOutgoingURLs(URL, mustContain);
    Page tempPage;
    tempPage.initializeData(URL, getIndexbyURL(URL), outLinks);
    webPages.push_back(tempPage);



    for(int i=0; i<outLinks.size(); i++){
        if(getIndexbyURL(outLinks.at(i)) == -1){
            urlList.push_back(outLinks.at(i));
            createNewNode(outLinks.at(i), mustContain);
        }
    }
}


void initialize(){
    string targetURL; 
    string mustContain;

    cout << "Enter Target URL : " ;     // https://www.du.ac.bd/
    cin >> targetURL;
    cout << "Must contain : ";          // du.ac.bd
    cin >> mustContain;

    urlList.push_back(targetURL);

    createNewNode(targetURL, mustContain);
   
}


Page findPagebyURL(string URL){
    for(int i=0; i<webPages.size(); i++){
        if(webPages.at(i).getName() == URL){
            return webPages.at(i);
        }
    }

    cout << "No page found with this URL." << endl;
    Page tempPage;
    return tempPage;
}


void printPagebyURL(string URL){
    Page tempPage = findPagebyURL(URL);
    tempPage.printPage();
}


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


void printDanglingPages(){
    vector<Page> dPages = danglingPages();
    if(dPages.size()==0){
        cout << "There is no dangling nodes in this graph.";
    }else{
        cout << "Dangling Pages are -\n\n";
        for(int i=0; i<dPages.size(); i++){
            dPages.at(i).printPage();
            cout << endl;
        }
    }
}


int main(){
    initialize();
    for(int i=0; i<webPages.size(); i++){
        webPages.at(i).printPage();
    }

    printDanglingPages();
}