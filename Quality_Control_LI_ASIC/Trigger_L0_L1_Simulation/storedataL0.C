//Este Macro guarda los datos que salen del ASIC en formato root.

#include "TMath.h"
#include "TH1D.h"
#include <iostream>
#include "TNtuple.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH2F.h"
using namespace std;


void storedataL0(int event)

{
  int cluster;
  for (cluster= 0; cluster < 7; cluster++){


  TFile infile(
	       Form("input_signal[%i][%i].root",event, cluster),"RECREATE");
  TNtuple input("Input","Input","time:channel1:channel2:channel3:channel4:channel5:channel6:channel7");
    input.ReadFile(
		   Form("data[%i][%i].txt", event, cluster));
    input.Write();

     TFile fatt( 
		Form("att[%i][%i].root",event,cluster),"RECREATE");
   TNtuple att("Attenuator","Attenuator","time:channel1:channel2:channel3:channel4:channel5:channel6:channel7:attenuation");
    att.ReadFile(
		 Form("att[%i][%i].txt",event, cluster));
    att.Write();
    
    
    TFile fout(
	       Form("out[%i][%i].root",event, cluster),"RECREATE");
    TNtuple out("Output","Output","time:channel1:channel2:channel3:channel4:channel5:channel6:channel7:option");
    out.ReadFile(
		 Form("out[%i][%i].txt",event, cluster));
		  out.Write();
		  
}
		  
    TFile fadder(
		  Form("adder[%i].root",event),"RECREATE");
    TNtuple adder("Adder","Adder","time:sum1:sum2:sum3:sum4:sum5:sum6:sum7");
    adder.ReadFile(
		   Form("adder[%i].txt",event));
		  adder.Write();		  
  		  

}
