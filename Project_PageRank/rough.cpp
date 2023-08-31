#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
using namespace std;

double generalMatrix[100][100];
double pageRankProbability[100];

/*-- niche multiline comment e thaka gula onno file e add kora lagbe --*/
/*graph.h e jokhon graph update hobe tokhin abar create matrix o kintu update hobe*/


// Creating TRANSITION MATRIX FUNCTION with corresponding PROBABILITY
void creatematrix(){
    // initializing matrix with zero
    for(int i=1; i<=webPages.size(); i++){
        for(int j=1; j<=webPages.size(); j++){
            generalMatrix[i][j] = 0;
        }
    }
    
    //updating probability of the graph according to outgoing links
    for(int i=1; i<=webPages.size(); i++){
        vector<int> outLinkDemo = webPages.at(i-1).getOutLinks();
        double outLinkProbability = (double)1/outLinkDemo.size();
        for(int j=1; j<=outLinkDemo.size(); j++){
            generalMatrix[i][outLinkDemo.at(j-1)] = outLinkProbability;
        }
    }
}


// Transition matrix printing Function
void printTransitionMatrix(){
    cout << "Transition Matrix: " << endl;
    for(int i=1; i<=webPages.size(); i++){
        for(int j=1; j<=webPages.size(); j++){
            // cout << generalMatrix[i][j] << "\t";
            printf("%7.2lf", generalMatrix[i][j]);
        }
        cout << endl;
    }
}


// Page Rank initialize Function
void initializePageRank(){
    for(int i=1; i<=webPages.size(); i++){
        pageRankProbability[i] = (double)1/webPages.size();
    }
}


// Page rank probability printing function
void printPageRankProbability(double pageProbability[]){
    cout << "Page Rank Probability : ";
    for(int i=1; i<=webPages.size(); i++){
        printf("%7.6lf  ", pageProbability[i]);
    }
    cout << endl;
}


// CONVERGE function
bool isConverge(double demoPageProbability[]){
    bool flag = true;
    for(int i=1; i<=webPages.size(); i++){
        if(demoPageProbability[i]!=pageRankProbability[i]){
            flag = false;
        }
    }
    return flag;
}


// Page Rank matrix multiplication [without dangling node]
void nonDanglingPageIteration(){

    double demoPageProbability[webPages.size()+1];

    while(!isConverge(demoPageProbability)){
        for(int i=1; i<=webPages.size(); i++){
            demoPageProbability[i] = pageRankProbability[i];
        }

        for(int j=1; j<=webPages.size(); j++){
            double demo = 0;
            for(int k=1; k<=webPages.size(); k++){
                // demo += generalMatrix[k][j]*pageRankProbability[k];
                demo += pageRankProbability[k]*generalMatrix[k][j];
            }
            pageRankProbability[j] = demo;
        }
    }
}


// MAIN FUNCTION
int main (void){

    initialLoad();

    creatematrix();

    printTransitionMatrix();

    initializePageRank();

    printPageRankProbability(pageRankProbability);

    nonDanglingPageIteration();

    printPageRankProbability(pageRankProbability);

}