void noiseanalysis()

{

  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
 
  ofstream a_file("noiseall.txt");
  double mean, RMS;
  int color[3] = {1,2,4};
  
  TCanvas *c1 = new TCanvas("Noise per channel for all ASICs","Noise per channel for all ASICs");
  TCanvas *c2 = new TCanvas("Noise for all ASICs","Noise for all ASICs");

   TCanvas *c3 = new TCanvas("Noise mean per channel","Noise mean per channel");


  c1->cd();
  asics.SetMarkerStyle(20);
  asics.SetMarkerColor(1);
  asics.Draw("noise:channel","noise < 40 && noise != 0");

  h=(TH2F*)gPad->FindObject("htemp");
  h->SetTitle("Noise per channel for all ASICs");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Noise [mV]");

  c1->SaveAs("Noise-Channel.gif");

  c2->cd();

  TMultiGraph *mg = new TMultiGraph;
  for (int disc =0; disc < 2; disc++){
    for (int sum = 0; sum < 3; sum++){ 
      for (int channel = 1; channel <= 7; channel++){

	asics.Draw("noise", Form("disc==%i && sum==%i && channel == %i && noise != 0 && noise < 40",disc,sum,channel));
	h=(TH2F*)gPad->FindObject("htemp");
	mean = h->GetMean();
	RMS = h->GetRMS();

	a_file << disc << "\t" << channel << "\t" << sum << "\t" << mean << "\t" << RMS << endl;
      }
    }
  }
	
   TNtuple *noise = new TNtuple("Noise", "Noise","channel:sum:noise:rms");

    c3->cd();
  TLegend *l=new TLegend(0.732092,0.101266,0.899713,0.278481);
  TMultiGraph *mg = new TMultiGraph;
  for (sum=0; sum < 3; sum++){
    for (channel = 1; channel <=7 ; channel++){
      
      asics.Draw("noise",Form("(noise < 40 && noise != 0) && sum==%i && channel == %i",sum,channel));
      h=(TH2F*)gPad->FindObject("htemp");
      mean = h->GetMean();
      RMS = h->GetRMS();
      noise->Fill(channel,sum,mean,RMS);    
    }
    
    noise->Draw("noise:channel:rms",Form("sum==%i && (noise < 40 && noise !=0)",sum),"goff");
    TGraphErrors *g = new TGraphErrors(noise->GetEntries("sum==%0 && (noise < 40 && noise !=0)"), noise->GetV2(), noise->GetV1(),0,noise->GetV3());
    g->SetMarkerStyle(20+sum);
    g->SetMarkerColor(color[sum]);
    l->AddEntry(g, 
		Form("Adder %c",'A'+sum),
		"p");
    mg->SetTitle("Noise mean per channel");
    mg->Add(g);
    mg->Draw("ap");

    mg->GetXaxis()->SetTitle("Channel");
    mg->GetYaxis()->SetTitle("Noise[mV]");
    
  }
  l->Draw();
  
  c3->SaveAs("Noise-ChannelMean.gif");

	
       

  
}
