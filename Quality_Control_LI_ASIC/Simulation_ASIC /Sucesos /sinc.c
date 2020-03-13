#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>


#define PI 3.14159265358979323846

double sinc(double x);

int main (void)
{

  fprintf(stderr, "%f\n",sinc());



}


double sinc(double x)
{

  if (x==0)
    return 1;

  return sin(x)/x;



}

