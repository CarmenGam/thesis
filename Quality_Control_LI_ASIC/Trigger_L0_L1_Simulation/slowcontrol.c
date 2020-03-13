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
#define NSBINS 10.0
#define SIGNAL_OUTPUT 3000 //Pulso asignado a la señal de salida en mV


double randn(double mu, double sigma);
double sinc (double t1, double t2);
double gaus(double x,double mu,double sigma);

int main (void)
{

  int mode, input,channel, i, j, error = 0, Nevents;
  double modeoption, ATTENUATION[7], PULSE;
  int switches[7][3]= {0};
  double th, THRESHOLD;

  FILE *fswitch;

  printf("=================================================================\n");
  printf("  Welcome to the Trigger System for CTA Camera Simulator  \n");
  printf("===============Mab Bernardos Martín==============================\n");
  printf("=================CIEMAT - 2016==================================\n");
  printf("=================================================================\n\n");

  printf(" How many events do you want to simulate? \n"); 
  printf("Number of events: ");
  scanf("%d", &Nevents);
  Nevents=Nevents;

  printf("Select voltage for input pulse[mV]:\n");
  printf("Input pulse: ");
  scanf("%lf",&PULSE);
  
  PULSE=PULSE;
  
  getchar();

  
  
  printf("The trigger System operates at two levels, L0 and L1.\n\n");
  printf("Set parameters for L0 trigger:\n");

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

   printf("Please, type the attenuation coefficient (0.6x to 1.35x) for each channel \n");
   
   for (i =0; i<7; i++){
     printf("Channel %d: ", i+1);
     scanf("%lf", &ATTENUATION[i]);

     if (ATTENUATION[i] < 0.6 || ATTENUATION[i] > 1.35){
     printf("Value out of range. Quitting\n");
     break;
     }
   }
    
   //eventgenerator(Nevents);
  
       
  }

  printf("\n\nNow please, set parameters for L1 trigger: \n");

  printf("Please, select the Mode for the trigger region (2, 3, 4). \n\n");
  printf("Mode 2: 2 clusters.\n");
  printf("Mode 3: 3 clusters.\n");
  printf("Mode 4: 4 clusters.\n\n");
  printf( "Mode: ");

  scanf("%d", &input );

  switch (input){

  case 2:
    printf("\n You have selected Mode 2. Please, now select the switches combination.\n\n");
    printf("For Set 1, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    
    printf("For Set 2, which channels do you want to open? (1,2,3,4,5,6,7)\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    
    printf("For Set 3, which channels do you want to open? (1,2,3,4,5,6,7)\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;

    break;

  case 3:

    printf("\n You have selected Mode 3. Please, now select the switches combination.\n\n");
    
    printf("For Set 1, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;


    printf("For Set 2, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;

    printf("For Set 3, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;

    

    break;

  case 4:

     printf("\n You have selected Mode 4. Please, now select the switches combination.\n\n");
    
    printf("For Set 1, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;
    printf("Forth Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][0] = 1;


    printf("For Set 2, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;
    printf("Forth Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][1] = 1;

    
    printf("For Set 3, which channels do you want to open? (1,2,3,4,5,6,7)\n\n");
    printf("First Channel: ");
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Second Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Third Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;
    printf("Forth Channel: ");  
    scanf("%d", &channel);
    switches[channel-1][2] = 1;

    break;

  default:

    printf(" Bad input, quitting!\n");
    error = 1;
    break;
  }

  if (error != 1){
  
  fswitch = fopen("switches.txt", "w");

  if (fswitch == NULL)
    fprintf(stderr,"Couldn't open file switches.txt");

  printf("This is your switches configuration: \n");
  for (i = 0; i< 7; i++){
    for(j = 0; j<3; j++){

      fprintf(fswitch, "%d ", switches[i][j]);
      printf("%d ", switches[i][j]);
    }
    fprintf(fswitch, "\n");
    printf("\n");
  }

  fclose(fswitch);
  

  printf("\n Now please, enter the Threshold voltage in mV.\n\n");
  printf("Threshold[mV]: ");

  scanf("%lf", &THRESHOLD);
  
  printf("\n Your selected Threshold[mV]: %lf \n\n", THRESHOLD);

  }

  
  
  

  //eventgenerator(Nevents);
  L0(mode, modeoption, Nevents, ATTENUATION,PULSE,1);      
  L1(THRESHOLD, Nevents,1);

  
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

