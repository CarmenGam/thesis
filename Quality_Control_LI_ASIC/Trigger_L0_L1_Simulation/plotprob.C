#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1D.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TFitResult.h"


using namespace std;

void plotprob(double voltage)
{ 
  
  ofstream a_file("Thprob50.txt",ios::app);
  
  
  TH2F *h = new TH2F();
  
  
  
  TFile infile("probability.root","RECREATE");
  TNtuple prob("Prob","Prob","pulse:th:prob");
  prob.ReadFile(Form("prob_pulse[%.2f]mV.txt",voltage));
  prob.Write();

  TFile *ff = new TFile("treefriend.root","recreate");
  TNtuple *probF = (TNtuple*)prob.CopyTree("");
  probF->SetName("probF");
  probF->Write();


  double *p,*th;
  
  double p0, p1,p02,p12;
  double th50,th50_3;
  
  TCanvas *c1= new TCanvas("Probability","Probability");
  
  
  gPad->Modified();
  gPad->Update();
  
  
  prob.SetMarkerStyle(2);
  prob.SetMarkerSize(0.5);
  prob.SetMarkerColor(2);
  prob.Draw("prob/100:th","","p");
  
  probF->SetMarkerStyle(2);
  probF->SetMarkerColor(38);
  probF->Draw("prob/100:th","prob < 90 && prob > 10","p same");
   
  int lines = probF->GetEntries("prob < 90 && prob > 10");
  cout<<lines << endl;
  double x[3], y[3];

  for (int irow=0; irow < lines; irow++){

    p = probF->GetV1();
    th = probF->GetV2();
    cout << p[irow] << "\t" << th[irow] << endl;
  }
  
  cout << p[lines/2] << "\t" << th[lines/2] << endl;
  cout << p[lines-1] << "\t" << th[lines-1] << endl;

  x[0] = th[0];
  y[0] = p[0];

  x[1] = th[lines/2];
  y[1] = p[lines/2];

  x[2] = th[lines-1];
  y[2] = p[lines-1];

  gPad->Modified();
  gPad->Update();
  
  TGraph *g2 = new TGraph(3,x,y);
  TGraph *g = new TGraph(lines,th,p);
  TFitResultPtr r2=g2->Fit("pol1","qS","");
  TFitResultPtr r=g->Fit("pol1","qS","");
  g2->SetMarkerStyle(4);
  g2->SetMarkerSize(1.5);
  g2->SetMarkerColor(4);
  g2->Draw("p");
  
  
  p0=r->Value(0);
  p1=r->Value(1);
  p02=r2->Value(0);
  p12=r2->Value(1);  

  
  
  th50 = (0.5-p0)/p1;
  th50_3=(0.5-p02)/p12;
  
    if ( !a_file.is_open() ) {
      cout << "Cannot open file" << endl;
    }
    else {
      a_file<< voltage <<"\t"<<th50 <<"\t"<<th50_3 <<   endl;
    }
    
    
    cout << voltage <<"\t"<<th50 <<"\t"<<th50_3 <<   endl;
    a_file.close();
    
    
    h=(TH2F*)gPad->FindObject("htemp"); //Asignamos los textos de los graficos
    
    h->GetXaxis()->SetTitle("Threshold[mV]");
    h->GetYaxis()->SetTitle("Triggering probability");
    h->SetTitle("Trigger Probability");
}


