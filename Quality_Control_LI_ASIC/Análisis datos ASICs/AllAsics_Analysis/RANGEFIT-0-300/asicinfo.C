void asicinfo(){

  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP;
  
  TFile ftypo("typicalasic.root","RECREATE");
  TNtuple typical("Typical","Typical","disc:channel:sum:gain:rmsgain:analog:rmsanalog:dig:rmsdig:fit:rmsfit:noise:rmsnoise");
  typical.ReadFile("typicalasic.txt");
  typical.Write();
  
  
  int here;
  int vuelta = 0;


  for (int asic = 61; asic < 100; asic++){
    TCanvas *c1 = new TCanvas(Form("ASIC %i",asic),Form("ASIC %i",asic));
    gStyle->SetTitleFontSize(0.09);
    gStyle->SetTitleFont(62,"a");   
    gStyle->SetStatStyle(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetCanvasColor(-1);
    gStyle->SetPadColor(-1);
    gStyle->SetFrameFillColor(-1);
    gStyle->SetHistFillColor(-1);
    gStyle->SetTitleFillColor(-1);
    gStyle->SetFillColor(-1);
    gStyle->SetFillStyle(0);
    gStyle->SetStatStyle(0);
    gStyle->SetTitleStyle(0); 
    
 
   
    c1->Divide(3,6,0.0001,0.0001);
    here=1;
    for (int disc = 0; disc < 2; disc++){
      for (int sum = 0; sum < 3; sum++){
	
	c1->cd(here);
	
	
	
	
	typical.Draw("channel:gain:rmsgain",Form("sum==%i && disc==%i",sum,disc),"goff");
	
	asics.Draw("channel:gain",Form(" asic == %i && sum==%i && disc == %i",asic,sum,disc),"goff");
	
	TMultiGraph *mg = new TMultiGraph();
	TLegend *l = new TLegend(0.128885,0.703064,0.305047,0.898526);
	TGraphErrors *g = new TGraphErrors(7,typical.GetV1(),typical.GetV2(),0,typical.GetV3());
	TGraphErrors *gasic = new TGraphErrors(7, asics.GetV1(),asics.GetV2(),0,0);
	
	gasic->SetMarkerStyle(34);
	gasic->SetMarkerColor(2);
	
	g->SetMarkerStyle(4);
	g->SetMarkerSize(1);
	g->SetMarkerColor(2);
	
	mg->Add(g);
	mg->Add(gasic);
	l->AddEntry(g,"Typical","p");
	l->AddEntry(gasic,Form("ASIC %i",asic),"p");	
	
	
	mg->Draw("ap");
	mg->SetTitle(Form("ASIC #%i: GAIN FOR DISC %i, ADDER %c",asic,disc,'A'+sum));
	mg->GetYaxis()->SetTitle("Gain");
	mg->GetYaxis()->SetLabelSize(0.085);
	mg->GetYaxis()->SetLabelOffset(0.001);
	mg->GetYaxis()->SetTitleSize(0.11);
	mg->GetYaxis()->SetTitleOffset(0.4);
	mg->GetXaxis()->SetTitle("Channel");
	mg->GetXaxis()->SetLabelSize(0.09);
	mg->GetXaxis()->SetTitleSize(0.11);
	mg->GetXaxis()->SetTitleOffset(-0.5);
	
	l->Draw();
	/*
	if (here <= 3){
	if (sum==0){
	  TPaveText *pt = new TPaveText(3,0.94,4.5,0.97,"br");
	}

	if (sum==1){
	  TPaveText *pt = new TPaveText(3,0.917,4.5,0.941,"br"); 
	}

	if (sum==2){
	  TPaveText *pt = new TPaveText(3,0.94,4.5,0.97,"br"); 
	}
	text = pt->AddText(Form("ADDER %c",'A'+sum));
	pt->Draw();
	}*/
      


	gPad->Modified();
	gPad->Update();
	
	c1->cd(here+3);
	
	
	typical.Draw("channel:analog:rmsanalog",Form("sum==%i && disc==%i",sum,disc),"goff");     
	asics.Draw("channel:analog",Form(" asic == %i && sum==%i && disc == %i",asic,sum,disc),"goff");
	
	TMultiGraph *mg = new TMultiGraph();
	TLegend *l = new TLegend(0.128885,0.703064,0.305047,0.898526);
	TGraphErrors *g = new TGraphErrors(7,typical.GetV1(),typical.GetV2(),0,typical.GetV3());
	TGraphErrors *gasic = new TGraphErrors(7, asics.GetV1(),asics.GetV2(),0,0);
	gasic->SetMarkerStyle(34);
	gasic->SetMarkerColor(4);
	
	g->SetMarkerStyle(4);
	g->SetMarkerSize(1);
	g->SetMarkerColor(4);
	
	mg->Add(g);
	mg->Add(gasic);
	l->AddEntry(g,"Typical","p");
	l->AddEntry(gasic,Form("ASIC %i",asic),"p");	
	
	mg->Draw("ap");
	mg->SetTitle(Form("ASIC #%i:OFFSET FOR DISC %i, ADDER %c",asic,disc,'A'+sum));
	mg->GetYaxis()->SetTitle("Offset[mV]");
	mg->GetYaxis()->SetLabelSize(0.085);
	mg->GetYaxis()->SetLabelOffset(0.001);
	mg->GetYaxis()->SetTitleSize(0.11);
	mg->GetYaxis()->SetTitleOffset(0.4);
	mg->GetXaxis()->SetTitle("Channel");
	mg->GetXaxis()->SetLabelSize(0.09);
	mg->GetXaxis()->SetTitleSize(0.11);
	mg->GetXaxis()->SetTitleOffset(-0.5);
	l->Draw();
	
	
	gPad->Modified();
	gPad->Update();
	
	c1->cd(here+6);
	
	typical.Draw("channel:noise:rmsnoise",Form("sum==%i && disc==%i",sum,disc),"goff");     
	
	asics.Draw("channel:noise",Form(" asic == %i && sum==%i && disc == %i",asic,sum,disc),"goff");
	
	TMultiGraph *mg = new TMultiGraph();
	TLegend *l = new TLegend(0.128885,0.703064,0.305047,0.898526);
	
	TGraphErrors *g = new TGraphErrors(7,typical.GetV1(),typical.GetV2(),0,typical.GetV3());
	
	TGraphErrors *gasic = new TGraphErrors(7, asics.GetV1(),asics.GetV2(),0,0);
	gasic->SetMarkerStyle(34);
	gasic->SetMarkerColor(1);
	
	g->SetMarkerStyle(4);
	g->SetMarkerSize(1);
	g->SetMarkerColor(1);
	l->AddEntry(g,"Typical","p");
	l->AddEntry(gasic,Form("ASIC %i",asic),"p");		    	
	mg->Add(g);
	mg->Add(gasic);
	
	mg->Draw("ap");
	mg->SetTitle(Form("ASIC #%i: NOISE FOR DISC %i, ADDER %c",asic,disc,'A'+sum));
	mg->GetYaxis()->SetTitle("Noise[mV]");
	mg->GetYaxis()->SetLabelSize(0.085);
	mg->GetYaxis()->SetLabelOffset(0.001);
	mg->GetYaxis()->SetTitleSize(0.11);
	mg->GetYaxis()->SetTitleOffset(0.4);
	mg->GetXaxis()->SetTitle("Channel");
	mg->GetXaxis()->SetLabelSize(0.09);
	mg->GetXaxis()->SetTitleSize(0.11);
	mg->GetXaxis()->SetTitleOffset(-0.5);
	l->Draw();
	

		
	here++;
      }
      here = 10;
    }

    c1->SaveAs(Form("ASIC0%i.pdf",asic));
  }  
}
