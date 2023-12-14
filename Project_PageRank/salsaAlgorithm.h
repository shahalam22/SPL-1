#ifndef SALSAALGORITHM_H
#define SALSAALGORITHM_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define eps 10e-8
#include "graph.h"
using namespace std;

double generalMatrixSALSA[1000][1000];

double authorityMatrixSALSA[1000][1000];
double hubMatrixSALSA[1000][1000];

double finalRankValueSALSA[1000];
int finalRankIndexSALSA[1000];
int outLinkNumSALSA[1000];

double authority_valueSALSA[1000];
double hub_valueSALSA[1000];

double authority_weightSALSA[1000];
double hub_weightSALSA[1000];


void printHubsValueSALSA(){
    cout << "Hub Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_valueSALSA[i] << endl;
    }
}

void printAuthorityValueSALSA(){
    cout << "Authority Value: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_valueSALSA[i] << endl;
    }
}

void printHubsWeightSALSA(){
    cout << "Hub Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << hub_weightSALSA[i] << endl;
    }
}

void printAuthorityWeightSALSA(){
    cout << "Authority Weight: " << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << "of " << i+1 << " is: " << authority_weightSALSA[i] << endl;
    }
}

void printFinalRankingSALSA(){
    cout << "Final Ranking: " << endl;
    cout << "No\tIndex\tValue" << endl;
    for(int i=0; i<webPages.size(); i++){
        cout << i+1 << "\t" << finalRankIndexSALSA[i]+1 << "\t" << finalRankValueSALSA[finalRankIndexSALSA[i]] << endl;
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
void creatematrixSALSA(){

    initialize();

    // initializing matrix with zero
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            generalMatrixSALSA[i][j] = 0;
        }
    }
    
    //updating probability of the graph according to outgoing links
    for(int i=0; i<webPages.size(); i++){
        // vector<int> outLinkDemo = webPages.at(i-1).getOutLinks();
        // double outLinkProbability = (double)1/outLinkDemo.size();
        // for(int j=1; j<=outLinkDemo.size(); j++){
        //     generalMatrixSALSA[i][outLinkDemo.at(j-1)] = outLinkProbability;
        // }

        vector<int> outLinkDemo = webPages.at(i).getOutLinksIndex(webPages);
        //double outLinkProbability = (double)1/outLinkDemo.size();
        //outLinkNumSALSA[i+1] = outLinkDemo.size();
        for(int j=0; j<outLinkDemo.size(); j++){
            generalMatrixSALSA[i][outLinkDemo.at(j)-1] = 1;
        }
    }
}


void initialize_authority_hubSALSA(){
    for(int i=0; i<webPages.size(); i++){
        authority_valueSALSA[i] = 1.00;
        hub_valueSALSA[i] = 1.00;
    }
}

void initialize_authority_hub_weightSALSA(){
    for(int i=0; i<webPages.size(); i++){
        int num1 = 0;
        for(int j=0; j<webPages.size(); j++){
            num1 += generalMatrixSALSA[i][j];
        }
        hub_weightSALSA[i] = (double) num1/webPages.size();
        authority_weightSALSA[i] = (double)1-hub_weightSALSA[i];
    }
}

void authority_hub_MatrixCreationSALSA(){
    
    double lr[webPages.size()][webPages.size()];
    double lc[webPages.size()][webPages.size()];
    double lct[webPages.size()][webPages.size()];

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            lr[i][j] = generalMatrixSALSA[i][j];
            lc[i][j] = generalMatrixSALSA[i][j];
        }
    }

    for(int i=0; i<webPages.size(); i++){
        double sumr = 0;
        double sumc = 0;
        for(int j=0; j<webPages.size(); j++){
            sumr += generalMatrixSALSA[i][j];
            sumc += generalMatrixSALSA[j][i];
        }

        for(int k=0; k<webPages.size(); k++){
            if(sumr!=0){
                lr[i][k] = (double)lr[i][k]/sumr;
            }
            if(sumc!=0){
                lc[k][i] = (double)lc[k][i]/sumc;
            }
        }
    }

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            lct[i][j] = lc[j][i];
        }
    }

    //printing lr and lc 
    /*cout << "lr: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            printf("%7.2lf  ", lr[i][j]);
        }
        cout << endl;
    }

    cout << "lc: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            printf("%7.2lf  ", lc[i][j]);
        }
        cout << endl;
    }*/

    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            for(int k=0; k<webPages.size(); k++){
                hubMatrixSALSA[i][j] += lr[i][k]*lct[k][j];
                authorityMatrixSALSA[i][j] += lct[i][k]*lr[k][j];
            }
        }
    }

    //printing hubMatrixSALSA and authorityMatrixSALSA
    /*cout << "hubMatrixSALSA: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            printf("%7.2lf  ", hubMatrixSALSA[i][j]);
        }
        cout << endl;
    }

    cout << "authorityMatrixSALSA: " << endl;
    for(int i=0; i<webPages.size(); i++){
        for(int j=0; j<webPages.size(); j++){
            printf("%7.2lf  ", authorityMatrixSALSA[i][j]);
        }
        cout << endl;
    }*/

}

bool convergeSALSA(double temp_authority_value[], double temp_hub_value[], double authority_valueSALSA[], double hub_valueSALSA[]){
    bool flag = true;
    for(int i=0; i<webPages.size(); i++){
        if(fabs(temp_authority_value[i]-authority_valueSALSA[i]) > eps){
            flag = false;
        }
        if(fabs(temp_hub_value[i]-hub_valueSALSA[i]) > eps){
            flag = false;
        }
    }
    return flag;
}

void normalizeSALSA(){
    double sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += authority_valueSALSA[i]*authority_valueSALSA[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        authority_valueSALSA[i] = authority_valueSALSA[i]/sum;
    }

    sum = 0;
    for(int i=0; i<webPages.size(); i++){
        sum += hub_valueSALSA[i]*hub_valueSALSA[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<webPages.size(); i++){
        hub_valueSALSA[i] = hub_valueSALSA[i]/sum;
    }
}

void finalRankingSALSA(){
    for(int i=0; i<webPages.size(); i++){
        finalRankValueSALSA[i] = ((authority_weightSALSA[i]*authority_valueSALSA[i]) + (hub_valueSALSA[i]*hub_weightSALSA[i]));
    }

    double demoFinalRankValue[webPages.size()];
    for(int i=0; i<webPages.size(); i++){
        demoFinalRankValue[i] = finalRankValueSALSA[i];
    }

    //giving final rank index
    for(int i=0; i<webPages.size(); i++){
        int max = 0;
        for(int j=0; j<webPages.size(); j++){
            if(demoFinalRankValue[j] > demoFinalRankValue[max]){
                max = j;
            }
        }
        finalRankIndexSALSA[i] = max;
        demoFinalRankValue[max] = -1;
    }
}


void salsaAlgorithm(){
    creatematrixSALSA();
    initialize_authority_hubSALSA();
    initialize_authority_hub_weightSALSA();
    authority_hub_MatrixCreationSALSA();

    double temp_authority_value[webPages.size()];
    double temp_hub_value[webPages.size()];

    int i=0;

    while(1){
        for(int i=0; i<webPages.size(); i++){
            temp_authority_value[i] = authority_valueSALSA[i];
            temp_hub_value[i] = hub_valueSALSA[i];
        }

        for(int i=0; i<webPages.size(); i++){
            double sumAuth = 0;
            double sumHub = 0;
            for(int j=0; j<webPages.size(); j++){
                sumAuth += authorityMatrixSALSA[j][i]*temp_authority_value[j];
                sumHub += hubMatrixSALSA[j][i]*temp_hub_value[j];
            }
            authority_valueSALSA[i] = sumAuth*authority_weightSALSA[i];
            hub_valueSALSA[i] = sumHub*hub_weightSALSA[i];
        }

        normalizeSALSA();

        if(convergeSALSA(temp_authority_value, temp_hub_value, authority_valueSALSA, hub_valueSALSA)){
            cout << "Final Hub And Authority Value:" << endl;
            //printHubsValueSALSA();
            //printAuthorityValueSALSA();
            finalRankingSALSA();
            printFinalRankingSALSA();
            break;
        }

        i++;

    }
}

/*
int main(){

    salsaAlgorithm();

    //printHubsValueSALSA();
    //printAuthorityValueSALSA();  
    //printHubsWeightSALSA();
    //printAuthorityWeightSALSA();

    //initialize_authority_hubSALSA();
    //printHubsValueSALSA();
    //printAuthorityValueSALSA();

    //initialize_authority_hub_weightSALSA();

    //authority_hub_MatrixCreationSALSA();

    return 0;
}
*/

#endif