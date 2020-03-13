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

void graph(int event)
{
  TFile finput(
	      Form("input_signal[%i].root", event));
 TNtuple* input=(TNtuple*)finput.Get("Input");


 TFile fatt(
	      Form("att[%i].root",event));
  TNtuple* att=(TNtuple*)fatt.Get("Attenuator");
 
    
  TFile fout(
	      Form("out[%i].root", event));
  TNtuple* out=(TNtuple*)fout.Get("Output");

  TFile fadder(
	      Form("adder[%i].root", event));
  TNtuple* adder=(TNtuple*)fadder.Get("Adder");

  TGraph *gf[7];
  int color[7] = {1,2,3,4,5,6,7};
  TString t=Form("Event %i", event);
  TCanvas *canvas= new TCanvas(t,t);
  TMultiGraph *mg = new TMultiGraph();
  TLegend *l=new TLegend(0.719,0.528,0.900202,0.898816);
  canvas->Divide(2,2);

     for (int channel=1; channel <= 7; channel++){

       input->SetLineColor(color[channel-1]);

       canvas->cd(1);
       input->SetLineColor(color[channel-1]);
       input->Draw(
		   Form("channel%i:time",channel),
		   "",
		   (channel==1?"l":"l same")

		   );

       /*TIter next(gPad->GetListOfPrimitives());
       
       TObject *who = 0;
       TObject *temp;

       while(temp=next()){ 
	 if(temp->GetName()==TString("Graph")) 
	   who=temp;
       }

       gf[channel-1]=(TGraph*)who;
       
       mg->Add(gf[channel-1]);
       

       l->AddEntry(who,
		   Form("Channel %i", channel),
		   "lc");
		   l->Draw();*/

       

       TH2F *h0 =(TH2F*)gPad->FindObject("htemp");
       h0->SetTitle(Form("Event %i", event));
       h0->GetXaxis()->SetTitle("Time[ns])");
       h0->GetYaxis()->SetTitle("Amplitude [mV])");

       /*l->AddEntry(h0,
		   Form("Channel %i",channel),
		   "lc");
		   l->Draw();*/
       
       canvas->cd(2);
       att->SetLineColor(color[channel-1]);
       att->Draw(
		   Form("channel%i:time",channel),
		   "",
		  (channel==1?"l":"l same")

		   );
       TH2F *h1 =(TH2F*)gPad->FindObject("htemp");
       h1->SetTitle("Attenuator output");
       h1->GetXaxis()->SetTitle("Time[ns])");
       h1->GetYaxis()->SetTitle("Amplitude [mV])");
       


       canvas->cd(3);
       out->SetLineColor(color[channel-1]);
       out->Draw(
		   Form("channel%i:time",channel),
		   "",
		  (channel==1?"l":"l same")

		   );

       TH2F *h2 =(TH2F*)gPad->FindObject("htemp");
       h2->SetTitle("Trigger option output");
       h2->GetXaxis()->SetTitle("Time[ns])");
       h2->GetYaxis()->SetTitle("Amplitude [mV])");
       
       gPad->Modified();
       gPad->Update();
        
   
     }
     
    
     
    
     
       canvas->cd(4);
       adder->SetLineColor(color[3]);
       adder->Draw("sum:time","","l");

       TH2F *h3 =(TH2F*)gPad->FindObject("htemp");
       h3->SetTitle("Adder output to L1");
       h3->GetXaxis()->SetTitle("Time[ns]");
       h3->GetYaxis()->SetTitle("Amplitude [mV]");
      
      gPad->Modified();
       gPad->Update();
     
       canvas->SaveAs("SumTrigger.pdf");
       
      
        



  
  /*
  int lines = input->GetEntries();

  float time[lines], channel1[lines], channel2[lines], channel3[lines], channel4[lines], channel5[lines], channel6[lines], channel7[lines], threshold[lines];

  float* row_content;
  int irow;

  for(irow=0; irow<lines;++irow){

    input->GetEntry(irow);
    row_content = input->GetArgs();
    time[irow] = row_content[0];
    channel1[irow] = row_content[1];
    channel2[irow] = row_content[2];
    channel3[irow] = row_content[3];  
    channel4[irow] = row_content[4];
    channel5[irow] = row_content[5];
    channel6[irow] = row_content[6];
    channel7[irow] = row_content[7];
    

    // cout << time[irow] << "   " << threshold[irow] << endl;
  }

  
  



  
    
  }
  
  float comp1[lines], comp2[lines], comp3[lines];

  for (irow=0; irow < lines; irow++){
    
    comp->GetEntry(irow);
    row_content = comp->GetArgs();
    comp1[irow] = row_content[1];
    comp2[irow] = row_content[2];
    comp3[irow] = row_content[3];

    //  cout << time[irow] << "   " << comp3[irow] << endl;
    
  }

  TCanvas *c1 = new TCanvas(Form("Event %i", event),Form("Event %i", event), 1500,1000);
  
  c1->Divide(2,2);
  
  c1->cd(1);
  TMultiGraph *mg1 = new TMultiGraph();

  TGraphErrors *gr0 = new TGraphErrors(lines,time,threshold,0,0);

   gr0->SetLineColor(9);
   gr0->SetLineWidth(2);
   gr0->SetMarkerStyle(1);
   mg1->Add(gr0);

  TGraphErrors *gr1 = new TGraphErrors(lines, time, channel1,0,0);

   gr1->SetMarkerColor(1);
   gr1->SetLineColor(1);
   gr1->SetLineWidth(1);
   gr1->SetMarkerStyle(1);
   mg1->Add(gr1);

   TGraphErrors *gr2 = new TGraphErrors(lines, time, channel2,0,0);

   gr2->SetMarkerColor(2);
   gr2->SetLineColor(2);
   gr2->SetMarkerStyle(1);
   mg1->Add(gr2);

    TGraphErrors *gr3 = new TGraphErrors(lines, time, channel3,0,0);

   gr3->SetMarkerColor(3);
   gr3->SetLineColor(3);
   gr3->SetMarkerStyle(1);
   mg1->Add(gr3);

   TGraphErrors *gr4 = new TGraphErrors(lines, time, channel4,0,0);

   gr4->SetMarkerColor(4);
   gr4->SetLineColor(4);
   gr4->SetMarkerStyle(1);
   mg1->Add(gr4);

   TGraphErrors *gr5 = new TGraphErrors(lines, time, channel5,0,0);

   gr5->SetMarkerColor(5);
   gr5->SetLineColor(5);
   gr5->SetMarkerStyle(1);
   mg1->Add(gr5);

   TGraphErrors *gr6 = new TGraphErrors(lines, time, channel6,0,0);

   gr6->SetMarkerColor(6);
   gr6->SetLineColor(6);
   gr6->SetMarkerStyle(1);
   mg1->Add(gr6);

   TGraphErrors *gr7 = new TGraphErrors(lines, time, channel7,0,0);

   gr7->SetMarkerColor(7);
   gr7->SetLineColor(7);
   gr7->SetMarkerStyle(1);
   mg1->Add(gr7);


    mg1->Draw("lap1");
    mg1->SetTitle("Input Signals");
    mg1->GetXaxis()->SetTitle("Time(ns)");
    mg1->GetYaxis()->SetTitle("Amplitude(mV)");

    TLegend leg1(.72,0.396559,.899758,.901);
    leg1.SetFillColor(0);
    leg1.AddEntry(gr0,"Threshold","l");
    leg1.AddEntry(gr1,"Channel 1","l");
    leg1.AddEntry(gr2,"Channel 2", "l");
    leg1.AddEntry(gr3,"Channel 3","l");
    leg1.AddEntry(gr4,"Channel 4","l");
    leg1.AddEntry(gr5,"Channel 5","l");
    leg1.AddEntry(gr6,"Channel 6","l");
    leg1.AddEntry(gr7,"Channel 7","l");
    

    leg1.DrawClone();

    gPad->Update();
    gPad->Modified();

  
    c1->cd(2);
  TMultiGraph *mg2 = new TMultiGraph();
  mg2->Add(gr0);
   TGraphErrors *gr8 = new TGraphErrors(lines, time, adderA,0,0);

   gr8->SetLineColor(1);
   gr8->SetLineWidth(1);
   gr8->SetMarkerStyle(1);
   mg2->Add(gr8);
   
   TGraphErrors *gr9 = new TGraphErrors(lines, time, adderB,0,0);

   gr9->SetLineColor(2);
   gr9->SetLineWidth(1);
   gr9->SetMarkerStyle(1);
   mg2->Add(gr9);

   TGraphErrors *gr10 = new TGraphErrors(lines, time, adderC,0,0);

   gr10->SetLineColor(4);
   gr10->SetLineWidth(1);
   gr10->SetMarkerStyle(1);
   mg2->Add(gr10);


    mg2->Draw("lap1");
    mg2->SetTitle("Adder outputs");
    mg2->GetXaxis()->SetTitle("Time(ns)");
    mg2->GetYaxis()->SetTitle("Amplitude(mV)");

    TLegend leg2(.72,0.64,.899758,.8999);
    leg2.SetFillColor(0);
    leg2.AddEntry(gr0,"Threshold","l");
    leg2.AddEntry(gr8,"Adder A","l");
    leg2.AddEntry(gr9,"Adder B", "l");
    leg2.AddEntry(gr10,"Adder C", "l");
    

    leg2.DrawClone();

    gPad->Update();
    gPad->Modified();

    c1->cd(3);

   TMultiGraph *mg3 = new TMultiGraph();
   mg3->Add(gr0);
   TGraphErrors *gr11 = new TGraphErrors(lines, time, comp1,0,0);

   gr11->SetLineColor(1);
   gr11->SetLineWidth(1);
   gr11->SetMarkerStyle(1);
   mg3->Add(gr11);

   TGraphErrors *gr12 = new TGraphErrors(lines, time, comp2,0,0);

   gr12->SetLineColor(2);
   gr12->SetLineWidth(1);
   gr12->SetMarkerStyle(1);
   mg3->Add(gr12);

   TGraphErrors *gr13 = new TGraphErrors(lines, time, comp3,0,0);

    gr13->SetLineColor(4);
    gr13->SetLineWidth(1);
    gr13->SetMarkerStyle(1);
    mg3->Add(gr13);

    mg3->Draw("lap1");
    mg3->SetTitle("Discriminator Output");
    mg3->GetXaxis()->SetTitle("Time(ns)");
    mg3->GetYaxis()->SetTitle("Amplitude(mV)");

    TLegend leg3(.671,0.74833,.89846,.902162);
    leg3.SetFillColor(0);
    leg3.AddEntry(gr0,"Threshold","l");
    leg3.AddEntry(gr11,"Discriminator 1","l");
    leg3.AddEntry(gr12,"Discriminator 2", "l");
    leg3.AddEntry(gr13,"Discriminator 3", "l");
    

    leg3.DrawClone();

    gPad->Update();
    gPad->Modified();

    c1->SaveAs(Form("event%i.pdf",event));
    c1->SaveAs(Form("event%i.gif",event));*/


}










  





      





