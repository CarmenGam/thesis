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

void gain_disccorrelation(int printoption)

{

// Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
  
  TGraph *gr[2][7][3];
  
  int lines = asics.GetEntries();
  int Nasics = asics.GetEntries("disc==0 && channel == 1 && sum == 0");
  
  double x[Nasics], y[Nasics];
  
  double gain[lines][2][7][3];
  
  int asic, disc,discy, channel, sum;
  
  float *row_content;
  
  ofstream fcorr("gain_disc_coeff.txt");
  
  for (int irow=0; irow < lines ; irow++){
    
    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    disc = row_content[1];
    channel= row_content[2];
    sum = row_content[3];
    gain[asic][disc][channel][sum] = row_content[9];
  }
  

  for (disc = 0; disc < 2; disc++){
    for (discy = 0; discy < 2; discy++){
      for(channel = 1; channel <= 7; channel++){
	for (sum = 0; sum < 3 ; sum++){

	  
	  if (discy != disc){

	    TString t= Form("Gain Correlation Disc %i - %i, Channel %i, Adder %c",disc, discy, channel, 'A'+sum);

	     TCanvas *canvas = new TCanvas(t,t);
	    
	    for(int i=0; i< Nasics ; i++){
	      
	      x[i] = gain[i][disc][channel][sum];
	      y[i] = gain[i][discy][channel][sum];
	      
	      
	      if (x[i] == 0 || y[i]  == 0 || x[i] < 0.7||y[i] < 0.7 ){
		
		
		x[i] = 0.874;
		y[i] =0.874;
		
	      }
	    }
	    
	    gr[disc][channel][sum]= new TGraph(Nasics,x,y);
	    
	    
	    gr[disc][channel][sum]->SetTitle(t);
	    gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Gain of Disc %i",disc));
	    gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Gain of Disc %i",discy));
	    
	    gr[disc][channel][sum]->SetMarkerColor(30);
	    gr[disc][channel][sum]->SetMarkerStyle(20);
	    gr[disc][channel][sum]->SetMarkerSize(0.5);
	    
	    gr[disc][channel][sum]->Draw("ap");
	    
	    TFitResultPtr r1 = gr[disc][channel][sum]->Fit("pol1", "qS","");
	    
	    gr[disc][channel][sum]->GetFunction("pol1")->SetLineColor(30);
	    double corr = gr[disc][channel][sum]->GetCorrelationFactor();
	    double chi2= gr[disc][channel][sum]->GetFunction("pol1")->GetChisquare();
	    double ndf= gr[disc][channel][sum]->GetFunction("pol1")->GetNDF();
	    
	    gPad->Modified();
	    gPad->Update();
	    
	    
	    fcorr << channel << "\t" << sum <<  "\t" << disc << "\t" << discy << "\t" << corr << "\t" << chi2 << "\t" << ndf << endl;
	    
	    if (printoption==0){
	      canvas->SaveAs(Form("GAIN_DISCCORR-CH%iDISC%iDISC%iSUM%i.gif",channel,disc,discy,sum));
	    }
	    if (printoption==1){
	      canvas->SaveAs(Form("GAIN_DISCCORR-CH%iDISC%iDISC%iSUM%i.gif",channel,disc,discy,sum)); 
	    }	    	    
	  }
	}
      }
    }
  }
}
