#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "Trigger.h"


#define B  0.5  //Bandwidth, 500 MHz
#define SIGNAL_OUTPUT 3000 //Pulso asignado a la señal de salida en mV
#define PHE_CONV 10.0 //Factor de conversión entre fotoelectrones y mV
#define NSBINS 10.0 // Nanosegundos * 10 que debe durar el pulso por encima del threshold para activar el trigger. Según bibliografía, 1 ns. 

#define FWHM 3.25 //Anchura a media altura en mV
#define nFWHM 2.0 //Ruido de 0.2 PHE, 2 mV
#define PI 3.14159265358979323846

double randn(double mu, double sigma);
double sinc (double t1, double t2);
double gaus(double x,double mu,double sigma);

int main(int argc, char *argv[])
{
    
  int Nevents,Nclusters,i;
  double Threshold;
  double ThMAX;
  double ThMIN;
  double binning;
  double ATTENUATION[7]={1,1,1,1,1,1,1};
  double PULSE;
  char fname[100];
  int printoption = 0;

  FILE *fprob;

  if ( argc != 4 ) /* argc should be 3 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s 'Number of events' 'Pulse[mV]' 'printoption(1=generate intermediate textfiles)'\n", argv[0] );
    }
    else{
      Nevents = atoi(argv[1]);
      PULSE = atof(argv[2]);
      printoption=atof(argv[3]);
      
	L0(1,60,Nevents,1,ATTENUATION,PULSE,printoption);

    }
}


 double randn (double mu, double sigma)
{

  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;

  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
     }
      
   do
     {
       U1 = -1 + ((double) rand() / RAND_MAX)*2;
       U2 = -1 + ((double) rand() / RAND_MAX)*2;
       W = pow (U1, 2) + pow (U2,2);
     }
      
   while (W >= 1 || W == 0);

      mult = sqrt((-2 * log(W)) / W);
      X1 = U1 * mult;
      X2 = U2 * mult;

      call = !call;

      return (mu + sigma * (double)X1);

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
  return exp(-0.5*x*x)/sqrt(2*PI)/sigma;

}
