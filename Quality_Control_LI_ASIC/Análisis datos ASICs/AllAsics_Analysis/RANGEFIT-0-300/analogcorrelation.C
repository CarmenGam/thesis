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

void analogcorrelation(int printoption)

{

  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
  
  
  TGraph *gr[7][3];
  
  
  int lines = asics.GetEntries("disc==0");
  int Nasics = asics.GetEntries("sum==0 && channel == 1 && disc==0");

  cout << Nasics << endl;
  
  double x[Nasics], y[Nasics];
  
  double analog[lines][7][3];
  
  int asic, channel, sum, channely;
  
  float *row_content;
  
  ofstream fcorr("analog_coefficients.txt");


 
  for (int irow=0; irow < lines ; irow++){

    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];    
    channel= row_content[2];
    sum = row_content[3];


    analog[asic][channel][sum] = row_content[5];   
      
  }

  
 
    for (channel = 1; channel <= 7 ; channel++){
      
      for (channely = 1; channely <= 7; channely++){
	
	if (channely != channel){
	  
	  for ( sum = 0; sum < 3 ; sum++){
	    
	    TString t= Form("Analog Offset Correlation Channel %i - %i Adder %c",channel,channely,'A'+sum);
	    
	    TCanvas *canvas = new TCanvas(t,t);
	    
	    for(int i=0; i< Nasics ; i++){
	      
	      x[i] = analog[i+61][channel][sum];
	      y[i] = analog[i+61][channely][sum];
	    }
	    
	    
	    
	    gr[channel][sum]= new TGraph(Nasics,x,y);
	    
	    gr[channel][sum]->SetMarkerColor(38);
	    gr[channel][sum]->SetMarkerStyle(20);
	    gr[channel][sum]->SetMarkerSize(0.8);
	    gr[channel][sum]->SetTitle(t);
	    gr[channel][sum]->GetXaxis()->SetTitle(Form("Offset of Channel %i[mV]",channel));
	    gr[channel][sum]->GetYaxis()->SetTitle(Form("Offset of Channel %i[mV]",channely));
	    gr[channel][sum]->Draw("ap");
	    
	    
	    TFitResultPtr r1 = gr[channel][sum]->Fit("pol1", "qS","");
	    gr[channel][sum]->GetFunction("pol1")->SetLineColor(38);

	    
	    double corr = gr[channel][sum]->GetCorrelationFactor();
	    double chi2= gr[channel][sum]->GetFunction("pol1")->GetChisquare();
	    double ndf= gr[channel][sum]->GetFunction("pol1")->GetNDF();
	


	    fcorr << sum <<  "\t" << channel << "\t" << channely <<  "\t" << corr <<"\t" << chi2 << "\t" << ndf << endl; 
	    	    
	    gPad->Modified();
	    gPad->Update();
	    
	    
	    if (printoption==0){
	      
	        canvas->SaveAs(Form("ANALOGCORR-CH%iCH%iSUM%i.gif",channel,channely,sum));
	    }
	    
	    
	    if (printoption==1){
	       canvas->SaveAs(Form("ANALOGCORR-CH%iCH%iSUM%i.pdf",channel,channely,sum));
	    }
	    
	    
	  }
	}
      }
    }
}



