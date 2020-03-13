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

void correlation_adders(int printoption)
{
  
  // Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
  
  TGraph *gr[2][7][3];
  TGraph *gr2[2][7][3];
  
  int lines = asics.GetEntries();
  int Nasics = asics.GetEntries("disc==0 && channel == 1 && sum == 0");
  
  double x[Nasics], y[Nasics], x2[Nasics], y2[Nasics];
  
  double off[lines][2][7][3];
  double diff[lines][2][7][3];
  
  ofstream a_file ("badpoints.txt");
  
  ofstream fcorr("fit_adders_coeff.txt");
  
  int asic, disc, channel, sum, sumy;
  
  float *row_content;
  a_file<<"#asic/disc/channel/sum/fitoffset/analogoffset/diff/gain" << endl;
  for (int irow=0; irow < lines ; irow++){
    
    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    disc = row_content[1];
    channel= row_content[2];
    sum = row_content[3];
    
    
    off[asic][disc][channel][sum] = row_content[4];
    diff[asic][disc][channel][sum] = row_content[7];
    //cout << off[asic][0][0][0] << endl;
    
    
     
    if ((row_content[4] > 40.) || (row_content[4] < -55.)){
      
      cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      
    }
    
    if ((row_content[9] < 0.7) || (row_content[9] > 1.0)){
      
      cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      
    }
    
    
    
    //cout << off[asic][disc][channel][sum] << endl;
  }

  
  
  for (disc = 0; disc < 2; disc++){
    for(channel = 1; channel <= 1; channel++){
      for (sum = 0; sum < 2 ; sum++){
	
	for (sumy = 0; sumy < 2; sumy++){
	  
	  if (sumy != sum){
	    
	    
	    
	    TString t= Form("Adder %c - %c Disc %i Channel %i",'A' + sum,'A' + sumy, disc,channel);
	    TCanvas *canvas = new TCanvas(t,t,1000,400);
	    canvas->Divide(2,1);
	    
	for(int i=0; i< Nasics ; i++){
	  
	  x[i] = off[i+61][disc][channel][sum];
	  y[i] = off[i+61][disc][channel][sumy];
	  x2[i] = diff[i+61][disc][channel][sum];
	  y2[i] = diff[i+61][disc][channel][sumy];
	  
	  // cout<< x2[i] << ""<< y2[i] << endl;
	}
	
	
	//TMultiGraph *mg = new TMultiGraph();
	canvas->cd(1);
	gr[disc][channel][sum]= new TGraph(Nasics,x,y);
	
	gr[disc][channel][sum]->SetMarkerColor(38);
	gr[disc][channel][sum]->SetMarkerStyle(20);
	gr[disc][channel][sum]->SetMarkerSize(0.5);
	gr[disc][channel][sum]->SetTitle(t);
	gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Adder %c[mV]",'A'+sum));
	gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Adder %c[mV]",'A'+sumy));
	gr[disc][channel][sum]->Draw("ap");
	
	TFitResultPtr r1 = gr[disc][channel][sum]->Fit("pol1", "qS","");
	
	gr[disc][channel][sum]->GetFunction("pol1")->SetLineColor(38);
	double corr = gr[disc][channel][sum]->GetCorrelationFactor();
	double chi2= gr[disc][channel][sum]->GetFunction("pol1")->GetChisquare();
	double ndf= gr[disc][channel][sum]->GetFunction("pol1")->GetNDF();
	
	
	
      	//mg->Add(gr[disc][channel][sum]);	
	
	gPad->Modified();
	gPad->Update();
	
	canvas->cd(2);
	gr2[disc][channel][sum]= new TGraph(Nasics,x2,y2);//Difference
	
	
	gr2[disc][channel][sum]->SetMarkerColor(46);
	gr2[disc][channel][sum]->SetMarkerStyle(25);
	gr2[disc][channel][sum]->SetTitle(t);
	gr2[disc][channel][sum]->GetXaxis()->SetTitle(Form("Adder %c[mV]",'A'+sum));
	gr2[disc][channel][sum]->GetYaxis()->SetTitle(Form("Adder %c[mV]",'A'+sumy));
	gr2[disc][channel][sum]->Draw("ap");

	TFitResultPtr r2 = gr2[disc][channel][sum]->Fit("pol1", "qS","");
	
	gr2[disc][channel][sum]->GetFunction("pol1")->SetLineColor(46);
	
	double corrdiff = gr2[disc][channel][sum]->GetCorrelationFactor();
	double chi2diff= gr2[disc][channel][sum]->GetFunction("pol1")->GetChisquare();
	double ndfdiff= gr2[disc][channel][sum]->GetFunction("pol1")->GetNDF();
	
      	//mg->Add(gr2[disc][channel][sum]);
	
	
	
	/*TLegend leg(.098,0.818,.405,.900);
	leg.SetFillColor(0);
	leg.AddEntry(gr[disc][channel][sum],"Fit Offset","p0");
	leg.AddEntry(gr2[disc][channel][sum],"Fit Offset - Analog Offset","p0");*/
	
	
	
	
	//mg->Draw("ap");
	//mg->SetTitle(t);
	//mg->GetXaxis()->SetTitle(Form("Adder %c[mV]",'A'+sum));
	//mg->GetYaxis()->SetTitle(Form("Adder %c[mV]",'A'+sumy));
	
	
	
	
	
	//leg.Draw();


	fcorr << disc << "\t" << channel <<  "\t" << sum << "\t" << sumy <<  "\t" << corrdiff << "\t" << corr << "\t" << chi2diff << "\t" << ndfdiff << "\t" << chi2 << "\t" << ndf <<  endl; 

	
	if (printoption==0){
	  canvas->SaveAs(Form("ADDERSCORR-SUM%cSUM%cCH%iDISC%i.gif",'A'+sum,'A'+sumy,channel,disc));
	}
	
	if (printoption==1){
	  canvas->SaveAs(Form("ADDERSCORR-SUM%cSUM%cCH%iDISC%i.pdf",'A'+sum,'A'+sumy,channel,disc));
	}
	  }
	}
      }
    }
  }
}






