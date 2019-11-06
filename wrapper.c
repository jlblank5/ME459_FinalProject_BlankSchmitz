// Author: Dylan Schmitz
// wrapper to test stuff

#include <stdlib.h>
#include <stdio.h>
#include "readLVM.h"

int main(int argc,char *argv[]){
    //char *filename = "check1.lvm";
    char *filename = argv[1];
    //double **dataMatrix;
    double *dataMatrix;
    int numFields = 0; // number of fields (i.e. data columns) in the .lvm file
    int numSamples = 0; // number of samples (i.e. data rows) in the .lvm file

    int i, j; // index variables

    dataMatrix = readLVM(filename,&numFields,&numSamples); // call readLVM to load data into a matrix

    // print the data with each field in its own column
    for( j = 0 ; j < numSamples ; j++ ){
        for( i = 0 ; i < numFields ; i++ ){
            //printf("%.4f\t",dataMatrix[i][j]);
            //printf("%.12f,",dataMatrix[i][j]);
            printf("%.12f,",dataMatrix[(j*numFields) + i]);
        }// end for fields
        printf("\b\n");
    }// end for samples

    free(dataMatrix);

    return 0;
}// end main