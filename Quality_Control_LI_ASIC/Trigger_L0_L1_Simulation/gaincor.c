// Este programa me ayuda a calcular la corrección que debo introducir a la ganancia debida al ancho de banda.

//Voy a generar una gaussiana sin corregir y otra corregida y voy a ver cómo varían sus amplitudes.

//Necesito saber si la corrección a la ganancia es: ¿un valor fijo?¿Un valor sumador?¿Multiplicado?¿Qué ganancia teórica tengo que introdcir en mi simulación para que la ganancia final sea como la medida real?

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "Trigger.h"

#define B  0.5
#define FWHM 3.25
#define nFWHM 2.0
#define PI 3.14159265358979323846
#define gain 0.859


double sinc (double t1, double t2);
double gaus(double x,double mu,double sigma);


int main(void)
{

double sigma;
double integral, conv;
int i=0, j=0, k=0;
double t,ti,tj;

 double signal[200] = {0};
 double bw_signal[200] = {0};

sigma = FWHM / (2.0*sqrt(log(2.0)));

for (i=0; i< 200; i++){
  ti=i*0.1-10.0;
  signal[i]=1000*gain*gaus(ti,0,sigma);

 }

 for (i=0; i< 200; i++){
  
  ti=i*0.1-10.0; 
  integral=0;
  conv=0;

  for(k=0; k< 200 ; k++){
    tj = k*0.1-10.0;
    
    integral+=sinc(ti,tj)*0.1;
    conv+= signal[k]*sinc(ti,tj)*0.1;
    
  }
  
  bw_signal[i] = conv/integral;
    
 }
 
 //t=-10;
 //for (i=0; i<200; i++){
 
   fprintf(stderr, "%f\t%f\t%f \n",t,signal[100], bw_signal[100]);
   //t=t+0.1;
   //}



}




double sinc(double t1, double t2)
{

  if (t1==t2){
    return 1;
  }
  else 
    return sin((t1-t2)*2*PI*B)/(PI*(t1-t2));
  
}

double gaus(double x,double mu,double sigma)
{
  x-=mu;
  x/=sigma;
  return exp(-0.5*x*x);

}
