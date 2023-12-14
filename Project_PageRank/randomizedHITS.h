#ifndef RANDOMIZEDHITS_H
#define RANDOMIZEDHITS_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define eps 10e-8
#include "graph.h"
using namespace std;

double generalMatrixRHITS[1000][1000];

double authorityMatrixRHITS[1000][1000];
double hubMatrixRHITS[1000][1000];

double finalRankValueRHITS[1000];
int finalRankIndexRHITS[1000];
int outLinkNumRHITS[1000];

double authority_valueRHITS[1000];
double hub_valueRHITS[1000];

double authority_weightRHITS[1000];
double hub_weightRHITS[1000];

const double factorRHITS = 0.85;


void printHubsValueRHITS(){
    cout << "Hub Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_valueRHITS[i] << endl;
    }
}

void printAuthorityValueRHITS(){
    cout << "Authority Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_valueRHITS[i] << endl;
    }
}

void printHubsWeightRHITS(){
    cout << "Hub Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_weightRHITS[i] << endl;
    }
}

void printAuthorityWeightRHITS(){
    cout << "Authority Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_weightRHITS[i] << endl;
    }
}

void printFinalRankingRHITS(){
    cout << "Final Ranking: " << endl;
    cout << "No\tIndex\tValue" << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << i+1 << "\t" << finalRankIndexRHITS[i]+1 << "\t" << finalRankValueRHITS[finalRankIndexRHITS[i]] << endl;
    }
}

/*-- niche multiline comment e thaka gula onno file e add kora lagbe --*/
/*graph.h e jokhon graph update hobe tokhon abar create matrix o kintu update hobe*/
/*emnvabe ekta function er moddhe onno function kemne use [ekta function onno function diye kmne manipulated hobe] hobe eta include korte hobe*/

/*
bool containsOrNot(vector<int> dNodes, int index){
    bool flag = false;
    for(int i=0; i<dNodes.size(); i++){
        if(index == dNodes.at(i)){
            flag = true;
        }
    }
    return flag;
}
*/


// Creating TRANSITION MATRIX FUNCTION with corresponding PROBABILITY
void creatematrixRHITS(){

    initialize();

    // initializing matrix with zero
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            generalMatrixRHITS[i][j] = 0;
        }
    }
    
    //updating probability of the graph according to outgoing links
    for(int i=0; i<webPages.size(); i++){
        // vector<int> outLinkDemo = webPages.at(i-1).getOutLinks();
        // double outLinkProbability = (double)1/outLinkDemo.size();
        // for(int j=1; j<=outLinkDemo.size(); j++){
        //     generalMatrixRHITS[i][outLinkDemo.at(j-1)] = outLinkProbability;
        // }

        vector<int> outLinkDemo = webPages.at(i).getOutLinksIndex(webPages);
        //double outLinkProbability = (double)1/outLinkDemo.size();
        //outLinkNumRHITS[i+1] = outLinkDemo.size();
        for(int j=0; j<outLinkDemo.size(); j++){
            generalMatrixRHITS[i][outLinkDemo.at(j)-1] = 1;
        }
    }
}


void initialize_authority_hubRHITS(){
    for(int i=0; i<webPages.size(); i++){
        authority_valueRHITS[i] = 1.00;
        hub_valueRHITS[i] = 1.00;
    }
}

void initialize_authority_hub_weightRHITS(){
    for(int i=0; i<webPages.size(); i++){
        int num1 = 0;
        for(int j=0; j<webPages.size(); j++){
            num1 += generalMatrixRHITS[i][j];
        }
        hub_weightRHITS[i] = (double) num1/webPages.size();
        authority_weightRHITS[i] = (double)1-hub_weightRHITS[i];
    }
}

void authority_hub_MatrixCreationRHITS(){
    double e[webPages.size()][webPages.size()];

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            e[i][j] = (double)(1-factorRHITS)/webPages.size();
        }
    }

    double authTemp[webPages.size()][webPages.size()];
    double hubTemp[webPages.size()][webPages.size()];

    double tGM[webPages.size()][webPages.size()];

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            tGM[i][j] = generalMatrixRHITS[j][i];
        }
    }
    
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            double sum =0;
            for(int k=0; k<webPages.size(); k++){
                sum += tGM[i][k]*generalMatrixRHITS[k][j];
            }
            authTemp[i][j] = sum;
        }
    }

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            double sum =0;
            for(int k=0; k<webPages.size(); k++){
                sum += generalMatrixRHITS[i][k]*tGM[k][j];
            }
            hubTemp[i][j] = sum;
        }
    }

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            authorityMatrixRHITS[i][j] = factorRHITS*authTemp[i][j] + e[i][j];
            hubMatrixRHITS[i][j] = factorRHITS*hubTemp[i][j] + e[i][j];
        }
    }

//priniting authority and hub matrix
/*    cout << "Authority Matrix: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            cout << authTemp[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Hub Matrix: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            cout << hubTemp[i][j] << " ";
        }
        cout << endl;
    }
*/

}

bool convergeRHITS(double temp_authority_value[], double temp_hub_value[], double authority_valueRHITS[], double hub_valueRHITS[]){
    bool flag = true;
    for(int i=0; i<webPages.size(); i++){
        if(fabs(temp_authority_value[i]-authority_valueRHITS[i]) > eps){
            flag = false;
        }
        if(fabs(temp_hub_value[i]-hub_valueRHITS[i]) > eps){
            flag = false;
        }
    }
    return flag;
}

void normalizeRHITS(){
    double sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += authority_valueRHITS[i]*authority_valueRHITS[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        authority_valueRHITS[i] = authority_valueRHITS[i]/sum;
    }

    sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += hub_valueRHITS[i]*hub_valueRHITS[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        hub_valueRHITS[i] = hub_valueRHITS[i]/sum;
    }
}

void finalRankingRHITS(){
    for(int i=0; i<webPages.size(); i++){
        finalRankValueRHITS[i] = ((authority_weightRHITS[i]*authority_valueRHITS[i]) + (hub_valueRHITS[i]*hub_weightRHITS[i]));
    }

    double demoFinalRankValue[webPages.size()];
    for(int i=0; i<webPages.size(); i++){
        demoFinalRankValue[i] = finalRankValueRHITS[i];
    }

    //giving final rank index
    for(int i=0; i<webPages.size(); i++){
        int max = 0;
        for(int j=0; j<webPages.size(); j++){
            if(demoFinalRankValue[j] > demoFinalRankValue[max]){
                max = j;
            }
        }
        finalRankIndexRHITS[i] = max;
        demoFinalRankValue[max] = -1;
    }
}


void randomizedHitsAlgorithm(){
    creatematrixRHITS();
    initialize_authority_hubRHITS();
    initialize_authority_hub_weightRHITS();
    authority_hub_MatrixCreationRHITS();

    double temp_authority_value[webPages.size()];
    double temp_hub_value[webPages.size()];

    int i=0;

    while(1){
        for(int i=0; i<webPages.size(); i++){
            temp_authority_value[i] = authority_valueRHITS[i];
            temp_hub_value[i] = hub_valueRHITS[i];
        }

        for(int i=0; i<webPages.size(); i++){
            double sumAuth = 0;
            double sumHub = 0;
            for(int j=0; j<webPages.size(); j++){
                sumAuth += authorityMatrixRHITS[j][i]*temp_authority_value[j];
                sumHub += hubMatrixRHITS[j][i]*temp_hub_value[j];
            }
            authority_valueRHITS[i] = sumAuth*authority_weightRHITS[i];
            hub_valueRHITS[i] = sumHub*hub_weightRHITS[i];
        }

        normalizeRHITS();

        if(convergeRHITS(temp_authority_value, temp_hub_value, authority_valueRHITS, hub_valueRHITS)){
            cout << "Final Hub And Authority Value:" << endl;
            //printHubsValueRHITS();
            //printAuthorityValueRHITS();
            finalRankingRHITS();
            printFinalRankingRHITS();
            break;
        }

        i++;

    }
}


/*
int main(){

    randomizedHitsAlgorithm();

    //printHubsValueRHITS();
    //printAuthorityValueRHITS();  
    //printHubsWeightRHITS();
    //printAuthorityWeightRHITS();

    //initialize_authority_hubRHITS();
    //printHubsValueRHITS();
    //printAuthorityValueRHITS(); 

   // initialize_authority_hub_weightRHITS();

    //authority_hub_MatrixCreationRHITS();

    return 0;
}
*/

#endif