#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

#define MAX_ITER 200 
#define FWHM 3.5
double randn (double mu, double sigma);

int main(void)
{

//Este programa suma ruido blanco gaussiano a una señal. 

  FILE *fsign,*fnoise, *fresult;
  
  int i = 0;
  double sigma;
  double t = -10.0;
  double signal[200];
  double noise[200];
  double result[200];

  srand(time(NULL));

  fsign = fopen("data1.txt","r");
  if (fsign == NULL)
    fprintf(stderr, "Couldn't open file");

  while (!feof(fsign))
    {
      fscanf(fsign,"%lf ", &signal[i]);
      i++;
     
    }
   fclose (fsign);
   
   fnoise = fopen("noise.txt","w");
   if (fnoise == NULL)
    fprintf(stderr, "Couldn't open file");
   
    sigma =  FWHM / (2.0*sqrt(log(2.0)));
   for (i=0; i<200; i++){
     noise[i] = randn(0,sigma);
     t=t+0.1;
     fprintf(fnoise, "%f %f\n",t, noise[i]);
     
   }
   
   fresult = fopen("signal_wnoise.txt","w");
    if (fresult == NULL)
      fprintf(stderr, "Couldn't open file");
    t=-10.0;
   for (i=0; i<200; i++){
     t=t + 0.1;
     result[i] = signal[i] + noise[i];
     fprintf(fresult, "%f %f\n",t, result[i]);    
   }

   fclose(fresult);
 
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
