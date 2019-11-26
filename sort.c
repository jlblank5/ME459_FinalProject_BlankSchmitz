// Author: Jon Blank

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    return i;
}

// finds the difference in successive array elements
double* diff(double arr[], size_t size){
    double d;
    // dynamically allocate an array to store values
    double* diff = malloc((*double)(size-1)*sizeof(double));
    // find the difference at each point in the array
    for (int i=0; i<size-1; i++){
        diff[i] = arr[i+1]-arr[i];
    }
    return diff;
}

// computed the cross-correlation given two signals, a window, the sampling time and returns
// the correlation coefficient and time delay
double * sort(double *signalRef, double ts, double tapRate, double *timeDelay){

    // get rid of aberrant negative values
    for (int i=1; i<len(signalRef)-1; i++){
        if (signalRef[i]<0){
            signalRef[i]=(signalRef[i-1]+signalRef[i+1])/2;
        }
    }

    // calculate the data points per tap
    double m = ts/tapRate;
    // create an array of booleans the size of signalRef
    boolean* extended = malloc((*boolean)len(signalRef)*sizeof(boolean));
    boolean* retracted = malloc((*boolean)len(signalRef)*sizeof(boolean));
    int* leading = malloc((*int)m*sizeof(int));
    int* trailing = malloc((*int)m*sizeof(int));
    // find pulse edges of the tap signal
    int n = len(signalRef);
    int j = 0; int k = 0; int flag;
    for (int i=0; i<n; i++){
        // store the extended and retracted tapper data
        extended[i]=signalRef[i]>signalRef(max(signalRef,n))/2;
        retracted[i]=signalRef[i]<signalRef(max(signalRef,n))/2;
        if (i<n-1){
            // store the leading and trailing indices
            if (abs(extended[i+1]-extended[i])>0){flag=1;}
            if (flag){leading[j]=i; j++;}    
            if (abs(retracted[i+1]-retracted[i])>0){flag=0;}
            if (!flag){trailing[k]=i; k++;}
        }
    }
    free(extended);
    free(retracted);

    // implement a sorting algorithm to obtian the data during the push and pull events
    int nPush = len(leading)
    // dynamically allocate memory for the push data
    double* push = malloc((*double)n*sizeof(double));
    for (int i=0; i<n; i++){
        push[i] = signalRef[leading[i]];
    }
    int nPull = len(trailing)
    // dynamically allocate memory for the pull data
    double* pull = malloc((*double)n*sizeof(double));
    for (int i=0; i<n; i++){
        pull[i] = signalRef[trailing[i]];
    }

    // create the sorted array to hold all of the push and pull data
    if (nPush==nPull){
        double sortedArray[nPush][2];
    } else {
        double* sortedArray = malloc((*double)(nPush+nPull)*sizeof(double));
    }
    

    return sortedArray;
}