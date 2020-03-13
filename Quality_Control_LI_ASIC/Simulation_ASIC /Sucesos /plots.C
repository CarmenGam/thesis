

{
  #include "iostream.h"
  gInterpreter->Load("storedata.C+");
  gInterpreter->Load("graph.C+");

  int event;
  int Nevents = 0;
  char input[10000];

  cout<<"====================================================================\n";
  cout<<"This is a ROOT Macro to plot the results of the ASIC for LI Trigger\n";
 
  cout << "Decision simulator\n";
  cout<<"====================================================================\n";

  cout<<"Please, enter the number of events to plot.\n";
  cout<<"Number of events: ";
  cin.get(input, 10000);
  cin.ignore();
  Nevents = atoi(input);
  cout<< Nevents <<endl;

  if (Nevents != NULL){
  
  for (event=0; event< Nevents; event++){

    storedata(event);
    graph(event);
    
  }
  }
}
