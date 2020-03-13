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
#include <fstream>
using namespace std;

void gainanalysis(int printoption)

{



 // Read back the ntuple 
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
 

 ofstream a_file("gainall.txt");
  int marker[6]={20,21,22};
   int color[3]={1,2,4};
   double x[2][3][7], y[7];
   int channel,disc, sum;
   TH2F *h = new TH2F();
   TH2F *h2 = new TH2F();
   TGraph *gr[2][3];
   

  for ( disc=0; disc < 2; disc ++){
    for ( channel = 1; channel <= 7; channel++){
      for ( sum = 0; sum < 3; sum++){
	TString t= Form(" Gain, Channel %i, Disc %i Adder %c", channel, disc,'A'+sum);

	  asics.Draw(
		     "gain",
		     Form("channel==%i && disc==%i && sum==%i && gain >= 0.7 && gain <= 1.01",channel ,disc, sum));

      h=(TH2F*)gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h->GetXaxis()->SetTitle("Gain [mV]");
      h->SetTitle(t);
      h->SetFillColor(30);
      
      x[disc][sum][channel]=h->GetMean();
      y[channel-1]=channel;

      a_file << disc << "\t" << channel << "\t" << sum <<"\t" <<"\t" << x[disc][sum][channel] <<"\t"<<  h->GetRMS() << endl;
      

      gPad->Modified();
      gPad->Update();
	  

      }
    }
  }

    
      
	TString t2= Form("Gain per channel for all ASICs");
	TCanvas *c2 = new TCanvas(t2,t2);
 
	asics.SetMarkerStyle(20);
	asics.SetMarkerColor(1);
	asics.Draw("gain:channel", "gain >= 0.7 && gain <= 1.01 ");

	h2=(TH2F*)gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h2->GetXaxis()->SetTitle("Channel");
      h2->GetYaxis()->SetTitle("Gain");
      h2->SetTitle(t2);
      h2->GetXaxis()->SetRangeUser(-1,7);
      gPad->Modified();
      gPad->Update();
      
      
      if (printoption==0){
      c2->SaveAs("Gain-Channel.gif");
      }
      if (printoption==1){
      c2->SaveAs("Gain-Channel.pdf");
      }
      
  

  TFile fgain("gainstats.root","RECREATE");
  TNtuple *gainstP= new TNtuple("Gain","Gain","disc:channel:sum:mean:rms");
  TNtuple &gainst = *gainstP;
  gainst.ReadFile("gainall.txt");
  gainst.Write();

  

      TString t3=Form("Gain mean per channel for all ASICs");
      TCanvas *cgain= new TCanvas(t3,t3);
      TLegend *l=new TLegend(0.732092,0.101266,0.899713,0.278481);//Leyenda, tamaño de la leyenda
      
TMultiGraph *mg = new TMultiGraph;
      for (sum = 0; sum < 3; sum++){
	

      
	gainst.Draw("mean:channel:rms",
		   Form("sum==%i",sum),
		    "goff"
		   );  
	
	TGraphErrors *g=new TGraphErrors(gainst.GetEntries("sum==0 && disc==0"),gainst.GetV2(),gainst.GetV1(),0,gainst.GetV3());

	g->SetMarkerStyle(marker[sum]);
	g->SetMarkerColor(color[sum]);

	l->AddEntry(g, 
		    Form("Adder %c",'A'+sum),
		    "p");
	mg->Add(g);

	mg->SetTitle(t3);
	mg->Draw("ap");
	
	mg->GetXaxis()->SetTitle("Channel");
	mg->GetYaxis()->SetTitle("Gain mean");
		
      }
      l->Draw();
      
  if (printoption==0){
     cgain->SaveAs("GainMean.gif");
  }
  if (printoption==1){
     cgain->SaveAs("GainMean.pdf");
     }
  
    


}
