#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "L0.h"

#define B  0.5
#define PHE_CONV 10.0
#define FWHM 3.25
#define nFWHM 2.0
#define PI 3.14159265358979323846
#define NSBINS 10.0

double randn(double mu, double sigma);
double sinc (double t1, double t2);
double gaus(double x,double mu,double sigma);

int main (void)
{

  int mode, input, i, j, error = 0, Nevents;
  double modeoption, ATTENUATION;

 printf("=================================================================\n");
  printf("  Welcome to the L0 Trigger System for CTA Camera Simulator  \n");
  printf("=================================================================\n\n");

  printf("Please, select the L0 trigger approach: \n");
  printf("Option 1. Sum Trigger\n");
  printf("Option 2. Majority Trigger\n\n");
  printf("Option: ");

  scanf("%d", &input);

  mode = input;
  
  switch (input){

  case 1:

    printf("\n You have selected SUM Trigger. Please, select the voltage for clipping[mV].\n");
    printf("Voltage clipping: ");
    scanf("%lf", &modeoption);
    //fprintf(stderr, "%lf", modeoption);

    break;
	    
  case 2:

    printf("\n You have selected Majority Trigger. Please, select the Threshold voltage[mV].\n");
    printf("Threshold[mV]: ");
    scanf("%lf", &modeoption);
    //fprintf(stderr, "%lf", modeoption);
    break;

    default:

    printf("Bad input, quitting!\n");
    error = 1;
    break;
  }

  if (error!=1){

   printf("Please, type the attenuation coefficient (0.6x to 1.35x) \n");
   printf("Attenuation: ");
   scanf("%lf", &ATTENUATION);
   if (ATTENUATION < 0.6 || ATTENUATION > 1.35)
     printf("Value out of range. Quitting\n");
   else {
     

  printf(" How many events do you want to simulate? \n"); 
  printf("Number of events: ");
  scanf("%d", &Nevents); 

  eventgenerator(Nevents);
  L0(mode, modeoption, Nevents, ATTENUATION);  
  
   }     
  }
}


//Generador de ruido gaussiano.

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

