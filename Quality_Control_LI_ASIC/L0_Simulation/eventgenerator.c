#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "L0.h"

int eventgenerator(int Nevents)
{

  FILE *fphe[Nevents];
  
  int phe[7];
  int i, j;
  char fname[100];
  srand(time(NULL));

  for (i=0; i<Nevents; i++){

    sprintf(fname, "phe[%d].txt", i);
    fphe[i] = fopen(fname,"w");
    if (fphe[i] == NULL)
	 fprintf(stderr, "Couldn't open file phe");
    
    for (j=0; j<7; j++){

     

       if (j==0)
       phe[j] = rand() % 121;
       else{
	 phe[j] = rand() % ((phe[0]+10)-(phe[0]-10)) + (phe[0]-10);
	 if (phe[j] < 0)
	   phe[j] = 0;
	 }

       fprintf(fphe[i], "%d ", phe[j]);

	 }
    fclose(fphe[i]);
    
  }

}
