{

  gROOT->Reset();
  
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->

  TFile a_file("allasicsdata.root");
  TNtuple* asicscpP=(TNtuple*)a_file.Get("Asics");
  TNtuple &asicscp=*asicscpP; // Carlos is lazy, para no tener que escribir ->

  ofstream o_file("correlation_analog_offset.txt");


  int Nasics = asics.GetEntries("sum==0 && channel == 1 && disc==0");
  cout << Nasics << endl;

  for (int sum = 0; sum < 3; sum++){

    for (int channel=1; channel <=7 ; channel++){

      for (int channely=1; channely <=7; channely++){
	
	if (channel!=channely){
	  
	  TString t=Form("Channel %i - Channel %i, sum %c",channel, channely, 'A'+sum);
	  TCanvas *c = new TCanvas(t, t);
	  
	  asics.Draw("analog",
		     Form("disc==0 && sum == %i && channel == %i",sum,channel)
		     ,"goff");
	  double  &x[Nasics]=*asics->GetV1();
	  
	  
	  asicscp.Draw("analog",
		       Form("disc==0 && sum == %i && channel == %i",sum,channely),
		       "goff"); 
	  double  &y[Nasics]=*asicscp->GetV1();
	  
	  
	  TGraph *g= new TGraph(Nasics, asics->GetV1(),asicscp->GetV1());
	  
	  TFitResultPtr r = g->Fit("pol1", "qS","");
	  double p0 = r->Value(0);
	  double p1 = r->Value(1);
	  
	  
	  double corr = g->GetCorrelationFactor();
	  
	  o_file << channel<< "\t" << channely << "\t"  << sum <<"\t"<< corr << "\t"<< p0 << "\t" << p1 << endl;
	  
	  g->SetMarkerColor(38);
	  g->SetMarkerStyle(2);
	  g->Draw("ap");
	  
	  gPad->Modified();
	  gPad->Update();
	}
      }
    }  
  }
}
