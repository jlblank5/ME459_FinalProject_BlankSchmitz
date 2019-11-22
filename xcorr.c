// Author: Jon Blank

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// computed the cross-correlation given two signals, a window, the sampling time and returns
// the correlation coefficient and time delay
double * readLVM(double *signalRef, double *signalMatch, double ts, double *window, double *timeDelay){

    double *corrCoeff;

    // create the time array of the window
    double time = ts*window;
    double ref = signalRef[0:len(time)];
    double match = signalMatch;

    // loop through each instance in time and compute the correlation
    for (int i = 0; i < len(time); i++){
        for (int j = 0; j < len(ref); j++){
            
        }
    }

    return corrCoeff;
}