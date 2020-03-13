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
#define NSBINS 10

int L0(int mode, double modeoption, int Nevents, double ATTENUATION)
{

  int i=0, j=0, k=0, nscount;
  int event;
  double t, tj, ti;
  double sigma;
  double integral, conv;
  double PHE[7];
 
      
  double snoise; 
  double threshold = 0;
  double clipping = 0;
  
  char fname[100];
  
  FILE *fp[Nevents], *fphe[Nevents],*fatt[Nevents], *fout[Nevents],*fadd[Nevents];

  for (event = 0; event < Nevents; event++){

      double input_signal[7][200] = {0};
      double noise[7][200] = {0};
      double signal_and_noise[7][200] = {0};
      double attenuated[7][200] = {0};
      double output_signal[7][200]= {0};
      double sum[200] = {0};

      
      sprintf(fname, "phe[%d].txt", event);
      fphe[event] = fopen(fname, "r");

      if (fphe == NULL)
	fprintf(stderr, "Couldn't open file phe");

      i = 0;
      while(!feof(fphe[event]))
	{
	  fscanf(fphe[event],"%lf ", &PHE[i]);
	  i++;
	}
      fclose(fphe[event]);
      

    

 /* -------------------GENERADOR DE LAS 7 SEÑALES INICIALES DE LOS 7 PMT---------------- */
      
sprintf(fname, "data[%d].txt", event);
  fp[event]=fopen(fname,"w");
   
    if (fp[event] == NULL)
      fprintf(stderr, "Couldn't open file data");

//Pulso gaussiano cuya amplitud es el numero de Fotoelectrones recogido * 10 mV
 

  sigma = FWHM / (2.0*sqrt(log(2.0))); //Computa el valor de sigma para las gaussianas
  snoise = nFWHM / (2.0*sqrt(log(2.0)));

  srand(time(NULL));
 
  for(j=0; j<7; j++){
   for (i=0; i<200; i++){
     noise[j][i] = randn(0,snoise);
   }
  }
  
   /////// ANCHO DE BANDA/////////////

  for (j=0; j<7; j++){
    
    for (i=0; i< 200; i++){ 
      ti= i*0.1-10.0;
      //integral = 0;
      //conv=0;
      // tj= k*0.1-10.0;
	  
      input_signal[j][i] = PHE[j]*PHE_CONV*gaus(ti,0,sigma);


	  //for (k=0; k< 200; k++){
	


	  //tj= k*0.1-10.0;

	  //integral+=sinc(ti,tj)*0.1; //La integral de la función sinc para cada delta de t, actuará como normalización.
       
	  //conv += PHE[j]*PHE_CONV*gaus(tj,0,sigma)*sinc(ti,tj)*0.1;	
	  //}
      //input_signal[j][i] = conv/integral;
    }

     
  }
    

for (j=0;j<7;j++){
      t=-10.0;
      for (i=0; i<200; i++){
	t=t + 0.1;
	signal_and_noise[j][i]= input_signal[j][i]+noise[j][i];
      }
 }
    t=-10.0;
    for (i=0; i<200; i++){
      t=t + 0.1;
      fprintf (fp[event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, signal_and_noise[0][i],signal_and_noise[1][i],signal_and_noise[2][i],signal_and_noise[3][i], signal_and_noise[4][i], signal_and_noise[5][i],signal_and_noise[6][i]);
    }

    fclose(fp[event]);  
    

   /////////////////////////ATTENUATOR////////////////////////////////

  sprintf(fname, "att[%d].txt", event);
  fatt[event]=fopen(fname,"w");
   
    if (fatt[event] == NULL)
      fprintf(stderr, "Couldn't open file att");

   
   for (i=0; i<7; i++){
       for (j=0; j< 200; j++){

	 attenuated[i][j]= ATTENUATION * signal_and_noise[i][j];

       }
   }
   

   t=-10.0;
    for (i=0; i<200; i++){
      t=t + 0.1;
      fprintf (fatt[event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, attenuated[0][i],attenuated[1][i],attenuated[2][i],attenuated[3][i], attenuated[4][i], attenuated[5][i],attenuated[6][i],ATTENUATION);
    }

    fclose(fatt[event]);  
  
    
    
    sprintf(fname, "out[%d].txt", event);
    fout[event]=fopen(fname,"w");
   
    if (fout[event] == NULL)
      fprintf(stderr, "Couldn't open file out");

    


   //////////////////////// SUM Trigger /////////////////////////////

    clipping = modeoption;
    


   if (mode == 1){

     for (i=0; i<7; i++){
       for (j=0; j< 200; j++){

	 if (attenuated[i][j] >= clipping)
	   output_signal[i][j] = clipping;
	 else {
	   output_signal[i][j] = attenuated[i][j];

	 }      
       }
     }
   }
    
   
    /////////////////////MAJORITY///////////////////////////////

    
    threshold = modeoption;
    
    if(mode == 2) {

      for (i=0; i<7; i++){
	nscount = 0;

	for (j=0; j<200; j++){
	  
	  if (attenuated[i][j] > threshold){
	    //fprintf(stderr, "%d\n", nscount);
	    nscount++;
	    
	  }
	}

	//fprintf(stderr, "%d\t%d\n", nscount,i);
	for (j=0; j < 200; j++){

	    if (nscount > NSBINS)
	      output_signal[i][j] = attenuated[i][j];

	    else

	      output_signal[i][j] = 0;
	   
	      }
	
      }

    }

    t=-10.0;
    for (i=0; i<200; i++){
      t=t + 0.1;
      fprintf (fout[event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, output_signal[0][i],output_signal[1][i],output_signal[2][i],output_signal[3][i], output_signal[4][i], output_signal[5][i],output_signal[6][i], modeoption);
    }

    fclose(fout[event]); 
  
      
  
   //////////////////////ADDER//////////////////////////////

    sprintf(fname, "adder[%d].txt", event);
  fadd[event]=fopen(fname,"w");  
   
    if (fadd[event] == NULL)
      fprintf(stderr, "Couldn't open file adder");


   for (j=0; j<200; j++){
     for(i=0; i< 7; i++){

       sum[j]+=output_signal[i][j];

     }
   }

   for (i=0; i<200;i++){
      ti= i*0.1-10.0;
      integral = 0;
      conv=0;

     for(k=0; k < 200; k++){
       tj= k*0.1-10.0;

       integral+=sinc(ti,tj)*0.1;
       conv += sum[k]*sinc(ti,tj)*0.1;      
     }
     
     sum[i]= conv/integral;

   }
     


   t=-10.0;
  for (k=0;k<200; k++){
    t=t+0.1;
    fprintf(fadd[event],"%f\t%f\n", t, sum[k] );
  }

  fclose(fadd[event]);


      	 
    
  }

}
	 
  
	 
