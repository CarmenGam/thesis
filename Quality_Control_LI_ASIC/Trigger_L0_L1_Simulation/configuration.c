#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>
//#include "Trigger.h"

int main(void){
  
  FILE *fpixels, *fclusters, *fswitch;
  
  int input;
  int Npixels, Nclusters,i,channel,j,error;
  int pixels[7] = {0};
  int clusters[7] = {0};
  int switches[7][3]= {0};
  
  printf("============================================================================\n");
  printf("  Welcome to the configuration for Trigger System for CTA Camera Simulator  \n");
  printf("==========================Mab Bernardos Martín==============================\n");
  printf("==============================CIEMAT - 2016==================================\n");
  printf("=============================================================================\n\n");
  
  printf("The trigger System operates at two levels, L0 and L1.\n\n");
  printf("Set parameters for L0 trigger:\n");

  printf("How many pixels do you want to use in the simulation?\n");
  printf("N pixels: ");

  scanf("%d", &Npixels);
  
  for (i = 0; i<Npixels; i++){

    pixels[i] = 1;
  }
  
  getchar();

  fpixels = fopen("pixels.txt", "w");

  if (fpixels == NULL)
    fprintf(stderr,"Couldn't open file pixels.txt");
  
  
  for (i = 0; i< 7; i++){
    
    fprintf(fpixels, "%d ", pixels[i]);      
    
    fprintf(fpixels, "\n");
    
  }
  
  fclose(fpixels);
  
  printf("How many clusters do you want to use in the simulation?\n");
  printf("N clusters ");
  
  scanf("%d", &Nclusters);
  
  for (i = 0; i<Nclusters; i++){
    
    clusters[i] = 1;
  }
  
 fclusters = fopen("switchesL0.txt", "w");

  if (fclusters == NULL)
    fprintf(stderr,"Couldn't open file pixels.txt");
  
  
  for (i = 0; i< 7; i++){
    
    fprintf(fclusters, "%d ", clusters[i]);      
    
    fprintf(fclusters, "\n");
    
  }
  
  fclose(fclusters);  





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

  }
}
