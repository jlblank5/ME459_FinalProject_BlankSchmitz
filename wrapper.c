// Author: Dylan Schmitz
// wrapper to test stuff

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "fileIO.h"
#include "filter.h"
#include "sort.h"

int main(int argc,char *argv[]){
    //char *filename = "check1.lvm";
    char *fileIn = "check2.lvm";
    char *fileOut = "processed.csv";
    char *sortedTapOut = "sortedTap.csv";
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

    writeCSV(fileOut,dataMatrix[0],numSamples,1); // write filtered data out to file for plotting in Matlab

    // sort the push and pull tap indices
    int *pushPullIndices;
    pushPullIndices = sort(dataMatrix[0], sampleFreq, numSamples, 100);

    writeCSVInt(sortedTapOut,pushPullIndices,1000,1); // write filtered data out to file for plotting in Matlab

    free(dataMatrix);
    free(filteredAcc1);
    free(pushPullIndices);

    return 0;
}// end main