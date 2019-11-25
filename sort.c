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
double diff(double arr[], size_t size){
    double d;
    // find the difference at each point in the array
    for (int i=0; i<size; i++){
        
    }
}

// computed the cross-correlation given two signals, a window, the sampling time and returns
// the correlation coefficient and time delay
double * sort(double *signalRef, double ts, double *timeDelay){

    // get rid of aberrant negative values
    for (int i=1; i<len(signalRef)-1; i++){
        if (signalRef[i]<0){
            signalRef[i]=(signalRef[i-1]+signalRef[i+1])/2;
        }
    }

    // create an array of booleans the size of signalRef
    boolean* extended = malloc((*boolean)len(signalRef)*sizeof(boolean));
    boolean* retracted = malloc((*boolean)len(signalRef)*sizeof(boolean));
    // find pulse edges of the tap signal
    int n = len(signalRef);
    for (int i=0; i<n; i++){
        extended[i]=signalRef[i]>signalRef(max(signalRef,n))/2;
        retracted[i]=signalRef[i]<signalRef(max(signalRef,n))/2;
    }

    return corrCoeff;
}