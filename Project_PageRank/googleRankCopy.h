#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"
using namespace std;

double generalMatrix[100][100];
double googleMatrix[100][100];
double pageRankProbability[100];
int finalRankIndex[100];

/*-- niche multiline comment e thaka gula onno file e add kora lagbe --*/
/*graph.h e jokhon graph update hobe tokhon abar create matrix o kintu update hobe*/
/*emnvabe ekta function er moddhe onno function kemne use [ekta function onno function diye kmne manipulated hobe] hobe eta include korte hobe*/



bool containsOrNot(vector<int> dNodes, int index){
    bool flag = false;
    for(int i=0; i<dNodes.size(); i++){
        if(index == dNodes.at(i)){
            flag = true;
        }
    }
    return flag;
}


// Creating TRANSITION MATRIX FUNCTION with corresponding PROBABILITY
void creatematrix(){

    updateGraph();

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


// Page Rank initialize Function
void initializePageRank(){
    for(int i=1; i<=webPages.size(); i++){
        pageRankProbability[i] = (double)1/webPages.size();
    }
}


void googleTransformation(){

    creatematrix();

    int eMatrix[webPages.size()+1][1], etMatrix[1][webPages.size()+1];
    int aMatrix[webPages.size()+1][1];
    double teleportMatrix[webPages.size()+1][webPages.size()+1];
    double scholasticMatrix[webPages.size()+1][webPages.size()+1];
    double df;

    cout << "Enter The DAMPING FACTOR (between 0 to 1): ";
    cin >> df;
    cout << endl;


    //initializing eMatrix & etMatrix
    for(int i=1; i<=webPages.size(); i++){
        eMatrix[i][0] = 1;
        etMatrix[0][i] = 1;
    }
    // // printing eMatrix and etMatrix in test perpose
    // for(int i=1; i<=webPages.size(); i++){
    //     cout << eMatrix[i][0] << " ";
    // }
    // cout << endl;
    // for(int i=1; i<=webPages.size(); i++){
    //     cout << etMatrix[0][i] << " ";
    // }


    // initializing binary dangling node factor (a) matrix
    vector<int> dNodes = danglingNodes();
    // // printing dNodes in test perpose
    // for(int i=0; i<dNodes.size(); i++){
    //     cout << dNodes.at(i) << " ";
    // }

    for(int i=1; i<=webPages.size(); i++){
        if(containsOrNot(dNodes, i)){
            aMatrix[i][0] = 1;
        }else{
            aMatrix[i][0] = 0;
        }
    }
    // // printing aMatrix in test perpose
    // for(int i=1; i<=webPages.size(); i++){
    //     cout << aMatrix[i][0] << " ";
    // }
    // cout << endl;
    // cout << endl;


    // initializing Teleportation Matrix, E = (e.et)/n
    for(int i=1; i<=webPages.size(); i++){
        double x = (double)1/webPages.size();
        for(int j=1; j<=webPages.size(); j++){
            teleportMatrix[i][j] = x*eMatrix[j][0]*etMatrix[0][j];
        }
    }
    // // printing Teleportation Matrix in test perpose
    // for(int i=1; i<=webPages.size(); i++){
    //     for(int j=1; j<=webPages.size(); j++){
    //         cout << teleportMatrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // initializing Scholstic Matrix, S = H + a(et/n)
    for(int i=1; i<=webPages.size(); i++){
        double x = (double)1/webPages.size();
        for(int j=1; j<=webPages.size(); j++){
            scholasticMatrix[j][i] = generalMatrix[j][i] + ((double)aMatrix[j][0]*x*etMatrix[0][j]);
        }
    }
    // // printing Scholastic Matrix in test perpose
    // for(int i=1; i<=webPages.size(); i++){
    //     for(int j=1; j<=webPages.size(); j++){
    //         printf("%7.5lf  ", scholasticMatrix[i][j]);
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // initializing GOOGLE Matrix G, = alpha*S + (1-alpha)*E
    for(int i=1; i<=webPages.size(); i++){
        for(int j=1; j<=webPages.size(); j++){
            googleMatrix[i][j] = (df*scholasticMatrix[i][j]) + ((1-df)*teleportMatrix[i][j]);
        }
    }
    // // printing GOOGLE Matrix in test perpose
    // for(int i=1; i<=webPages.size(); i++){
    //     for(int j=1; j<=webPages.size(); j++){
    //         printf("%7.5lf  ", googleMatrix[i][j]);
    //     }
    //     cout << endl;
    // }

}


// GOOGLE matrix printing Function
void printGOOGLEMatrix(){
    cout << "GOOGLE Matrix: " << endl;
    for(int i=1; i<=webPages.size(); i++){
        for(int j=1; j<=webPages.size(); j++){
            printf("%7.5lf  ", googleMatrix[i][j]);
        }
        cout << endl;
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


// Page rank probability printing function
void printPageRankProbability(double pageProbability[]){
    cout << "Page Rank Probability : ";
    for(int i=1; i<=webPages.size(); i++){
        printf("%7.6lf  ", pageProbability[i]);
    }
    cout << endl;
}


// FINAL PAGERANK PROBABILITY TO DEMONSTRATE THE FINAL RANKING OF THE PAGES
void finalRankOfPages(){
    double demo[webPages.size()+1];
    for(int i=1; i<=webPages.size(); i++){
        demo[i] = pageRankProbability[i];
        // cout << demo[i] << endl;
    }

    for(int i=1; i<=webPages.size(); i++){
        int max = i;
        for(int j=1; j<=webPages.size(); j++){
            if(demo[max]<demo[j]){
                max = j;
            }
        }
        // cout << max << endl;
        finalRankIndex[i] = max;
        demo[max] = -1;
    }

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
void pageIterationPrintable(){       

    initializePageRank();
    googleTransformation();     // page iteration diye amra pageRank ber korbo. page rank amra generalMatrix noy borong googleMatrix diye ber korbo. tai age googleTransformation() function diye googleMatrix initialize kore nite hobe.

    double demoPageProbability[webPages.size()+1];
    int i = 0;

    while(1){
        for(int i=1; i<=webPages.size(); i++){
            demoPageProbability[i] = pageRankProbability[i];
        }

        for(int j=1; j<=webPages.size(); j++){
            double demo = 0;
            for(int k=1; k<=webPages.size(); k++){
                demo += pageRankProbability[k]*googleMatrix[k][j];
            }
            pageRankProbability[j] = demo;
        }

        if(isConverge(demoPageProbability)){
            cout << "Final Page Rank - " << endl;
            printPageRankProbability(pageRankProbability);
            cout << endl << endl;
            break;
        }

        cout << "PageRank after " << ++i << " iteration -" << endl;
        printPageRankProbability(pageRankProbability);
        cout << endl;
    }
}

void pageIteration(){       

    initializePageRank();
    googleTransformation();     // page iteration diye amra pageRank ber korbo. page rank amra generalMatrix noy borong googleMatrix diye ber korbo. tai age googleTransformation() function diye googleMatrix initialize kore nite hobe.

    double demoPageProbability[webPages.size()+1];
    int i = 0;

    while(1){
        for(int i=1; i<=webPages.size(); i++){
            demoPageProbability[i] = pageRankProbability[i];
        }

        for(int j=1; j<=webPages.size(); j++){
            double demo = 0;
            for(int k=1; k<=webPages.size(); k++){
                demo += pageRankProbability[k]*googleMatrix[k][j];
            }
            pageRankProbability[j] = demo;
        }

        if(isConverge(demoPageProbability)){
            // cout << "Final Page Rank - " << endl;
            // printPageRankProbability(pageRankProbability);
            // cout << endl << endl;
            break;
        }
    }

    finalRankOfPages();
}


void printFinalRank(){
    pageIteration();
    cout << "\tRank\tIndex\tProbability" << endl;
    for(int i=1; i<=webPages.size(); i++){
        cout << "\t" << i << "\t" << finalRankIndex[i] << "\t" << pageRankProbability[finalRankIndex[i]] << "\n";
    }
    cout << endl;
}



// // MAIN FUNCTION
// int main (void){

// /* googleRank.h test starts */

    // initialLoad();

    // creatematrix();
    
    // initializePageRank();

    // printTransitionMatrix();
    // cout << endl;

    // // // to see google matrix, we have to call "googleTransformation()" function here. Otherwise without calling "pageIteration()" function we won't be able to see googleMatrix. Because only called "googleTransformation()" function inside "pageIteration()" function.
    // // googleTransformation();
    // // printGOOGLEMatrix(); 
    // // cout << endl;

    // printPageRankProbability(pageRankProbability);
    // cout << endl;

    // pageIteration();    // googleTransformation() function is calling here

    // // printPageRankProbability(pageRankProbability);
    // // cout << endl;


    // finalRankOfPages();

    // printFinalRank();


// /* googleRank.h test ends */

// }