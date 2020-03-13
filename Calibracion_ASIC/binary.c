#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>



int main(int argc, char *argv[])

{

  if (argc != 2){
    printf( "Usage: %s 'Threshold' \n", argv[0] );
    }

  else{
    //Binary Search para encontrar el Threshold que me da una probabilidad de trigger del 50%
    //Tengo 256 posibles valores de Threshold, ordenados de menor a mayor y que tienen un código hexadecimal asignado
    // Voy a crear un array de 256 elementos (1,2,3... 256), cada uno de ellos correspondiente a un Threshold.
    //Voy a hacer una búsqueda binaria en ese array tal que me devuelva el elemento que se corresponde con el Threshold que da una probabilidad del 50%
    
    double maxvol = 1224.0;
    double step = maxvol/255;
    double TH50;
    int array[256];
    int i;
    
    TH50 = atof(argv[1])/step;
    
    
    for (i=0; i<256; i++){
      
      array[i] = i;
      //fprintf(stderr,"%2.1f ",array[i]*step);
    }
    double L,R; //Variables que uso para la búsqueda binaria.
    int m;
    L=0.0;
    R=255.0;
    
    while (1){
      m=floor((L+R)/2);
      
      if (L > R){
	m=floor((L+R)/2);
      fprintf(stderr,"%2.1f  %2.1f  %d \n",L,R,m);
      fprintf(stderr,"The Threshold selected is not configurable, the closest one is: %2.1f [mV]\n",array[m]*step);
      fprintf(stderr, "The Combination is: %d  \n",array[m]); 
      {break;}
      
      }

      if (array[m] < TH50){
	L=m+1; 
	fprintf(stderr,"%2.1f  %2.1f  %d \n",L,R,m);
      }
      
      if (array[m] > TH50){
	R=m-1; 
	fprintf(stderr,"%2.1f  %2.1f  %d \n",L,R,m);
	
      }
      
      if (array[m] == TH50){
	fprintf(stderr,"%2.1f  %2.1f  %d \n",L,R,m);
	fprintf(stderr, "The Threshold is: %2.1f [mV] \n",array[m]*step); 
	fprintf(stderr, "The Combination is: %d \n",array[m]); 
	{break;}
	//return 0;
      }      
    }   
  }  
}
