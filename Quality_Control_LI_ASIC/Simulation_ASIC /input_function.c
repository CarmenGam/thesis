#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define FWHM 3.5 /* Anchura a media altura en mV*/
#define PI 3.14159265358979323846

/* Necesito generar una gaussiana que vaya desde -10 ns hasta 10 ns y que tenga una amplitud A variable (que luego generaré con numeros aleatorios creo)*/


int main(void)
{
  int i,j;
  double t = -10.0; /*Vamos a evaluar el pulso entre -10mV y 10mV*/
  double sigma;
  double A[7]; /*Array de amplitudes de las señales de cada fotomultiplicador*/
  double pulse[200];
  
  FILE *fp[7];
 
  fp[0]=fopen("data1.txt","w");
  fp[1]=fopen("data2.txt","w");
  fp[2]=fopen("data3.txt","w");
  fp[3]=fopen("data4.txt","w");
  fp[4]=fopen("data5.txt","w");
  fp[5]=fopen("data6.txt","w");
  fp[6]=fopen("data7.txt","w");

 
  sigma = FWHM / (2.0*sqrt(log(2.0)));/*Computa el valor de sigma para las gaussianas*/

  A[0]= 50.0;/*Amplitudes*/
  A[1]= 30.0;
  A[2]=10.0;
  A[3]=20.0;
  A[4]=15.0;
  A[5]=40.0;
  A[6]=0.0;
  
  for (j=0; j<7; j++){
    t=-10.0;
    /*fprintf(fp[j], "Onda con amplitud %f \nAmplitude  Time \n", A[j]);*/
    for (i=0; i < 200; i++){
    t = t + 0.1;
    pulse[i]= A[j] * (1.0/(sigma*sqrt(2.0*PI))*exp(-pow(t,2)/(2.0*(pow(sigma, 2)))));        
    fprintf (fp[j], "%f \n", pulse[i]);
    
    }

  }

  for (i=0; i<7; i++)
   fclose(fp[i]);
  	 
  }
