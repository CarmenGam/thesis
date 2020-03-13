#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>


#define FWHM 3.5 /* Anchura a media altura en mV*/
#define PI 3.14159265358979323846
#define pow2(x) = (x*x)


 int Input_Signals(double A[7], int t, double *input_signal[7][200]){

  int i,j;
  double  sigma = FWHM / (2.0*sqrt(log(2.0)));
  FILE *fp[7];
  
  fp[0]=fopen("data1.txt","w");
  fp[1]=fopen("data2.txt","w");
  fp[2]=fopen("data3.txt","w");
  fp[3]=fopen("data4.txt","w");
  fp[4]=fopen("data5.txt","w");
  fp[5]=fopen("data6.txt","w");
  fp[6]=fopen("data7.txt","w");

   for (j=0; j<7; j++){
    t=-10.0;
    for (i=0; i < 200; i++){
    t = t + 0.1;
    input_signal[j][i] =  A[j] * (1.0/(sigma*sqrt(2.0*PI))*exp(-pow2(t)/(2.0*(pow2(sigma)))));
    fprintf (fp[j], "%f %f\n",t, input_signal[i][j]);
    
    }

  }
 
  for (i=0; i<7; i++)
   fclose(fp[i]);


  return(1);
}



