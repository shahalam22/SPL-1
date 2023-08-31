#include <iostream>
using namespace std;


void printPageRankProbability(double pageProbability[], int size){
    cout << "Page Rank Probability : ";
    for(int i=1; i<=size; i++){
        printf("%lf ", pageProbability[i]);
    }
}

int main(){
    double generalMatrix[7][7] = {0, 0, 0, 0, 0, 0, 0,
                            0, 0.00, 0.33, 0.00, 0.33, 0.00, 0.33,
                            0, 0.50, 0.00, 0.50, 0.00, 0.00, 0.00,
                            0, 0.50, 0.00, 0.00, 0.50, 0.00, 0.00,
                            0, 0.00, 0.00, 0.50, 0.00, 0.00, 0.50,
                            0, 0.33, 0.33, 0.33, 0.00, 0.00, 0.00,
                            0, 0.00, 0.33, 0.00, 0.33, 0.33, 0.00};
    double pageRankProbability[7] = {0, 0.166667, 0.166667, 0.166667, 0.166667, 0.166667, 0.166667};
    int size = 6;

    double demoPageProbability[size];

    for(int m=0; m<5; m++){
        for(int i=1; i<=size; i++){
            demoPageProbability[i] = pageRankProbability[i];
        }

        for(int j=1; j<=size; j++){
            double demo = 0;
            for(int k=1; k<=size; k++){
                demo += generalMatrix[j][k]*pageRankProbability[k];
                // cout << demo << "  ";
            }
            pageRankProbability[j] = demo;
        }
        printPageRankProbability(demoPageProbability, size);
        cout << "\t";
        printPageRankProbability(pageRankProbability, size);
        cout << endl;
    }
}