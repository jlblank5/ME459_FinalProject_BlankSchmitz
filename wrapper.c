// Author: Dylan Schmitz
// wrapper to test stuff

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "fileIO.h"
#include "filter.h"
#include "sort.h"
#include "xcorr.h"

int main(int argc,char *argv[]){
    //char *filename = "check1.lvm";
    char *fileIn = "check2.lvm";
    char *fileOut = "processed.csv";
    char *pushFile = "processed_push.csv";
    char *releaseFile = "processed_release.csv";
    char *sortedTapOut = "sortedTap.csv";
    double **dataMatrix;
    //double *dataMatrix;
    int numFields = 0; // number of fields (i.e. data columns) in the .lvm file
    int numSamples = 0; // number of samples (i.e. data rows) in the .lvm file

    int sampleFreq = 50000; // Hz

    double filter[2] = {150,5000};
    double window[2] = {0,2};
    double travelDist = 10;

    int i, j; // index variables

    // ----- timing -----
    clock_t start, stop; // timer vars
    double cpu_time_used; // timer vars
	start = clock();
    // ----- timing -----

    dataMatrix = readLVM(fileIn,&numFields,&numSamples); // call readLVM to load data into a matrix
   
    // filter first accelerometer data
    double *filteredAcc1, *filteredAcc2;
    filteredAcc1 = filtfilt(dataMatrix[1], numSamples, sampleFreq, filter[0], filter[1]);
    filteredAcc2 = filtfilt(dataMatrix[2], numSamples, sampleFreq, filter[0], filter[1]);

    //writeCSV(fileOut,dataMatrix[0],numSamples,1); // write filtered data out to file for plotting in Matlab

    // sort the push and pull tap indices
    int *pushPullIndices;
    int nLead, nTrail;
    size_t ind1, ind2;
    pushPullIndices = sort(dataMatrix[0], sampleFreq, numSamples, 100, &nLead, &nTrail);

    writeCSVInt(sortedTapOut,pushPullIndices,1000,1); // write filtered data out to file for plotting in Matlab

    // compute wave speed
    bool whichFirst = 0;
    double *push, *release;
    double delay = 0.0;
    int nPush, nRelease;
    if(nLead > nTrail){
        push = (double *) malloc(sizeof(double) * nTrail);
        nPush = nTrail;

        release = (double *) malloc(sizeof(double) * nTrail);
        nRelease = nTrail;
    }else if(nLead < nTrail){
        whichFirst = 1;
        push = (double *) malloc(sizeof(double) * nLead);
        nPush = nLead;

        release = (double *) malloc(sizeof(double) * nLead);
        nRelease = nLead;
    }else{
        if(pushPullIndices[0] > pushPullIndices[nLead]){
            whichFirst = 1;
        }

        if(!whichFirst){
            push = (double *) malloc(sizeof(double) * nLead);
            nPush = nLead;

            release = (double *) malloc(sizeof(double) * (nLead-1));
            nRelease = nLead - 1;
        }else{
            push = (double *) malloc(sizeof(double) * (nTrail-1));
            nPush = nTrail - 1;

            release = (double *) malloc(sizeof(double) * nTrail);
            nRelease = nTrail;
        }
    }// if malloc based on relative push/release length

    for( i = 0 ; i < nPush ; i++ ){
        if(!whichFirst){
            ind1 = pushPullIndices[i];
            ind2 = pushPullIndices[nPush + i];
        }else{
            ind1 = pushPullIndices[i];
            ind2 = pushPullIndices[nPush + i + 1];
        }// end conditional whichFirst

        delay = computeTimeDelay(filteredAcc1, filteredAcc2, ind1, ind2, window, sampleFreq);
        push[i] =  travelDist/delay;
    }// end for each push

    for( i = 0 ; i < nRelease ; i++ ){
        if(!whichFirst){
            ind1 = pushPullIndices[nPush + i];
            ind2 = pushPullIndices[i + 1];
        }else{
            ind1 = pushPullIndices[nPush + i];
            ind2 = pushPullIndices[i];
        }// end conditional whichFirst

        release[i] =  travelDist/computeTimeDelay(filteredAcc1, filteredAcc2, ind1, ind2, window, sampleFreq);
    }// end for each push

    // ----- timing -----
    stop = clock();
    cpu_time_used = ((double) (stop - start)) / CLOCKS_PER_SEC;
    printf("Exec. time: %.2f seconds",cpu_time_used);
    // ----- timing -----

    writeCSV(pushFile,push,nPush,1);
    writeCSV(releaseFile,release,nRelease,1);

    free(dataMatrix);
    free(filteredAcc1);
    free(pushPullIndices);
    free(push);
    free(release);

    return 0;
}// end main