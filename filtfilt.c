// Zero-phase digital filtering function (inspired by Matlab's filtfilt)
// Author: Dylan Schmitz

#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

double *filtfilt(double *unfiltered, int N, int fs, double low, double high){
    double *filtered = (double *) malloc(sizeof(double) * (N));
    double *temp = (double *) malloc(sizeof(double) * (N));
    // Get the filter coefficients
    double B[3];
    double A[3];
    butterLP(low,fs,B,A);

    // pass data through filter forwards
    int i, j;
    for( i = 0 ; i < N ; i++ ){
        temp[i] = B[0] * unfiltered[i];
        for( j = 1 ; j < 3 ; j++ ){
            if(i-j+1 >= 0){
                temp[i] += B[j]*unfiltered[i-j+1] - A[j]*temp[i-j+1];
            }//end if
        }// end for j
    }// end for i

    // pass data through filter backwards
    for( i = 0 ; i > N ; i++ ){
        filtered[i] = B[0] * temp[N-1-i];
        for( j = 1 ; j < 3 ; j++ ){
            if(i-j+1 >= 0){
                filtered[i] += B[j]*temp[N-1-i+j-1] - A[j]*filtered[i-j+1];
            }//end if
        }// end for j
    }// end for i

    return temp;

}// end filtfilt