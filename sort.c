// Author: Jon Blank

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort.h"

// finds the max of a given array
int max(double arr[], size_t size){
    // initialize the max
    int max = 0; 
    // find the maximum value in the array
    for(int i=0; i<size; i++){
        if (arr[i]>arr[max]){
            max = i;
        }
    }
    return max;
}

// computed the cross-correlation given two signals, a window, the sampling time and returns
// the correlation coefficient and time delay
int *sort(const double* signalRef, size_t ts, size_t tapRate){

    // initialize the new tap signal
    int n = sizeof(signalRef)/sizeof(signalRef[0]);
    double* signal = (double*)malloc(n*sizeof(double));

    // get rid of aberrant negative values
    for (int i=1; i<n-1; i++){
        if (signalRef[i]<0){
            signal[i]=(signalRef[i-1]+signalRef[i+1])/2;
        }
    }

    // calculate the data points per tap
    int m = ts/tapRate;
    // create an array of booleans the size of signalRef
    bool* extended = (bool*)malloc((int)(sizeof(signal)/sizeof(signal[0]))*sizeof(bool));
    bool* retracted = (bool*)malloc((int)(sizeof(signal)/sizeof(signal[0]))*sizeof(bool));
    int* leading = (int*)malloc(m*sizeof(int));
    int* trailing = (int*)malloc(m*sizeof(int));
    // find pulse edges of the tap signal
    int j = 0; int k = 0; int flag;
    for (int i=0; i<n; i++){
        // store the extended and retracted tapper data
        extended[i]=signal[i]>(max(signal,n))/2;
        retracted[i]=signal[i]<(max(signal,n))/2;
        if (i<n-1){
            // store the leading and trailing indices
            if (abs(extended[i+1]-extended[i])>0){flag=1;}
            if (flag){leading[j]=i; flag=0; j++;}    
            if (abs(retracted[i+1]-retracted[i])>0){flag=1;}
            if (!flag){trailing[k]=i; flag=0; k++;}
        }
    }
    free(extended);
    free(retracted);

    // dynamically allocate memory to store leading and trailing indices
    int nLeading = 0; int nTrailing = 0;
    for (int i=0; i<m; i++){
        if (&leading[i] != NULL){nLeading++;}
        if (&trailing[i] != NULL){nTrailing++;}
    }
    int* pushPullIndices = (int*)malloc((nTrailing+nLeading)*sizeof(int));
    if (nLeading>nTrailing){
        for (int i=0; i<nLeading; i++){
            pushPullIndices[i] = leading[i];
            if (i==nLeading-1){
                // skip this indices
            } else {
                pushPullIndices[nLeading+i] = trailing[i];
            }
        }
    } else {
        for (int i=0; i<nTrailing; i++){
            pushPullIndices[nLeading+i] = trailing[i];
            if (i==nLeading + 1){
                // skip this indices
            } else {
                pushPullIndices[i] = leading[i];
            }
        }
    }  

    free(leading);
    free(trailing);

    return pushPullIndices;
}