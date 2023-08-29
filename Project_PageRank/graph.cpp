#include <iostream>
#include <fstream>
#include "page.h"
using namespace std;


//creating relevent vectors
vector<vector<int>> matrix{};
vector<string> url{};
vector<string> id{};
//creating webpages
vector<Page> webPages{};


// ADDNEW WEBPAGE FUNCTION
void addNewPage(string address, string idNo, vector<int> inLinks, vector<int> outLinks){
    //updating general values
    url.push_back(address);
    id.push_back(idNo);
    for(int i=0; i<matrix.size(); i++){
        matrix.at(i).push_back(inLinks[i]);
        webPages.at(i).updateOutLinks(matrix.at(i));
    }
    matrix.push_back(outLinks);
    
    //creating new node and merging with "webPages" vector
    Page tempPage;
    tempPage.getdata(address, idNo, outLinks);
    webPages.push_back(tempPage);
}


// VALID SITE FUNCTION - is a function exists in the graph or not
void validSite(string address){
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


// MAIN FUNCTION
int main (void){    
    int n = 6;
    // cout << "Enter the dimension of the matrix" << endl;
    // cin >> n;


    //initializing URL vector
    fstream urlFile;
    urlFile.open("url.txt");
    if(!urlFile){
        cout << "Such URL file doesn't exist!" << endl;
    }else{
        for(int i=0; i<n; i++){
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
        for(int i=0; i<n; i++){
            string tempId;
            idFile >> tempId;
            id.push_back(tempId);
        }
    }
    idFile.close();

    //initializing MATRIX vector
    fstream matrixFile;
    matrixFile.open("matrix.txt");
    if(!idFile){
        cout << "Such MATRIX file doesn't exist!" << endl;
    }else{
        for(int i=0; i<n; i++){
            vector<int> temp{};
            for(int j=0; j<n; j++){
                int k;
                matrixFile >> k;
                temp.push_back(k);
            }
            matrix.push_back(temp);
        }
    }
    matrixFile.close();


    // //test print of URL, ID, MATRIX vectors
    // for(int i=0; i<url.size(); i++){
    //     cout << url[i] << endl;
    // }
    // for(int i=0; i<id.size(); i++){
    //     cout << id[i] << endl;
    // }
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    //initializing properties of the webpage
    for(int i=0; i<url.size(); i++){
        Page tempPage;
        tempPage.getdata(url[i], id[i], matrix[i]);
        webPages.push_back(tempPage);
    }


    // //adding new nodes in the graph
    // vector<int> newInLink1 = {0,0,1,0,1,0,0};
    // vector<int> newOutLink1 = {0,1,1,0,0,0,1};
    // addNewPage("http://www.sample.org/sleep.html", "HgO8a4", newInLink1, newOutLink1);

    // vector<int> newInLink2 = {0,0,1,0,1,0,0,1};
    // vector<int> newOutLink2 = {0,1,1,0,0,0,1,0};
    // addNewPage("http://www.sample.org/eating.html", "Okiba4", newInLink2, newOutLink2);


    // //printing web pages
    // for(int i=0; i<url.size(); i++){
    //     webPages[i].printPage();
    //     cout << endl;
    // }

    // for(int i=0; i<matrix.size(); i++){
    //     for(int j=0; j<matrix.size(); j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // // printing neighbour pages function test
    // webPages.at(2).Neighbours("https://www.sample.info/", webPages, matrix);
    // webPages.at(3).Neighbours("http://www.sample.edu/plate" ,webPages, matrix);
    // webPages.at(4).Neighbours("http://sample.info/note.aspx" ,webPages, matrix);


    // // validSite() function test
    // validSite("http://www.sample.edu/plate");
    // validSite("habijabi");



}