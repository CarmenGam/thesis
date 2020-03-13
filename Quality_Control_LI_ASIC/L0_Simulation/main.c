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
#define ATTENUATION 0.6
#define NSBINS 10.0



double randn(double mu, double sigma);
double sinc (double t1, double t2);
double gaus(double x,double mu,double sigma);

int main(void){

  L0(2,50,5);


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

