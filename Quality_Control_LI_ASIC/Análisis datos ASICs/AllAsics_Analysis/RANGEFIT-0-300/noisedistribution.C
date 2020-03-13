void noisedistribution(){


  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP;

  TCanvas *c1 = new TCanvas("Noise Distribution", "Noise Distribution");
  
  TPad *pad1 = new TPad("Pad1","Pad1",0.55,0.175,0.797,0.434,0,-1,-2);

  TPad *pad2 = new TPad("Pad2","Pad2",0.366,0.510,0.620,0.769,0,-1,-2);

  float outlier;
  int asic;
  int lines = asics.GetEntries();
  float *row_content;
  float noise;

  for (int irow=0; irow < lines ; irow++){
    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    noise = row_content[12];
    
    
    if (noise > 40){
      
      cout << asic << "\t" << noise <<  endl;
    }    
  }





  c1->cd();
  asics.Draw("noise", "noise !=0 && noise < 40 ");
  h= (TH2F*)gPad->FindObject("htemp");
  h->SetTitle("Distribution of noises for all ASICs");
  h->SetFillColor(798);
  h->GetXaxis()->SetTitle("Noise [mV]");
  h->SetName("Noise");
  h->Fit("gaus");
  
  pad1->Draw();
  pad2->Draw();

  TArrow *ar1 = new TArrow(39,500,20,650,0.01,"<|");
  ar1->SetLineColor(1);
  ar1->SetLineWidth(2);
  ar1->Draw();
  
  
  TArrow *ar1 = new TArrow(39,80,33,300,0.01,"<|");
  ar1->SetLineColor(1);
  ar1->SetLineWidth(2);
  ar1->Draw();




  pad1->cd();

  asics.Draw("noise", "noise > 40 && noise < 100");
  h = (TH2F*)gPad->FindObject("htemp");
  h->Rebin(4);
  h->SetFillColor(798);
  h->GetXaxis()->SetLabelSize(0.1);
  h->GetXaxis()->SetNdivisions(5);
  h->GetXaxis()->SetTitle();
  h->GetYaxis()->SetLabelSize(0.1);
  h->GetYaxis()->SetNdivisions(5);
  h->GetXaxis()->SetTitle();
  h->SetStats(0);
  h->SetTitle();

  TPaveText *pt = new TPaveText(48,2.3,54,4.8,"br");
  text = pt->AddText(" ASIC #329 ");
  text = pt->AddText(" ASIC #437 ");
  pt->Draw();
  


  pad2->cd();

  asics.Draw("noise", "noise > 100");
  h = (TH2F*)gPad->FindObject("htemp");
  h->Rebin(4);
  h->SetFillColor(798);
  h->GetXaxis()->SetLabelSize(0.1);
  h->GetXaxis()->SetNdivisions(5);
  h->GetXaxis()->SetTitle();
  h->GetYaxis()->SetLabelSize(0.1);
  h->GetYaxis()->SetNdivisions(5);
  h->GetXaxis()->SetTitle();
  h->SetStats(0);
  h->SetTitle();

  TPaveText *pt = new TPaveText(340,0.25,353,0.75,"br");
  text = pt->AddText(" ASIC #110");
  text = pt->AddText(" ASIC #209");
  pt->Draw();

  c1->SaveAs("Noisedistrib.gif");



}
