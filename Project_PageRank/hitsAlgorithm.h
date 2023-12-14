#ifndef HITSALGORITHM_H
#define HITSALGORITHM_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define eps 10e-8
#include "graph.h"
using namespace std;

double generalMatrixHITS[1000][1000];
double finalRankValueHITS[1000];
int finalRankIndexHITS[1000];
int outLinkNumHITS[1000];

double authority_valueHITS[1000];
double hub_valueHITS[1000];

double authority_weightHITS[1000];
double hub_weightHITS[1000];


void printHubsValueHITS(){
    cout << "Hub Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_valueHITS[i] << endl;
    }
}

void printAuthorityValueHITS(){
    cout << "Authority Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_valueHITS[i] << endl;
    }
}

void printHubsWeightHITS(){
    cout << "Hub Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_weightHITS[i] << endl;
    }
}

void printAuthorityWeightHITS(){
    cout << "Authority Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_weightHITS[i] << endl;
    }
}

void printFinalRankingHITS(){
    cout << "Final Ranking: " << endl;
    cout << "No\tIndex\tValue" << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << i+1 << "\t" << finalRankIndexHITS[i]+1 << "\t" << finalRankValueHITS[finalRankIndexHITS[i]] << endl;
    }
}

void printGeneralMatrixHITS(){
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            cout << generalMatrixHITS[i][j] << " ";
        }
        cout << endl;
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
void creatematrixHITS(){

    initialize();

    // initializing matrix with zero
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            generalMatrixHITS[i][j] = 0;
        }
    }
    
    //updating probability of the graph according to outgoing links
    for(int i=0; i<webPages.size(); i++){
        // vector<int> outLinkDemo = webPages.at(i-1).getOutLinks();
        // double outLinkProbability = (double)1/outLinkDemo.size();
        // for(int j=1; j<=outLinkDemo.size(); j++){
        //     generalMatrixHITS[i][outLinkDemo.at(j-1)] = outLinkProbability;
        // }

        vector<int> outLinkDemo = webPages.at(i).getOutLinksIndex(webPages);
        //double outLinkProbability = (double)1/outLinkDemo.size();
        //outLinkNumHITS[i+1] = outLinkDemo.size();
        for(int j=0; j<outLinkDemo.size(); j++){
            generalMatrixHITS[i][outLinkDemo.at(j)-1] = 1;
        }
    }
}

void initialize_authority_hubHITS(){
    for(int i=0; i<webPages.size(); i++){
        authority_valueHITS[i] = 1.00;
        hub_valueHITS[i] = 1.00;
    }
}

void initialize_authority_hub_weightHITS(){
    for(int i=0; i<webPages.size(); i++){
        int num1 = 0;
        for(int j=0; j<webPages.size(); j++){
            num1 += generalMatrixHITS[i][j];
        }
        hub_weightHITS[i] = (double) num1/webPages.size();
        authority_weightHITS[i] = (double)1-hub_weightHITS[i];
    }
}

bool convergeHITS(double temp_authority_value[], double temp_hub_value[], double authority_valueHITS[], double hub_valueHITS[]){
    bool flag = true;
    for(int i=0; i<webPages.size(); i++){
        if(fabs(temp_authority_value[i]-authority_valueHITS[i]) > eps){
            flag = false;
        }
        if(fabs(temp_hub_value[i]-hub_valueHITS[i]) > eps){
            flag = false;
        }
    }
    return flag;
}

void normalizeHITS(){
    double sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += authority_valueHITS[i]*authority_valueHITS[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        authority_valueHITS[i] = authority_valueHITS[i]/sum;
    }

    sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += hub_valueHITS[i]*hub_valueHITS[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        hub_valueHITS[i] = hub_valueHITS[i]/sum;
    }
}

void finalRankingHITS(){
    for(int i=0; i<webPages.size(); i++){
        finalRankValueHITS[i] = ((authority_weightHITS[i]*authority_valueHITS[i]) + (hub_valueHITS[i]*hub_weightHITS[i]));
    }

    double demoFinalRankValue[webPages.size()];
    for(int i=0; i<webPages.size(); i++){
        demoFinalRankValue[i] = finalRankValueHITS[i];
    }

    //giving final rank index
    for(int i=0; i<webPages.size(); i++){
        int max = 0;
        for(int j=0; j<webPages.size(); j++){
            if(demoFinalRankValue[j] > demoFinalRankValue[max]){
                max = j;
            }
        }
        finalRankIndexHITS[i] = max;
        demoFinalRankValue[max] = -1;
    }
}

void hitsAlgorithm(){

    creatematrixHITS();

    initialize_authority_hubHITS();
    initialize_authority_hub_weightHITS();

    double temp_authority_value[webPages.size()];
    double temp_hub_value[webPages.size()];

    int i=0;

    while(1){
        for(int i=0; i<webPages.size(); i++){
            temp_authority_value[i] = authority_valueHITS[i];
            temp_hub_value[i] = hub_valueHITS[i];
        }

        for(int i=0; i<webPages.size(); i++){     
            double sumAuth = 0;
            double sumHub = 0;
            for(int j=0; j<webPages.size(); j++){
                sumAuth += generalMatrixHITS[j][i]*hub_valueHITS[j];
                sumHub += generalMatrixHITS[i][j]*authority_valueHITS[j];
            }
            authority_valueHITS[i] = sumAuth*hub_weightHITS[i];
            hub_valueHITS[i] = sumHub*authority_weightHITS[i];
        }
        
        normalizeHITS();

        if(convergeHITS(temp_authority_value, temp_hub_value, authority_valueHITS, hub_valueHITS)){
            //cout << "Final Hub And Authority Value:" << endl;
            //printHubsValueHITS();
            //printAuthorityValueHITS();
            finalRankingHITS();
            printFinalRankingHITS();
            break;
        }

        i++;
    }

}


/*
int main(){

    hitsAlgorithm();

    //creatematrixHITS();
    //printGeneralMatrixHITS();

    //printHubsValueHITS();
    //printAuthorityValueHITS();  
    //printHubsWeightHITS();
    //printAuthorityWeightHITS();

    //initialize_authority_hubHITS();
    //printHubsValueHITS();
    //printAuthorityValueHITS(); 

   // initialize_authority_hub_weightHITS();
}
*/

#endif