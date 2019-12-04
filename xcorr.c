// normxcorr: Function to compute the normalized cross correlation between a template and a reference signal
// computeTimeDelay: computes the delay between two shear wave arrivals in two signals for a given tap instance
// Author(s): Jon Blank, Dylan Schmitz
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double *normxcorr(double *templ, size_t lenT, double *ref, size_t lenR){
    double *r = (double *) malloc(sizeof(double) * (lenR - lenT)); //array of correlation coefficients
    double *seg; // subarray pointer

    double mult, A2, B2;
    int i, j; // loop index variable

    for ( i = 0 ; i < (lenR-lenT) ; i++ ){
        seg = &ref[i];
        mult = 0;
        A2 = 0;
        B2 = 0;

        for ( j = 0 ; j < lenT ; j++ ){
            mult += templ[j] * seg[j];
            A2 += templ[j] * templ[j];
            B2 += seg[j] * seg[j];
        }// end for j

        r[i] = mult/sqrt(A2*B2);
    }// end for i

    return r;
}// end normxcorr

double computeTimeDelay(double *sig1, double *sig2, size_t indA, size_t indZ, double *window, int sampleRate){
    double *templ, *ref, *r;
    double timeDelay;
    int windowShift;
    size_t templLength, refLength;

    // determine the beginning index of the template according to the first element of window (which is in milliseconds)
    windowShift = (int) (sampleRate*window[0]/1000);

    // define the template length according to the second element of window
    templLength = (size_t) (sampleRate*(window[1] - window[2]));
    
    // define the template as a segment of sig1 based on indA and the window
    templ = &sig1[indA + windowShift];

    // define the reference array length by the difference between indZ and indA
    refLength = indZ - indA;

    // define the reference as a segment of sig2 starting at indA
    ref = &sig2[indA];

    // perform the cross-correlation between the template and reference signals
    r = normxcorr(templ,templLength,ref,refLength);

    // find the maximum correlation value

    // peform cosine interpolation for subsample frame shift

    // compute time lag based on frame lag


    free(r);

    return timeDelay;
    

}// end computeTimeDelay