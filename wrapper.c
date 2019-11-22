// Author: Dylan Schmitz
// wrapper to test stuff

#include <stdlib.h>
#include <stdio.h>
#include "readLVM.h"
#include "filter.h"

int main(int argc,char *argv[]){
    //char *filename = "check1.lvm";
    char *filename = argv[1];
    double **dataMatrix;
    //double *dataMatrix;
    int numFields = 0; // number of fields (i.e. data columns) in the .lvm file
    int numSamples = 0; // number of samples (i.e. data rows) in the .lvm file

    int sampleFreq = 50000; // Hz

    int i, j; // index variables

    dataMatrix = readLVM(filename,&numFields,&numSamples); // call readLVM to load data into a matrix

    // print the data with each field in its own column
    /*
    for( j = 0 ; j < numSamples ; j++ ){
        for( i = 0 ; i < numFields ; i++ ){
            printf("%.4f\t",dataMatrix[i][j]);
            printf("%.12f,",dataMatrix[i][j]);
            //printf("%.12f,",dataMatrix[(j*numFields) + i]);
        }// end for fields
        printf("\b\n");
    }// end for samples
    */

    // Test the low-pass filter coefficient calculator
    /*
    double B[3];
    double A[3];
    butterLP(1500,50000,B,A);
    printf("Low-pass numerator coefficients: %.6f %.6f %.6f\n",A[0],A[1],A[2]);
    printf("Low-pass denominator coefficients: %.6f %.6f %.6f\n",B[0],B[1],B[2]);
    */
   
    // filter first accelerometer data
    double *filteredAcc1;
    filteredAcc1 = filtfilt(dataMatrix[1], numSamples, sampleFreq, 150, 1500);

    for( i = 0 ; i < numSamples ; i++ ){
        printf("%f\n",filteredAcc1[i]);
    }//end for

    free(dataMatrix);
    free(filteredAcc1);

    return 0;
}// end main