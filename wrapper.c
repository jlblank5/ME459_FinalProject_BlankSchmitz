// Author: Dylan Schmitz
// wrapper to test stuff

#include <stdlib.h>
#include <stdio.h>
#include "fileIO.h"
#include "filter.h"

int main(int argc,char *argv[]){
    //char *filename = "check1.lvm";
    char *fileIn = argv[1];
    char *fileOut = "processed.csv";
    double **dataMatrix;
    //double *dataMatrix;
    int numFields = 0; // number of fields (i.e. data columns) in the .lvm file
    int numSamples = 0; // number of samples (i.e. data rows) in the .lvm file

    int sampleFreq = 50000; // Hz

    int i, j; // index variables

    dataMatrix = readLVM(fileIn,&numFields,&numSamples); // call readLVM to load data into a matrix
   
    // filter first accelerometer data
    double *filteredAcc1;
    filteredAcc1 = filtfilt(dataMatrix[1], numSamples, sampleFreq, 150, 1500);

    writeCSV(fileOut,filteredAcc1,numSamples,1); // write filtered data out to file for plotting in Matlab

    free(dataMatrix);
    free(filteredAcc1);

    return 0;
}// end main