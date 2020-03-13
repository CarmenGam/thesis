#include "TMath.h"
#include "TH1D.h"
#include <iostream>
#include "TNtuple.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH2F.h"
#include "TPad.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TObject.h"
#include "TGraph.h"
using namespace std;

void graphL0(int event, int cluster)
{

  //===========================Store the Ntuples======================
  TNtuple *tuple[4];

  TFile finput(
	       Form("input_signal[%i][%i].root", event, cluster));
  tuple[0]=(TNtuple*)finput.Get("Input");

 TFile fatt(
	    Form("att[%i][%i].root",event, cluster));
  tuple[1]=(TNtuple*)fatt.Get("Attenuator");
    
  TFile fout(
	     Form("out[%i][%i].root", event, cluster));
  tuple[2]=(TNtuple*)fout.Get("Output");

  TFile fadder(
	      Form("adder[%i].root", event));
  tuple[3]=(TNtuple*)fadder.Get("Adder");

  
  
  //======================Definitions & Declarations========================= 
  
  
  TH2F *h[4];
  TString t=(Form("Event %i, Cluster %i", event, cluster));
  //TLegend *l=new TLegend(0.719,0.528,0.900202,0.898816);
  TCanvas *canvas= new TCanvas(t,t);
  int where = 1;
  //TObject *who=0;
  //TObject *temp;
  int color[7] = {1,2,3,4,5,6,7};
  const char *titles[] = {"Input Signal", "Attenuator Output", "Trigger approach Output", "Adder Output to L1"};

  canvas->Divide(2,2);

//=====================Draw the Ntuples=================================

for(int graf=0; graf<4; graf++){
  canvas->cd(where);

//==========The first 3 Graphs have the same elements================
  if (graf < 3){
    for (int channel=1; channel <= 7; channel++){

       
       tuple[graf]->SetLineColor(color[channel-1]);      
       tuple[graf]->Draw(
		   Form("channel%i:time",channel),
		   "",
		   (channel==1?"l":"l same")
		   

		   );
       
       
     }
  }

//========The output of the L0 is a single signal=================

  else {
    tuple[graf]->SetLineColor(2);
       tuple[graf]->Draw(
			 Form("sum%i:time",cluster+1),"","l");
  }

       h[graf]=(TH2F*)gPad->FindObject("htemp");
       h[graf]->SetTitle(titles[graf]);
       h[graf]->GetXaxis()->SetTitle("Time[ns])");
       h[graf]->GetYaxis()->SetTitle("Amplitude [mV])");
       h[graf]->GetYaxis()->SetRange(0,250);
       

       where++;

      }
}
	   
	    
 
	     
