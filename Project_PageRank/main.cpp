#include <bits/stdc++.h>
#include "googlePageRank.h"
#include "hitsAlgorithm.h"
#include "randomizedHITS.h"
#include "salsaAlgorithm.h"

using namespace std;

int main(){

    int choice;

    while(1){
        cout << "WELCOME to the DASHBOARD" << endl << endl;
        cout << "Analysis webpages ranking using different algorithms" << endl;
        cout << "Please select the algorithm you want to run" << endl << endl;
        cout << "1. Google PageRank Algorithm" << endl;
        cout << "2. HITS Algorithm" << endl;
        cout << "3. Randomized HITS Algorithm" << endl;
        cout << "4. SALSA Algorithm" << endl << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if(choice==1){
            googlePageRank();
        }
        else if(choice==2){
            hitsAlgorithm();
        }
        else if(choice==3){
            randomizedHitsAlgorithm();
        }
        else if(choice==4){
            salsaAlgorithm();
        }
        else if(choice==0){
            break;
        }
        else{
            cout << "Invalid choice" << endl;
            break;
        }
    }

}