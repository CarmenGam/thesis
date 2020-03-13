#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

#define MAX_ITER 200 

double randn (double mu, double sigma);

int main(void)
{

  FILE *rnum;
  
  rnum = fopen("num.txt","w");
  
    if (rnum == NULL)
      fprintf(stderr, "Couldn't open file");

  srand (time(NULL));
  int i;
  double random_number;
  
  for (i=0; i< MAX_ITER; i++)
    {
    random_number =  randn(0.0, 1.0);  
    fprintf(rnum,"%2.3f\n", random_number);
    }
 
  fclose(rnum);

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
