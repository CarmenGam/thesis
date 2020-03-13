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

{

 // Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->

  TGraph *gr[2][7][3];
  TGraph *gr2[2][7][3];
  
  int lines = asics.GetEntries();
  int Nasics = asics.GetEntries("disc==0 && channel == 0 && sum == 0");

  double x[Nasics], y[Nasics], x2[Nasics], y2[Nasics];

  double off[lines][2][7][3];
  double diff[lines][2][7][3];
  
  ofstream a_file ("badpoints.txt");

  int asic, disc, channel, sum, channely;

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

   

    if ((row_content[4] > 45.) || (row_content[4] < -55.)){

      /* cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;*/
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      
      }

 if ((row_content[9] < 0.7) || (row_content[9] > 1.0)){

      /* cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;*/
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;

 }


    
    //cout << off[asic][disc][channel][sum] << endl;
  }


  
for (disc = 0; disc < 2; disc++){
  for (channel = 0; channel < 7 ; channel++){

    for (channely = 0; channely < 7; channely++){

      if (channely != channel){
	
	for ( sum = 0; sum < 3 ; sum++){
	 
	TString t= Form("Fit Offset, Channel %i - %i Disc %i Adder %c",channel,channely, disc,'A'+sum);
	TString t1= Form("Fit Offset, Channel %i - %i Disc %i Adder %c",channel,channely, disc,'A'+sum);
	TString t2= Form("Fit Offset-Analog Offset, Channel %i - %i Disc %i Adder %c",channel,channely, disc,'A'+sum);
	TCanvas *canvas = new TCanvas(t,t,1000,600);
		canvas->Divide(2,1);


		
	for(int i=0; i< Nasics ; i++){

	  x[i] = off[i+61][disc][channel][sum];
	  y[i] = off[i+61][disc][channely][sum];
	  x2[i] = diff[i+61][disc][channel][sum];
	  y2[i] = diff[i+61][disc][channely][sum];
	
	  // cout<< x2[i] << ""<< y2[i] << endl;
	}
	
	
	//TMultiGraph *mg = new TMultiGraph();
	canvas->cd(1);
	TGraph *gr[disc][channel][sum]= new TGraph(Nasics,x,y);
	
	//gr[disc][channel][sum]->SetTitle(t);
	//gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
        //gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));
	gr[disc][channel][sum]->SetMarkerColor(38);
	gr[disc][channel][sum]->SetMarkerStyle(20);
	gr[disc][channel][sum]->SetMarkerSize(0.5);
	gr[disc][channel][sum]->Draw("ap");
	gr[disc][channel][sum]->SetTitle(t1);
	gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
	gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));
      	//mg->Add(gr[disc][channel][sum]);

	

	    
	//gr[disc][channel][sum]->Draw("ap");
	
	
			    
	gPad->Modified();
	gPad->Update();

	canvas->cd(2);
	TGraph *gr2[disc][channel][sum]= new TGraph(Nasics,x2,y2);
	
	
	gr2[disc][channel][sum]->SetMarkerColor(46);
	gr2[disc][channel][sum]->SetMarkerStyle(20);
	gr2[disc][channel][sum]->SetMarkerSize(0.5);
	gr2[disc][channel][sum]->Draw("ap");
	gr2[disc][channel][sum]->SetTitle(t2);
	gr2[disc][channel][sum]->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
	gr2[disc][channel][sum]->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));
      	//mg->Add(gr2[disc][channel][sum]);


	/*TLegend leg(.098,0.818,.405,.900);
    leg.SetFillColor(0);
    leg.AddEntry(gr[disc][channel][sum],"Fit Offset","p0");
    leg.AddEntry(gr2[disc][channel][sum],"Fit Offset - Analog Offset","p0");*/
    
    


    /*	mg->Draw("ap");
	mg->SetTitle(t);
	mg->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
	mg->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));*/





	//leg->Draw();
	canvas->SaveAs(Form("OFFSET-CH%iCH%iDISC%iSUM%i.png",channel,channely,disc,sum));
	//canvas->SaveAs(Form("COMBI-CH%iCH%iDISC%iSUM%i.png",channel,channely,disc,sum));

	}
      }
    }
  }
 }


}



