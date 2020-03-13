void offsetanalysis()

{

  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
 
  
  ofstream a_file("offsetall.txt");

  double mean, RMS, meandig, RMSdig, meanfit, RMSfit;
  int color[3] = {1,2,4};

  TCanvas *c1 = new TCanvas("Analog Offset per channel for all ASICs","Analog Offset per channel for all ASICs");
  TCanvas *c2 = new TCanvas("Analog Offsetl for all ASICs","Analog Offset for all ASICs");
  TCanvas *c3 = new TCanvas("Offset mean per channel", "Offset mean per channel");
  TCanvas *c4 = new TCanvas("Digital Offset per channel for all ASICs", "Offset mean per channel");
  
  


  c1->cd();
  
  asics.SetMarkerStyle(20);
  asics.SetMarkerColor(1);
  asics.Draw("analog:channel","asic < 100 || asic > 130");
  
  h=(TH2F*)gPad->FindObject("htemp");
  h->SetTitle("Analog Offset per channel for all ASICs");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Analog Offset [mV]");
  
  //c1->SaveAs("Analog-Channel.gif");

  asics.SetMarkerStyle(20);
  asics.SetMarkerColor(1);
  asics.Draw("digoffset:channel","digoffset < 40");
  
  h=(TH2F*)gPad->FindObject("htemp");
  h->SetTitle("Digital Offset per channel for all ASICs");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Digital Offset [mV]");

  // c1->SaveAs("Digital-Channel.gif");

  asics.SetMarkerStyle(20);
  asics.SetMarkerColor(1);
  asics.Draw("fitoffset:channel");
  
  h=(TH2F*)gPad->FindObject("htemp");
  h->SetTitle("Fit Offset per channel for all ASICs");
  h->GetXaxis()->SetTitle("Channel");
  h->GetYaxis()->SetTitle("Fit Offset [mV]");

  // c1->SaveAs("Fit-Channel.gif");
  


  c2->cd();

  TMultiGraph *mg = new TMultiGraph;
  for (int disc =0; disc < 2; disc++){
    for (int sum = 0; sum < 3; sum++){ 
      for (int channel = 1; channel <= 7; channel++){

       
	asics.Draw("analog", Form("disc==%i && sum==%i && channel == %i && (asic < 100 || asic > 130)",disc,sum,channel));
	h=(TH2F*)gPad->FindObject("htemp");
	mean = h->GetMean();
	RMS = h->GetRMS();

	asics.Draw("digoffset", Form("disc==%i && sum==%i && channel == %i && (digoffset > 0 && digoffset < 50)",disc,sum,channel));
	h=(TH2F*)gPad->FindObject("htemp");
	meandig = h->GetMean();
	RMSdig = h->GetRMS();
	
	asics.Draw("fitoffset", Form("disc==%i && sum==%i && channel == %i",disc,sum,channel));
	h=(TH2F*)gPad->FindObject("htemp");
	meanfit = h->GetMean();
	RMSfit = h->GetRMS();



	a_file << disc << "\t" << channel << "\t" << sum << "\t" << mean << "\t" << RMS << "\t" << meandig << "\t" << RMSdig << "\t" << meanfit << "\t" << RMSfit <<  endl; 	


      }
    }
  }
  
  TNtuple *offset = new TNtuple("Offset", "Offset","channel:sum:analog:rms");

  c3->cd();
  TLegend *l=new TLegend(0.732092,0.101266,0.899713,0.278481);
  TMultiGraph *mg = new TMultiGraph;
  for (sum=0; sum < 3; sum++){
    for (channel = 1; channel <=7 ; channel++){
      
      asics.Draw("analog",Form("(asic < 100 || asic > 130) && sum==%i && channel == %i",sum,channel));
      h=(TH2F*)gPad->FindObject("htemp");
      mean = h->GetMean();
      RMS = h->GetRMS();
      offset->Fill(channel,sum,mean,RMS);    
    }
    
    offset->Draw("analog:channel:rms",Form("sum==%i",sum),"goff");
    TGraphErrors *g = new TGraphErrors(offset->GetEntries("sum==0"), offset->GetV2(), offset->GetV1(),0,offset->GetV3());
    g->SetMarkerStyle(20+sum);
    g->SetMarkerColor(color[sum]);
    l->AddEntry(g, 
		Form("Adder %c",'A'+sum),
		"p");
    mg->SetTitle("Analog Offset mean per channel");
    mg->Add(g);
    mg->Draw("ap");

    mg->GetXaxis()->SetTitle("Channel");
    mg->GetYaxis()->SetTitle("Analog Offset[mV]");
    
  }
  l->Draw();
  
  //c3->SaveAs("Analog-ChannelMean.gif");


  TNtuple *digoffset = new TNtuple("Digoffset", "Digoffset","channel:sum:digoffset:rms");
  
  c4->cd();
  TLegend *l=new TLegend(0.732092,0.101266,0.899713,0.278481);
  TMultiGraph *mg = new TMultiGraph;
  for (sum=0; sum < 3; sum++){
    for (channel = 1; channel <=7 ; channel++){
      
      asics.Draw("digoffset",Form("digoffset < 40 && sum==%i && channel == %i",sum,channel));
      h=(TH2F*)gPad->FindObject("htemp");
      mean = h->GetMean();
      RMS = h->GetRMS();
      digoffset->Fill(channel,sum,mean,RMS);    
    }
    
    digoffset->Draw("digoffset:channel:rms",Form("sum==%i",sum),"goff");
    TGraphErrors *g = new TGraphErrors(digoffset->GetEntries("sum==0"), digoffset->GetV2(), digoffset->GetV1(),0,digoffset->GetV3());
    g->SetMarkerStyle(20+sum);
    g->SetMarkerColor(color[sum]);
    l->AddEntry(g, 
		Form("Adder %c",'A'+sum),
		"p");
    mg->SetTitle("Digital Offset mean per channel");
    mg->Add(g);
    mg->Draw("ap");

    mg->GetXaxis()->SetTitle("Channel");
    mg->GetYaxis()->SetTitle("Digital Offset[mV]");
    
  }
  l->Draw();
  
  c4->SaveAs("Digital-ChannelMean.gif");


  
  



  

   
  
}
