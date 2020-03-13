{
  
  gInterpreter->Load("allasicsplots.C+");
  // gInterpreter->Load(".C+");

  int printoption,choice;
  char input[10000};
  
  
  cout<<"====================================================================\n";
  cout<<"This is a ROOT Macro to generate plots for the analysis of"<< endl;
  
  cout<<"L1 Trigger system ASIC for CTA LST Camera"<< endl;
 
  cout<<"====================================================================\n";

  cout<<"This Macro will generate a huge amount of plots, we recommend to run it in batch mode!" << endl;
  
  cout<<"Please, Select the output format." << endl;
  cout <<"Type 0 for '.gif' or 1 for '.pdf' : " << endl;
  cin.get(input,10000);
  cin.ignore();
  printoption = atoi(input);
  
  
  cout<<"Type 1 if you want to generate the plots offered. Type 0 to skip to the next option."  << endl;

  cout<<"Plot histograms for Fit Offset, Gain and Fit Offset-Analog Offset difference?: " << endl;
  cin.get(input,10000);
  cin.ignore();
  choice = atoi(input);
  if (choice==1)
    allasicsplots(printoption);
   
  cout<<"Plot the correlation of the fit offset and the offsets difference between channels, for fixed adder and discriminator?:  " << endl;
  cin.get(input,10000);
  cin.ignore();
  choice = atoi(input);
  if (choice==1){
    offcorrelation();
    cout<<"Hola!" << endl;
  }

  cout<<"Plot the correlation of the fit offset and the offsets difference between adders, for fixed channel and discriminator?: "<<endl;
 cin.get(input,10000); 
 cin.ignore();
 choice = atoi(input);
 if (choice==1){
    //correlation_adders();
    cout<<"Hola!" << endl;
 }
  cout<<"Plot the correlation of the fit offset and the offsets difference between discriminators, for fixed channel and adder?: "<<endl;
 cin.get(input,10000);
 cin.ignore();
 choice = atoi(input);

 if (choice==1){
    //correlation_disc();
    cout<<"Hola!" << endl;
 }
  cout<<"Plot the result of the analysis of the gains?" << endl;
  cin.get(input,10000);
  cin.ignore();
  choice = atoi(input);

  if (choice==1){
    //gainanalysis();
    cout<<"Hola!" << endl;
  }
  cout<<"Thank you, bye!" << endl;
  
}
