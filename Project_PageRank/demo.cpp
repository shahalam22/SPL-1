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


// this is the demo page to the page rank

/*

#include <stdio.h>

// Function to merge two subarrays of arr[].
// First subarray is arr[l..m].
// Second subarray is arr[m+1..r].
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive function to perform merge sort on the array
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Utility function to print an array
void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Driver program to test the functions
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);

    return 0;
}


*/