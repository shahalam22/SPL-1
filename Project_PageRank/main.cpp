#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
using namespace std;


// MAIN FUNCTION
int main (void){

    initialLoad();

/* Point - 2 test starts */

    // // test print of URL, ID, MATRIX vectors
    // for(int i=0; i<urlList.size(); i++){
    //     cout << urlList[i] << endl;
    // }
    // for(int i=0; i<idList.size(); i++){
    //     cout << idList[i] << endl;
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
    // vector<int> newInLink1{3,5};
    // vector<int> newOutLink1{2,3,6};
    // addNewPage("http://www.sample.org/sleep.html", "o4Uypq", webPages.size(), newInLink1, newOutLink1);

    // vector<int> newInLink2{3,4,7};
    // vector<int> newOutLink2{2,3,5};
    // addNewPage("http://www.sample.org/eating.html", "0OF3nS", webPages.size(), newInLink2, newOutLink2);


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
    // vector<int> newInLink1{3,5};
    // vector<int> newOutLink1{};
    // addNewPage("http://www.sample.org/sleep.html", "o4Uypq", webPages.size(), newInLink1, newOutLink1);

    // printAllPagesDetails();

    // // printing dangling nodes
    // vector<Page> Dpages = danglingNodes();
    // if(Dpages.size()==0){
    //     cout << "No dangling node in this graph" << endl;
    // }else{
    //     cout << "\nDangling Nodes are : \n";
    //     for(int i=0; i<Dpages.size(); i++){
    //         Dpages.at(i).printPage();
    //     }
    // }


/* Point - 2 ends */

}