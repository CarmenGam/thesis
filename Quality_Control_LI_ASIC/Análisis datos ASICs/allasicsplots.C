{
  gROOT->Reset();


 // Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
  


for (int disc=0; disc < 2; disc ++){
  for (int channel = 0; channel < 7; channel++){
    for (int sum = 0; sum < 3; sum++){
      
      TString t= Form("Channel %i Disc %i Adder %c",channel, disc,'A'+sum);
      TString t2= Form("Channel %i Disc %i Adder %c",channel, disc,'A'+sum);
      //TCanvas *generalC = new TCanvas(t,t,1500,1000);
      TCanvas *generalC = new TCanvas(t,t,1500,1000);
      generalC.Divide(1,2);
      generalC.cd(1);
      
      //TCanvas *canvas = new TCanvas(t,t);
      
      asics.Draw(
		 "diff",
		 Form("channel==%i && disc==%i && sum==%i && diff < 500.",channel, disc, sum));

      TH2F *h=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h->GetXaxis()->SetTitle("Fit Offset - Analog Offset mV");
      h->SetTitle(t);
      h->SetFillColor(46);

       gPad->Modified();
       gPad->Update();

      generalC.cd(2);

     asics.Draw(
		 "differr",
		 Form("channel==%i && disc==%i && sum==%i && differr < 500. && differr > -500",channel, disc, sum));

      TH2F *herr=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      herr->GetXaxis()->SetTitle("Fit Offset - Analog Offset/Fit Error mV");
      herr->SetTitle(t2);
      herr->SetFillColor(38);

      gPad->Modified();
      gPad->Update();

      generalC->SaveAs(Form("DISC%iCH%iSUM%c.png",disc,channel,'A'+sum));
    }
  }
 }

 



}
