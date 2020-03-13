#include "TNtuple.h"


void plot(){
  TNtuple *dataP=new TNtuple("data","data","t:a");
  TNtuple &data=*dataP;
  data.ReadFile("data1.txt");
  data.Draw("a:t");
}
