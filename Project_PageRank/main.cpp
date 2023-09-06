#include <iostream>
#include <fstream>
#include <string>
#include "googleRank.h"
using namespace std;


int main(void){

    initialLoad();

    for(int u=1; ; u++){

        cout << "\n--- Google's PAGERANK algorithm implementation ---\n" << endl;
        cout << "1. View list of pages" << endl;
        cout << "2. Add new page" << endl;
        cout << "3. Find page by URL" << endl;
        cout << "4. Find page by ID" << endl;
        cout << "5. Find neighbours [outlinkd and inlinked pages] of a page" << endl;
        cout << "6. View Dangling Nodes" << endl;
        cout << "7. Goto PageRank Algorithm Functions" << endl;

        int a;
        cout << endl;
        cout << "Enter command: ";
        cin >> a;
        cout << endl;

        if(a==1){
            printAllPagesDetails();
            cout << endl;
        }else if(a==2){
            // //adding new nodes in the graph
            // vector<int> newInLink1{3,5};
            // vector<int> newOutLink1{2,3,6};
            // addNewPage("http://www.sample.org/sleep.html", "o4Uypq", webPages.size()+1, newInLink1, newOutLink1);
            addNewPage();
            cout << "\nPage added successfully" << endl;
            cout << endl;

            // vector<int> newInLink2{3,4,7};
            // vector<int> newOutLink2{2,3,5};
            // addNewPage("http://www.sample.org/eating.html", "0OF3nS", webPages.size()+1, newInLink2, newOutLink2);
            // addNewPage();
        }else if(a==3){
            // FIND VALIDITY BY URL
            cout << "Enter the URL of the page : ";
            string urlToFindPage;
            cin >> urlToFindPage;
            findByUrl(urlToFindPage);
        }else if(a==4){
            // FIND VALIDITY BY ID
            cout << "Enter the ID of the page : ";
            string idToFindPage;
            cin >> idToFindPage;
            findByUrl(idToFindPage);
            cout << endl;
        }else if(a==5){
            cout << "Enter the index of the page: ";
            int indexForNeighbour;
            cin >> indexForNeighbour;
            cout << endl;
            webPages.at(indexForNeighbour-1).Neighbours(webPages);
            cout << endl;
        }else if(a==6){
            printDanglingNodes();
        }else if(a==7){

            creatematrix();           
            initializePageRank();

            for(int y=0; ; y++){
                cout << "\n-- PAGERANK --\n" << endl;
                cout << "1. View initial matrix" << endl;
                cout << "2. View GOOGLE matrix" << endl;
                cout << "3. Demonstrate ranking probability" << endl;
                cout << "4. Final Rank of the pages" << endl;
                cout << "5. Exit" << endl;

                int b = 0;
                cout << endl;
                cout << "Enter command: ";
                cin >> b;
                cout << endl;

                if(b==1){
                    printTransitionMatrix();
                    cout << endl << endl;
                }else if(b==2){
                    googleTransformation();
                    printGOOGLEMatrix();
                    cout << endl << endl;
                }else if(b==3){
                    cout << "Initial Page Rank -";
                    printPageRankProbability(pageRankProbability);
                    cout << endl;
                    pageIterationPrintable();
                }else if(b==4){
                    printFinalRank();
                    cout << endl;
                }else if(b==5){
                    cout << "Exited Successfully." << endl;
                    cout << endl;
                    break;
                }else{
                    cout << "Command not found." << endl;
                    cout << endl;
                    break;
                }
            }
        }else{
            cout << "Command not found" << endl;
            cout << endl;
            break;
        }
    }

}