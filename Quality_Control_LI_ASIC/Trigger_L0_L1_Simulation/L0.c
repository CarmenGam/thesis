#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "Trigger.h"

#define B  0.5
#define PHE_CONV 10.0
#define FWHM 3.25
#define nFWHM 2.0
#define PI 3.14159265358979323846
#define NSBINS 10

int L0(int mode, double modeoption, int Nevents,double ATTENUATION[7], double PULSE, int printoption)
{


  int i=0, j=0, k=0, nscount,ii,jj;
  int event=0;
  int cluster=0;
  int pixel = 0;
  int Npixels =0;
  int Nclusters = 0;
  double t, tj, ti;
  double sigma;
  double integral, conv;
  double PHE[7];
  double pixels[7];
  int switches[7];
  
  double snoise; 
  double threshold = 0;
  double clipping = 60.0;
  
  char fname[100];
  
  FILE *fswitch, *fpixel;
 

 
  
  fswitch = fopen("switchesL0.txt", "r");
  
  if (fswitch == NULL)
    fprintf(stderr,"Couldn't open file switchesL0.txt");
  
  for (i=0; i<7; i++)
    {
      
      fscanf(fswitch, "%d", &switches[i]);
      
    }
  
  
  fclose(fswitch);
  
  fpixel = fopen("pixels.txt", "r");
  
  if (fswitch == NULL)
    fprintf(stderr,"Couldn't open file switchesL0.txt");
  
  for (i=0; i<7; i++)
    {
      
      fscanf(fpixel, "%d", &pixel);
      pixels[i] = 1.0 *pixel;
    }
  
  
  fclose(fswitch);
    
  for (i=0; i<7; i++){
    
    //fprintf(stderr, "%d\n",switch_status[i][j]);
    if (switches[i]==1){
      Nclusters++;
    }     
  }

  double rt[7][Nclusters]; 
  double rgain[7][Nclusters];
  
  for (cluster=0; cluster< Nclusters; cluster++){	
    for(j=0; j<7; j++){
      srand((j+1)*(cluster+1));
      rt[j][cluster] = ((rand()%200000)-100000)/100000.0;
      rgain[j][cluster] =((rand()%200000)-100000)/10000.0;
      
      // fprintf(stderr, "%f\t%f\t%d\t%d\t%d\n", rt[j][cluster],rgain[j][cluster],cluster,j,event);
      
    }
  }
 
  
  FILE *fp[Nevents*Nclusters], *fphe[Nevents*Nclusters],*fatt[Nevents*Nclusters], *fout[Nevents*Nclusters],*fadd[Nevents];

  srand(time(NULL));
  
  for (event = 0; event < Nevents; event++){
    
    double input_signal[7][200] = {0};
    double noise[7][200] = {0};
    double signal_and_noise[7][200] = {0};
    double attenuated[7][200] = {0};
    double output_signal[7][200]= {0};
    double sum[7][200] = {0};
    double sum_noise[7][200] = {0};
    
    for(ii=0; ii<7; ii++){
      
      //fprintf(stderr, "%d\n",switch_status[ii][jj]);
      if (switches[ii]==1){
	//fprintf(stderr, "%d\n",switch_status[ii][jj]);
	cluster=ii;

	///////////////////////////////////////////////////////////////////	
//////Usar esta parte del codigo si queremos leer un fichero de fotoelectrones//
	
	/* sprintf(fname, "phe[%d].txt", cluster+7*event);
	   fphe[cluster+7*event] = fopen(fname, "r");
	   
	   if (fphe == NULL)
	   fprintf(stderr, "Couldn't open file phe");
	   
	   i = 0;
	   while(!feof(fphe[cluster+7*event]))
	   {
	   fscanf(fphe[cluster+7*event],"%lf ", &PHE[i]);
	   i++;
	   }
	   fclose(fphe[cluster+7*event]);*/
	
	
	
	
	/* -------------------GENERADOR DE LAS 7 SEÑALES INICIALES DE LOS 7 PMT---------------- */
	
	
	//Pulso gaussiano cuya amplitud es el numero de Fotoelectrones recogido * 10 mV
		
	sigma = FWHM / (2.0*sqrt(log(2.0))); //Computa el valor de sigma para las gaussianas
	snoise =30/sqrt(12);//nFWHM / (2.0*sqrt(log(2.0)));
			
	for(j=0; j<7; j++){
	  for (i=0; i<200; i++){
	    noise[j][i] = randn(0,snoise);	    
	  }
	}
			
	for (j=0; j<7; j++){
	  
	  
	  	  
	  for (i=0; i< 200; i++){ 
	    ti= i*0.1-10.0;
	    //integral = 0;
	    //conv=0;
	    // tj= k*0.1-10.0;
	    
	    //input_signal[j][i] = PHE[j]*PHE_CONV*gaus(ti,0,sigma);
	    input_signal[j][i] = pixels[j]*(PULSE+rgain[j][cluster])*gaus(ti+rt[j][cluster],0,sigma);
	    
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
	
	if (printoption==1){
	  
	  sprintf(fname, "data[%d][%d].txt", event, cluster);
	  fp[cluster+Nclusters*event]=fopen(fname,"w");
   
	  if (fp[cluster+Nclusters*event] == NULL)
	    fprintf(stderr, "Couldn't open file data");
	  
	  
	  t=-10.0;
	  for (i=0; i<200; i++){
	    t=t + 0.1;
	    fprintf (fp[cluster+Nclusters*event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, signal_and_noise[0][i],signal_and_noise[1][i],signal_and_noise[2][i],signal_and_noise[3][i], signal_and_noise[4][i], signal_and_noise[5][i],signal_and_noise[6][i]);
	  }
	  
	  fclose(fp[cluster+Nclusters*event]);  
	  
	}
	
	/////////////////////////ATTENUATOR////////////////////////////////
	
	
	
	for (i=0; i<7; i++){
	  for (j=0; j< 200; j++){
	    
	    attenuated[i][j]= ATTENUATION[cluster] * signal_and_noise[i][j];
	    
	  }
	}
	
	if (printoption==1){
	  sprintf(fname, "att[%d][%d].txt", event, cluster);
	  fatt[cluster+Nclusters*event]=fopen(fname,"w");
	  
	  if (fatt[cluster+Nclusters*event] == NULL)
	    fprintf(stderr, "Couldn't open file att");
	  
	  
	  t=-10.0;
	  for (i=0; i<200; i++){
	    t=t + 0.1;
	    fprintf (fatt[cluster+Nclusters*event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, attenuated[0][i],attenuated[1][i],attenuated[2][i],attenuated[3][i], attenuated[4][i], attenuated[5][i],attenuated[6][i],ATTENUATION);
	  }
	  
	  fclose(fatt[cluster+Nclusters*event]);  
	}	
			    	
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
		nscount++;		
	      }
	    }
	    
	    for (j=0; j < 200; j++){
	      
	      if (attenuated[i][j] > threshold && nscount > NSBINS){
		output_signal[i][j] = 1;
	      }
	      else{
		
		output_signal[i][j] = 0;
	      }	      
	    }	      
	  }	  
	}
	
	if (printoption==1){
	  
	  sprintf(fname, "out[%d][%d].txt", event,cluster);
	  fout[cluster+Nclusters*event]=fopen(fname,"w");
	  
	  if (fout[cluster+Nclusters*event] == NULL)
	    fprintf(stderr, "Couldn't open file out");
	  
	  t=-10.0;
	  for (i=0; i<200; i++){
	    t=t + 0.1;
	    fprintf (fout[cluster+Nclusters*event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, output_signal[0][i],output_signal[1][i],output_signal[2][i],output_signal[3][i], output_signal[4][i], output_signal[5][i],output_signal[6][i], modeoption);
	  }
	  
	  fclose(fout[cluster+Nclusters*event]); 
	  
	}
	
	//////////////////////ADDER//////////////////////////////
	
	
	
	for (j=0; j<200; j++){
	  for(i=0; i< 7; i++){
	    
	    sum[cluster][j]+=output_signal[i][j];
	    
	  }
	}
	
	for (i=0; i<200;i++){
	  ti= i*0.1-10.0;
	  integral = 0;
	  conv=0;
	  
	  for(k=0; k < 200; k++){
	    tj= k*0.1-10.0;
	    
	    integral+=sinc(ti,tj)*0.1;
	    conv += sum[cluster][k]*sinc(ti,tj)*0.1;      
	  }
	  
	  sum[cluster][i] = conv/integral;
	  
	}
	
		
	//=========Añadimos más ruido al final de L0=================//
	

	for (j=0; j<200; j++){
	  
	  sum_noise[cluster][j] = sum[cluster][j] + randn(0,snoise);
	  
	}
	
	sprintf(fname, "adder[%d].txt", event);
	fadd[event]=fopen(fname,"w");  
	
	if (fadd[event] == NULL)
	  fprintf(stderr, "Couldn't open file adder");
	
	
	t=-10.0;
	for (k=0;k<200; k++){
	  t=t+0.1;
	  fprintf(fadd[event],"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, sum_noise[0][k],sum_noise[1][k],sum_noise[2][k],sum_noise[3][k],sum_noise[4][k],sum_noise[5][k],sum_noise[6][k]);
	}
	
	fclose(fadd[event]);
	
      }
    }   
  }
}

  
	 
