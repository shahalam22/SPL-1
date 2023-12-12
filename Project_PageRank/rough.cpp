#include <iostream>
#include <fstream>
#include <string>
#define eps 10e-8
#include "graphCopy.h"
using namespace std;

double generalMatrix[6][6] = {{0, 0.5, 0.5, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0},
                              {0.33, 0.33, 0, 0, 0.33, 0},
                              {0, 0, 0, 0, 0.5, 0.5},
                              {0, 0, 0, 0.5, 0, 0.5},
                              {0, 0, 0, 1, 0, 0}};
double googleMatrix[1000][1000];
double pageRankProbability[1000];
int finalRankIndex[1000];
int outLinkNum[1000];

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
/*
void creatematrix(){

    initialize();

    // initializing matrix with zero
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            generalMatrix[i][j] = 0;
        }
    }
    
    //updating probability of the graph according to outgoing links
    for(int i=0; i<6; i++){
        // vector<int> outLinkDemo = webPages.at(i-1).getOutLinks();
        // double outLinkProbability = (double)1/outLinkDemo.size();
        // for(int j=1; j<=outLinkDemo.size(); j++){
        //     generalMatrix[i][outLinkDemo.at(j-1)] = outLinkProbability;
        // }

        vector<int> outLinkDemo = webPages.at(i).getOutLinksIndex(webPages);
        double outLinkProbability = (double)1/outLinkDemo.size();
        outLinkNum[i] = outLinkDemo.size();
        for(int j=0; j<outLinkDemo.size(); j++){
            generalMatrix[i][outLinkDemo.at(j)-1] = outLinkProbability;
        }
    }
}
*/


// Page Rank initialize Function
void initializePageRank(){
    for(int i=0; i<6; i++){
        pageRankProbability[i] = (double)1/6;
    }
}


void googleTransformation(){

    //  creatematrix();

    int eMatrix[6][1], etMatrix[1][6];
    int aMatrix[6][1];
    double teleportMatrix[6][6];
    double scholasticMatrix[6][6];
    double df;

    cout << "Enter The DAMPING FACTOR (between 0 to 1): ";
    cin >> df;
    cout << endl;


    //initializing eMatrix & etMatrix
    for(int i=0; i<6; i++){
        eMatrix[i][0] = 1;
        etMatrix[0][i] = 1;
    }
    // printing eMatrix and etMatrix in test perpose
     cout << "eMatrix: " << endl;
     for(int i=0; i<6; i++){
         cout << eMatrix[i][0] << " ";
     }
     cout << endl;
     cout << "etMatrix: " << endl;
     for(int i=0; i<6; i++){
         cout << etMatrix[0][i] << " ";
     }
     cout << endl;
    

    // initializing binary dangling node factor (a) matrix
    vector<int> dNodes;
    dNodes.push_back(1);
    // printing dNodes in test perpose
     
     cout << "Dangling Node: " << endl;
     for(int i=0; i<dNodes.size(); i++){
         cout << dNodes.at(i) << " ";
     }
     cout << endl;
    

    for(int i=0; i<6; i++){
        if(containsOrNot(dNodes, i)){
            aMatrix[i][0] = 1;
        }else{
            aMatrix[i][0] = 0;
        }
    }
    // printing aMatrix in test perpose
     
     cout << "aMatrix: " << endl;
     for(int i=0; i<6; i++){
         cout << aMatrix[i][0] << " ";
     }
     cout << endl;
     cout << endl;
    

    // initializing Teleportation Matrix, E = (e.et)/n
    for(int i=0; i<6; i++){
        double x = (double)1/6;
        for(int j=0; j<6; j++){
            teleportMatrix[i][j] = x*eMatrix[j][0]*etMatrix[0][j];
        }
    }
     // printing Teleportation Matrix in test perpose
     
     cout << "Teleportation Matrix: " << endl;
     for(int i=0; i<6; i++){
         for(int j=0; j<6; j++){
             cout << teleportMatrix[i][j] << " ";
         }
         cout << endl;
     }
     cout << endl;
     


    // initializing Scholstic Matrix, S = H + a(et/n)
    for(int i=0; i<6; i++){
        double x = (double)1/6;
        for(int j=0; j<6; j++){
            scholasticMatrix[j][i] = generalMatrix[j][i] + ((double)aMatrix[j][0]*x*etMatrix[0][j]);
        }
    }
     // printing Scholastic Matrix in test perpose
     
     cout << "Scholastic Matrix: " << endl;
     for(int i=0; i<6; i++){
         for(int j=0; j<6; j++){
             printf("%7.5lf  ", scholasticMatrix[i][j]);
         }
         cout << endl;
     }
     cout << endl;
     

    // initializing GOOGLE Matrix G, = alpha*S + (1-alpha)*E
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            googleMatrix[i][j] = (df*scholasticMatrix[i][j]) + ((1-df)*teleportMatrix[i][j]);
        }
    }
    // // printing GOOGLE Matrix in test perpose
    // for(int i=1; i<=6; i++){
    //     for(int j=1; j<=6; j++){
    //         printf("%7.5lf  ", googleMatrix[i][j]);
    //     }
    //     cout << endl;
    // }

}


// GOOGLE matrix printing Function
void printGOOGLEMatrix(){
    cout << "GOOGLE Matrix: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%12.5lf", googleMatrix[i][j]);
        }
        cout << endl;
    }
}


// Transition matrix printing Function
void printTransitionMatrix(){
    cout << "Transition Matrix: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            // cout << generalMatrix[i][j] << "\t";
            printf("%12.5lf", generalMatrix[i][j]);
        }
        cout << endl;
    }
}


// Page rank probability printing function
void printPageRankProbability(double pageProbability[]){
    cout << "Page Rank Probability : ";
    for(int i=0; i<6; i++){
        printf("%7.6lf  ", pageProbability[i]);
    }
    cout << endl;
}


// FINAL PAGERANK PROBABILITY TO DEMONSTRATE THE FINAL RANKING OF THE PAGES
void finalRankOfPages(){
    double demo[6];
    for(int i=0; i<6; i++){
        demo[i] = pageRankProbability[i];
        // cout << demo[i] << endl;
    }

    for(int i=0; i<6; i++){
        int max = i;
        for(int j=0; j<6; j++){
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
    for(int i=0; i<6; i++){
        if(demoPageProbability[i]-pageRankProbability[i] > eps){
        //if(demoPageProbability[i]!=pageRankProbability[i]){
            flag = false;
        }
    }
    return flag;
}


// Page Rank matrix multiplication [without dangling node]
void pageIterationPrintable(){       

    googleTransformation();     // page iteration diye amra pageRank ber korbo. page rank amra generalMatrix noy borong googleMatrix diye ber korbo. tai age googleTransformation() function diye googleMatrix initialize kore nite hobe.
    initializePageRank();

    /*printTransitionMatrix();
    cout << endl << endl;
    printGOOGLEMatrix();*/

    double demoPageProbability[6];
    //double tempProb[6];
    int i = 0;

    while(1){

        for(int j=0; j<6; j++){
            //cout << pageRankProbability[j] << " ";
            demoPageProbability[j] = pageRankProbability[j];
        }

        for(int j=0; j<6; j++){
            double demo = 0;
            for(int k=0; k<6; k++){
                demo += demoPageProbability[k]*googleMatrix[k][j];
            }
            pageRankProbability[j] = demo;
        }

        double sum = 0;

        for(int j=0; j<6; j++){
            sum += pageRankProbability[j];
        }

        for(int j=0; j<6; j++){
            pageRankProbability[j] = (double) pageRankProbability[j]/sum;
        }

        if(isConverge(demoPageProbability)){
            cout << "Final Page Rank - " << endl;
            printPageRankProbability(pageRankProbability);
            cout << endl << endl;
            break;
        }

    /*    cout << "Demo PageRank after " << ++i << " iteration -" << endl;
        printPageRankProbability(demoPageProbability);
        cout << endl << endl;
    */
        cout << "PageRank after " << ++i << " iteration -" << endl;
        printPageRankProbability(pageRankProbability);
        cout << endl << endl << endl;
    }
    
}

void pageIteration(){       

    googleTransformation();     // page iteration diye amra pageRank ber korbo. page rank amra generalMatrix noy borong googleMatrix diye ber korbo. tai age googleTransformation() function diye googleMatrix initialize kore nite hobe.
    initializePageRank();

    double demoPageProbability[6];
    int i = 0;

    while(1){
        for(int i=0; i<6; i++){
            demoPageProbability[i] = pageRankProbability[i];
        }

        for(int j=0; j<6; j++){
            double demo = 0;
            for(int k=0; k<6; k++){
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
    for(int i=1; i<=6; i++){
        cout << "\t" << i << "\t" << finalRankIndex[i] << "\t" << pageRankProbability[finalRankIndex[i]] << "\n";
    }
    cout << endl;
}



int main(){
    /* creatematrix();

     for(int i=0; i<6; i++){
         cout << outLinkNum[i] << "\t\t";
         for(int j=0; j<6; j++){
             printf("%12.5lf", generalMatrix[i][j]);
         }
         cout << endl << endl;
     }
    */
    
    // printFinalRank();

    // googleTransformation();

    // printGOOGLEMatrix();

    // creatematrix();

    // initializePageRank();
    // printPageRankProbability(pageRankProbability);

     pageIterationPrintable();

}