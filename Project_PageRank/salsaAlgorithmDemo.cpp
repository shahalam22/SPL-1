#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#define eps 10e-8
//#include "graphCopy.h"
using namespace std;

double generalMatrix[6][6] = {{0,0,1,0,1,0},
                              {1,0,0,0,0,0},
                              {0,0,0,0,1,0},
                              {0,0,0,0,0,0},
                              {0,0,1,1,0,0},
                              {0,0,0,0,1,0}};

double authorityMatrix[1000][1000];
double hubMatrix[1000][1000];

double finalRankValue[1000];
int finalRankIndex[1000];
int outLinkNum[1000];

double authority_value[1000];
double hub_value[1000];

double authority_weight[1000];
double hub_weight[1000];


void printHubsValue(){
    cout << "Hub Value: " << endl;
    for(int i=0; i<6; i++){
        cout << "of " << i+1 << " is: " << hub_value[i] << endl;
    }
}

void printAuthorityValue(){
    cout << "Authority Value: " << endl;
    for(int i=0; i<6; i++){
        cout << "of " << i+1 << " is: " << authority_value[i] << endl;
    }
}

void printHubsWeight(){
    cout << "Hub Weight: " << endl;
    for(int i=0; i<6; i++){
        cout << "of " << i+1 << " is: " << hub_weight[i] << endl;
    }
}

void printAuthorityWeight(){
    cout << "Authority Weight: " << endl;
    for(int i=0; i<6; i++){
        cout << "of " << i+1 << " is: " << authority_weight[i] << endl;
    }
}

void printFinalRanking(){
    cout << "Final Ranking: " << endl;
    cout << "No\tIndex\tValue" << endl;
    for(int i=0; i<6; i++){
        cout << i+1 << "\t" << finalRankIndex[i]+1 << "\t" << finalRankValue[finalRankIndex[i]] << endl;
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
/*void creatematrix(){

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
        //double outLinkProbability = (double)1/outLinkDemo.size();
        //outLinkNum[i+1] = outLinkDemo.size();
        for(int j=0; j<outLinkDemo.size(); j++){
            generalMatrix[i][outLinkDemo.at(j)-1] = 1;
        }
    }
}
*/


void initialize_authority_hub(){
    for(int i=0; i<6; i++){
        authority_value[i] = 1.00;
        hub_value[i] = 1.00;
    }
}

void initialize_authority_hub_weight(){
    for(int i=0; i<6; i++){
        int num1 = 0;
        for(int j=0; j<6; j++){
            num1 += generalMatrix[i][j];
        }
        hub_weight[i] = (double) num1/6;
        authority_weight[i] = (double)1-hub_weight[i];
    }
}

void authority_hub_MatrixCreation(){
    
    double lr[6][6];
    double lc[6][6];
    double lct[6][6];

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            lr[i][j] = generalMatrix[i][j];
            lc[i][j] = generalMatrix[i][j];
        }
    }

    for(int i=0; i<6; i++){
        double sumr = 0;
        double sumc = 0;
        for(int j=0; j<6; j++){
            sumr += generalMatrix[i][j];
            sumc += generalMatrix[j][i];
        }

        for(int k=0; k<6; k++){
            if(sumr!=0){
                lr[i][k] = (double)lr[i][k]/sumr;
            }
            if(sumc!=0){
                lc[k][i] = (double)lc[k][i]/sumc;
            }
        }
    }

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            lct[i][j] = lc[j][i];
        }
    }

    //printing lr and lc 
    /*cout << "lr: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%7.2lf  ", lr[i][j]);
        }
        cout << endl;
    }

    cout << "lc: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%7.2lf  ", lc[i][j]);
        }
        cout << endl;
    }*/

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            for(int k=0; k<6; k++){
                hubMatrix[i][j] += lr[i][k]*lct[k][j];
                authorityMatrix[i][j] += lct[i][k]*lr[k][j];
            }
        }
    }

    //printing hubMatrix and authorityMatrix
    /*cout << "hubMatrix: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%7.2lf  ", hubMatrix[i][j]);
        }
        cout << endl;
    }

    cout << "authorityMatrix: " << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            printf("%7.2lf  ", authorityMatrix[i][j]);
        }
        cout << endl;
    }*/

}

bool converge(double temp_authority_value[], double temp_hub_value[], double authority_value[], double hub_value[]){
    bool flag = true;
    for(int i=0; i<6; i++){
        if(fabs(temp_authority_value[i]-authority_value[i]) > eps){
            flag = false;
        }
        if(fabs(temp_hub_value[i]-hub_value[i]) > eps){
            flag = false;
        }
    }
    return flag;
}

void normalize(){
    double sum = 0;
    for(int i=0; i<6; i++){
        sum += authority_value[i]*authority_value[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<6; i++){
        authority_value[i] = authority_value[i]/sum;
    }

    sum = 0;
    for(int i=0; i<6; i++){
        sum += hub_value[i]*hub_value[i];
    }
    sum = sqrt(sum);
    for(int i=0; i<6; i++){
        hub_value[i] = hub_value[i]/sum;
    }
}

void finalRanking(){
    for(int i=0; i<6; i++){
        finalRankValue[i] = ((authority_weight[i]*authority_value[i]) + (hub_value[i]*hub_weight[i]));
    }

    double demoFinalRankValue[6];
    for(int i=0; i<6; i++){
        demoFinalRankValue[i] = finalRankValue[i];
    }

    //giving final rank index
    for(int i=0; i<6; i++){
        int max = 0;
        for(int j=0; j<6; j++){
            if(demoFinalRankValue[j] > demoFinalRankValue[max]){
                max = j;
            }
        }
        finalRankIndex[i] = max;
        demoFinalRankValue[max] = -1;
    }
}


void salsaAlgorithm(){
    //creatematrix();
    initialize_authority_hub();
    initialize_authority_hub_weight();
    authority_hub_MatrixCreation();

    double temp_authority_value[6];
    double temp_hub_value[6];

    int i=0;

    while(1){
        for(int i=0; i<6; i++){
            temp_authority_value[i] = authority_value[i];
            temp_hub_value[i] = hub_value[i];
        }

        for(int i=0; i<6; i++){
            double sumAuth = 0;
            double sumHub = 0;
            for(int j=0; j<6; j++){
                sumAuth += authorityMatrix[j][i]*temp_authority_value[j];
                sumHub += hubMatrix[j][i]*temp_hub_value[j];
            }
            authority_value[i] = sumAuth*authority_weight[i];
            hub_value[i] = sumHub*hub_weight[i];
        }

        normalize();

        if(converge(temp_authority_value, temp_hub_value, authority_value, hub_value)){
            cout << "Final Hub And Authority Value:" << endl;
            //printHubsValue();
            //printAuthorityValue();
            finalRanking();
            printFinalRanking();
            break;
        }

        i++;

    }
}

int main(){

    //salsaAlgorithm();

    //printHubsValue();
    //printAuthorityValue();  
    //printHubsWeight();
    //printAuthorityWeight();

  /*  initialize_authority_hub();
    printHubsValue();
    printAuthorityValue(); */

   // initialize_authority_hub_weight();

    authority_hub_MatrixCreation();

    return 0;
}
