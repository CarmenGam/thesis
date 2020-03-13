{
  gROOT->Reset();


TFile fasics("allasicsdata.root");
TNtuple* asicsP=(TNtuple*)fasics.Get("Asics");
TNtuple asics=*asicsP;


 for (int disc=0; disc<2; disc++){
   TString t=Form("Disc %i");
   TCanvas c1 = new TCanvas(t,t);
   
   for(int sum=0; sum<3; sum++){

     asics.Draw("analog:channel",
		Form("disc==%i && adder==%
