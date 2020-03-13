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



void diffcorrelation(int printoption)
{
  


 // Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->

  TGraph *gr[2][7][3];
  
  int lines = asics.GetEntries();
  int Nasics = asics.GetEntries("disc==0 && channel == 0 && sum == 0");

  double x[Nasics], y[Nasics];

  double diff[lines][2][7][3];
  
  double analog;

  int asic, disc, channel, sum, channely;

  float *row_content;

  ofstream file("badanalog.txt");

  for (int irow=0; irow < lines ; irow++){

    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    disc = row_content[1];
    channel= row_content[2];
    sum = row_content[3];
    analog = row_content[5];


    diff[asic][disc][channel][sum] = row_content[7];


    if (row_content[5] < -1 || row_content[5] > 1){

      file << asic << "\t" << analog << endl;
    }

      /*if ((row_content[7] > 500.) || (row_content[7] < -55.)){

      cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[7]<< endl;
    }
    
    //cout << diff[asic][disc][channel][sum] << endl;*/
  }


  /*
for (disc = 0; disc < 2; disc++){
  for (channel = 0; channel < 2 ; channel++){

    for (channely = 0; channely < 1; channely++){

      if (channely != channel){
	
	for ( sum = 0; sum < 3 ; sum++){

	TString t= Form("Offsets Difference, Channel %i - %i Disc %i Adder %c",channel,channely, disc,'A'+sum);
	TCanvas *canvas = new TCanvas(t,t);

	
	for(int i=0; i< Nasics ; i++){

	  x[i] = diff[i+61][disc][channel][sum];
	  y[i] = diff[i+61][disc][channely][sum];
	
	  //cout<< x[i] << ""<< y[i] << endl;
	  }
		
	TGraph *gr[disc][channel][sum]= new TGraph(Nasics,x,y);
	
	gr[disc][channel][sum]->SetTitle(t);
	gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
	gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));
	gr[disc][channel][sum]->SetMarkerColor(46);
	gr[disc][channel][sum]->SetMarkerStyle(20);
	gr[disc][channel][sum]->SetMarkerSize(0.5);
			    
	gr[disc][channel][sum]->Draw("ap");
			    
	gPad->Modified();
	gPad->Update();

	//canvas->SaveAs(Form("CH%iCH%iDISC%iSUM%i.png",channel,channely,disc,sum));

       }
      }
    }
  }
  }*/


}



