#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "ASIC.h"

#define B  0.5  //Bandwidth, 500 MHz
#define SIGNAL_OUTPUT 3000 //Pulso asignado a la señal de salida en mV
#define PHE_CONV 10.0 //Factor de conversión entre fotoelectrones y mV
#define NSBINS 10.0 // Nanosegundos * 10 que debe durar el pulso por encima del threshold para activar el trigger. Según bibliografía, 1 ns. 

#define FWHM 3.25 //Anchura a media altura en mV
#define nFWHM 2.0 //Ruido de 0.2 PHE, 2 mV
#define PI 3.14159265358979323846

int ASIC(float THRESHOLD, int Nevents)
{
  int i=0, j=0, k=0; // Contadores que voy a necesitar 
  int event;
  
  double t, tj, ti; //Tiempo 
  double sigma;
  double integral, conv;
  double PHE[7]; //Numero de fotoelectrones que recibe cada fotomultiplicador
  double input_signal[7][200] = {0}; //Señal de entrada en cada uno de los 7 Inputs 
  double snoise; // Sigma del ruido
  double noise[7][200]; 
  double signal_and_noise[7][200];

  
  double replic_signal[7][3][200]; //Cada señal de entrada se triplica
  double sum[3][200]; //Suma resultado de cada sumador
  int switch_status[7][3]; // Estado de los 21 Interruptores
    

  int out[3][200]; // Resultado de la comparación de la suma de los 3 sumadores, puede ser o 0 o 3 V 
  int output_trigger; // Decision final del trigger, o 0 o 1 

  char fname[100];

  FILE *fp[Nevents], *fadd[Nevents], *fcomp[Nevents], *fphe[Nevents], *fswitch; // Archivos que genera el programa: las señales de entrada, las salidas de los sumadores y la saluda del comparador. 
  
  // En un fichero phe.txt estan los datos de los fotoelectrones que recibe cada PMT. 

  fswitch = fopen("switches.txt", "r");

  if (fswitch == NULL)
    fprintf(stderr,"Couldn't open file switches.txt");

  for (i=0; i<7; i++)
    {
    for (j=0; j<3; j++)
      {   
	fscanf(fswitch, "%d", &switch_status[i][j]);
	
      }
    }
 

  fclose(fswitch);
  

  for (event = 0; event < Nevents; event++){

    double input_signal[7][200] = {0};
    double noise[7][200] = {0};
    double signal_and_noise[7][200] = {0};
    double replic_signal[7][3][200] = {0};
    double sum[3][200]= {0};
    double out[3][200]= {0};


    sprintf(fname, "phe[%d].txt", event);
    fphe[event] = fopen(fname, "r");
 
 
  if (fphe == NULL)
  fprintf(stderr, "Couldn't open file phe");

 

  i = 0;
  while (!feof(fphe[event]))
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
  
  /*  for(j=0; j<7; j++){
    t=-10.0;
    for(i=0; i<200; i++){
      t=t+0.1;
      fprintf(stderr, "%f\t%f\n", t, noise[j][i]);
      
    }
    }*/
    

  /////// ANCHO DE BANDA/////////////

  for (j=0; j<7; j++){
    
    for (i=0; i< 200; i++){ 
      ti= i*0.1-10.0;
      integral = 0;
      conv=0;
      for (k=0; k< 200; k++){
	  
	  tj= k*0.1-10.0;

	  integral+=sinc(ti,tj)*0.1; //La integral de la función sinc para cada delta de t, actuará como normalización.
       
	  conv += PHE[j]*PHE_CONV*gaus(tj,0,sigma)*sinc(ti,tj)*0.1;	
      }
      input_signal[j][i] = conv/integral;
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
      fprintf (fp[event], "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f \n",t, signal_and_noise[0][i],signal_and_noise[1][i],signal_and_noise[2][i],signal_and_noise[3][i], signal_and_noise[4][i], signal_and_noise[5][i],signal_and_noise[6][i],THRESHOLD);
      } 

   fclose(fp[event]);

    
  /* ----------------------------INTERRUPTORES----------------------------*/

  //La señal que llega de cada PMT se triplica y pasa por los interruptores. En principio, la configuración de interruptores debe ser tal que solo se dejen pasar tres de las 7 señales por cada interruptor. 

  for (i=0; i < 7; i++){
    for (k=0; k<200; k++){
      for (j=0; j<3; j++){
      
	if (switch_status[i][j]== 0) // Si el interruptor está apagado, la señal de salida replicada es 0.
	  replic_signal[i][j][k]= 0; // Si está encendido, la señal de salida es igual a la original. 
	else
	  replic_signal[i][j][k]=signal_and_noise[i][k];
           
      }
    }
  }



  /* -----------------SUMADORES------------------------------------*/

  //Ahora cada señal que sale de un interruptor va a su sumador correspondiente, los interruptores [i,1] van al sumador [1], los [i,2] al [2]... El resultado de la suma van a ser tres señales resultado de la suma de las combinaciones de señales iniciales que han dejado pasar los interruptores. 
  
  sprintf(fname, "adder[%d].txt", event);
  fadd[event]=fopen(fname,"w");  
   
    if (fadd[event] == NULL)
      fprintf(stderr, "Couldn't open file");
  
  for (k=0; k<200; k++)
    for(j=0; j<3; j++)
      for(i=0; i<7; i++)

	sum[j][k]+=replic_signal[i][j][k];
      
 
  t=-10.0;
  for (k=0;k<200; k++){
    t=t+0.1;
    fprintf(fadd[event],"%f\t%f\t%f\t%f\n", t, sum[0][k],sum[1][k],sum[2][k]);
      }

  fclose(fadd[event]);

  /* ------------------COMPARADORES------------------*/

  // Hay que comparar cada señal sumada con un valor de threshold y asignarle un valor de pulso de señal cuadrada, que en este caso serán 3V (3000 mV). El comparador asigna valor 0 a todos los puntos de la señal que esten por debajo del THRESHOLD, y valor 3 V a todos los puntos que estén por encima del valor del THRESHOLD. 
 
  sprintf(fname, "comp[%d].txt", event);
  fcomp[event]=fopen(fname,"w");
  
  int nscount;
 
    if (fcomp[event] == NULL)
      fprintf(stderr, "Couldn't open file");

  
for (i=0; i<3; i++){
  nscount = 0;
  for (j=0; j<200; j++){
      if (sum[i][j] > THRESHOLD)
	nscount++;  
      }     
  for (j=0; j< 200; j++){

    if (sum[i][j] > THRESHOLD && nscount++ >  NSBINS){
      out[i][j]=SIGNAL_OUTPUT;
    }
    else{

      out[i][j]=0;
    }

  }
 }


    t=-10.0;
    for (j=0; j<200; j++){
      t=t+0.1;
      fprintf(fcomp[event], "%f\t%i\t%i\t%i\n",t, out[0][j], out[1][j],out[2][j]);
    
  }

    fclose(fcomp[event]);

  /* -------------------------------- PUERTA OR -------------------------------------*/

  //La puerta OR decide si se activa el trigger L1 de la cámara. Toma los outputs del comparador y si alguno de los tres h  a superado el valor de THRESHOLD, el trigger se activa. 
  
  for (i=0; i<200 ; i++){
    if (out[0][i] || out[1][i] || out[2][i]){  
      output_trigger=1; 
     
      fprintf (stderr,"Triggered!\n");
      break;
    }
    else {
      output_trigger=0;       
    }
  }

  if (output_trigger == 0)
    fprintf (stderr,"Nothing interesring...\n");

  }
}

