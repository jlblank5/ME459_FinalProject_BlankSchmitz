// Author: Dylan Schmitz
// filters raw accelerometer signals using a 2nd order butterworth filter

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159

int main(void){
    //variable declarations
    int i; //index variable

    double low = 150.0; // Hz
    double high = 1500.0; // Hz
    double fSamp = 50000; // Hz
    low = low/(fSamp/2); // convert
    high = high/(fSamp/2); // convert

    int fs = 2;

    //compute filter coefficients [A] and [B]
    double u[2];
    u[0] = 2*fs*tan(PI*low/fs);
    u[1] = 2*fs*tan(PI*high/fs);

    double Bw, Wn;
    Bw = u[1] - u[0]; // bandwidth?
    Wn = sqrt(low*high); // center frequency

    double a[2][2] = {{-sqrt(2),-1},{1,0}}; //convert to state-space
    double b[2] = {1,0}; //vertical
    double c[2] = {0,1}; //horizontal
    double d = 0;

    //lp2bp
    double q;
    q = Wn/Bw;
    double at[4][4] = {0};
    for(i = 0;i < 2;i++){
        at[i][i] = Wn*a[i][i]/q;
        at[i][i+1] = Wn*a[i][i+1]/q;
    }//end for
    at[1][3] = 1;
    at[2][4] = 1;
    at[3][1] = -1;
    at[4][2] = -1;

    double bt[4] = {0};
    bt[0] = Wn*b[0]/q;
    bt[1] = Wn*b[1]/q;

    double ct[4] = {0};
    ct[0] = Wn*c[0];
    ct[1] = Wn*b[1];
    
    double dt = d;

    //bilinear
    double t = 1/fs;
    double r = sqrt(t);

    double t1[4][4];
    t1[1][1] = 1 + a[1][1]/4;
    t1[1][2] = a[1][2]/4;
    t1[2][1] = 1 + a[2][1]/4;
    t1[2][2] = a[2][2]/4;

    double t2[4][4];
    t2[1][1] = 1 - a[1][1]/4;
    t2[1][2] = -a[1][2]/4;
    t2[2][1] = 1 - a[2][1]/4;
    t2[2][2] = -a[2][2]/4;

    for(i + 0;i<4;i++){
        a[i/2][i%2] = t2[i/2][i%2]/t1[i/2][i%2];
    }


    /*
    b[0] = t/r * t2/b;
    c = r*c/t2;
    d = c/t2 * b * t/2 + d;
    */

    //apply filter to input signal

    //return filtered signal


    return 0;
}// end main