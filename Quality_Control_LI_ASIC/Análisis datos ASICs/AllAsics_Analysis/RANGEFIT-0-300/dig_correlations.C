
void dig_correlations()
{


TFile in_file("allasicsdata.root");
TNtuple* asics=(TNtuple*)in_file.Get("Asics");

//TNtuple* NfriendP=(TNtuple*)in_file.Get("Asics");
 TFile *ff = new TFile("treefriend.root","recreate");
 TNtuple *asicsF = asics->CopyTree("");
 asicsF->SetName("AF");
 asicsF->Write();
 
 TNtuple *data = new TNtuple ("Correlation", "Correlaton","digfactorch:digchi2ch:digndfch:noisefactorch:noisechi2ch:noisendfch");
 
 
 
 for (int disc = 0; disc < 2; disc ++){
   for (int sum = 0; sum < 3; sum++){
     for (int channel = 1; channel <=7; channel++){
       for (int channely = 1; channely <=7; channely++){
	 
	 if (channel!=channely){
	   
	   
	   TCanvas *c = new TCanvas();
	   asics->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel), "goff");
	   
	   asicsF->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channely), "goff");

	   TGraph *gr =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel)), asics->GetV1(), asicsF->GetV1());
	   
	   gr->GetXaxis()->SetTitle(Form("Offset of Channel %i[mV])",channel));
	   gr->GetYaxis()->SetTitle(Form("Offset of Channel %i[mV])",channely));
	   gr->SetTitle(Form("Digital Offset Correlation Channel %i - Channel %i, Disc %i, Adder %i",channel,channely,disc,sum));
	   
	   gr->SetMarkerStyle(20);
	   gr->SetMarkerSize(0.5);
	   gr->SetMarkerColor(38);
	   gr->Draw("ap");
	   
	   TFitResultPtr r= gr->Fit("pol1","qS","");
	   gr->GetFunction("pol1")->SetLineColor(38);
	   double corrdigch = gr->GetCorrelationFactor();
	   double chi2digch = gr->GetFunction("pol1")->GetChisquare();
	   double ndfdigch = gr->GetFunction("pol1")->GetNDF();

	   TCanvas *c2 = new TCanvas();

	   
	   TGraph *gr2 =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40 ",disc,sum,channel)), asics->GetV2(), asicsF->GetV2());
	   

	   gr2->GetXaxis()->SetTitle(Form("Noise of Channel %i[mV])",channel));
	   gr2->GetYaxis()->SetTitle(Form("Noise of Channel %i[mV])",channely));
	   gr2->SetTitle(Form("Noise Correlation Channel %i - Channel %i, Disc %i, Adder %i",channel,channely,disc,sum));
	   
	   
	   gr2->SetMarkerStyle(20);
	   gr2->SetMarkerSize(0.5);
	   gr2->SetMarkerColor(93);
	   gr2->Draw("ap");
	   
	   TFitResultPtr r= gr2->Fit("pol1","qS","");
	   gr2->GetFunction("pol1")->SetLineColor(93);
	   double corrnoisech = gr2->GetCorrelationFactor();
	   double chi2noisech = gr2->GetFunction("pol1")->GetChisquare();
	   double ndfnoisech = gr2->GetFunction("pol1")->GetNDF();
	   

	   data->Fill(corrdigch,chi2digch,ndfdigch,corrnoisech,chi2noisech,ndfnoisech);
	   c->SaveAs(Form("DIGOFF-CH%iCH%iDISC%iSUM%c.gif",channel,channely,disc,'A'+sum));
	   c2->SaveAs(Form("NOISE-CH%iCH%iDISC%iSUM%c.gif",channel,channely,disc,'A'+sum));
	   
	 }
       }
     }
   }
 }


 /*data->Draw("digfactorch","");

 TH2F *h=gPad->FindObject("htemp");
 cout << h->GetMean() <<"\t" << h->GetRMS() << endl;

 data->Draw("digchi2ch","");
 
 TH2F *h2=gPad->FindObject("htemp");
 cout << h2->GetMean() <<"\t" << h2->GetRMS() <<  endl;

 data->Draw("digndfch","");

 TH2F *h3=gPad->FindObject("htemp");
 cout << h3->GetMean() <<"\t" << h3->GetRMS() << endl;

 data->Draw("noisefactorch","");

 TH2F *h4=gPad->FindObject("htemp");
 cout << h4->GetMean() <<"\t" << h4->GetRMS() << endl;

 data->Draw("noisechi2ch","");

 TH2F *h5=gPad->FindObject("htemp");
 cout << h5->GetMean() <<"\t" << h5->GetRMS() << endl;

 data->Draw("noisendfch","");

 TH2F *h6=gPad->FindObject("htemp");
 cout << h6->GetMean() <<"\t" << h6->GetRMS() << endl;*/

 

 
 TNtuple *data2 = new TNtuple ("Correlation Add", "Correlaton Add","digfactoradd:digchi2add:digndfadd:noisefactoradd:noisechi2add:noisendfadd");

 for (int disc = 0; disc < 2; disc ++){
   for (int channel = 1; channel <= 7; channel++){
     for (int sum = 0; sum < 3; sum++){
       for (int sumy = 1; sumy <=1; sumy++){
	 
	 if (sum!=sumy){

	   TCanvas *c = new TCanvas();
	   asics->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel), "goff");
	   
	   asicsF->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40 ",disc,sumy,channel), "goff");
	  	   
	   	   	   
	   TGraph *gr =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel)), asics->GetV1(), asicsF->GetV1());
	   
	   gr->GetXaxis()->SetTitle(Form("Offset of Adder %c[mV])",'A'+sum));
	   gr->GetYaxis()->SetTitle(Form("Offset of Adder %c[mV])",'A'+sumy));
	   gr->SetTitle(Form("Digital Offset Correlation Adder %c - Adder %c, Disc %i, Channel %i",'A'+sum,'A'+sumy,disc,channel));
	   
	   gr->SetMarkerStyle(20);
	   gr->SetMarkerSize(0.5);
	   gr->SetMarkerColor(38);
	   gr->Draw("ap");
	   
	   TFitResultPtr r= gr->Fit("pol1","qS","");
	   gr->GetFunction("pol1")->SetLineColor(38);
	   double corrdigadd = gr->GetCorrelationFactor();
	   double chi2digadd = gr->GetFunction("pol1")->GetChisquare();
	   double ndfdigadd = gr->GetFunction("pol1")->GetNDF();

	   TCanvas *c2 = new TCanvas();
	   
	   TGraph *gr2 =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40 ",disc,sum,channel)), asics->GetV2(), asicsF->GetV2());
	   
	   gr2->GetXaxis()->SetTitle(Form("Noise of Adder %c[mV])",'A'+sum));
	   gr2->GetYaxis()->SetTitle(Form("Noise of Adder %c[mV])",'A'+sumy));
	   gr2->SetTitle(Form("Noise Correlation Adder %c - Adder %c, Disc %i, Channel %i",'A'+sum,'A'+sumy,disc,channel));
	   gr2->SetMarkerStyle(20);
	   gr2->SetMarkerSize(0.5);
	   gr2->SetMarkerColor(93);
	   gr2->Draw("ap");
	   
	   TFitResultPtr r= gr2->Fit("pol1","qS","");
	   gr2->GetFunction("pol1")->SetLineColor(93);
	   double corrnoiseadd = gr2->GetCorrelationFactor();
	   double chi2noiseadd = gr2->GetFunction("pol1")->GetChisquare();
	   double ndfnoiseadd = gr2->GetFunction("pol1")->GetNDF();

	   data2->Fill(corrdigadd,chi2digadd,ndfdigadd,corrnoiseadd,chi2noiseadd,ndfnoiseadd);
	   c->SaveAs(Form("DIGOFF-CH%iDISC%iSUM%cSUM%c.gif",channel,disc,'A'+sum,'A'+sumy));
	   c2->SaveAs(Form("NOISE-CH%iDISC%iSUM%cSUM%c.gif",channel,disc,'A'+sum,'A'+sumy));

	 }
       }
     }
   }
 }

 data2->Draw("digfactoradd","");

 /* TH2F *h=gPad->FindObject("htemp");
 cout << h->GetMean() <<"\t" << h->GetRMS() << endl;

 data2->Draw("digchi2add","");
 
 TH2F *h2=gPad->FindObject("htemp");
 cout << h2->GetMean() <<"\t" << h2->GetRMS() <<  endl;

 data2->Draw("digndfadd","");

 TH2F *h3=gPad->FindObject("htemp");
 cout << h3->GetMean() <<"\t" << h3->GetRMS() << endl;

 data2->Draw("noisefactoradd","");

 TH2F *h4=gPad->FindObject("htemp");
 cout << h4->GetMean() <<"\t" << h4->GetRMS() << endl;

 data2->Draw("noisechi2add","");

 TH2F *h5=gPad->FindObject("htemp");
 cout << h5->GetMean() <<"\t" << h5->GetRMS() << endl;

 data2->Draw("noisendfadd","");

 TH2F *h6=gPad->FindObject("htemp");
 cout << h6->GetMean() <<"\t" << h6->GetRMS() << endl;*/





 TNtuple *data3 = new TNtuple ("Correlation", "Correlaton","digfactordisc:digchi2disc:digndfdisc:noisefactordisc:noisechi2disc:noisendfdisc");
 
   for (int channel = 1; channel <= 7; channel++){
     for (int sum = 0; sum < 3; sum++){
       for (int disc = 0; disc < 2; disc ++){
	 for (int discy = 0; discy < 2; discy ++){
       

	   if (disc!=discy){
	     
	     TCanvas *c = new TCanvas();
	     asics->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel), "goff");
	     
	     asicsF->Draw("digoffset:noise",Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",discy,sum,channel), "goff");
	     
	     
	     TGraph *gr =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i  && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel)), asics->GetV1(), asicsF->GetV1());
	     
	     gr->GetXaxis()->SetTitle(Form("Offset of Disc %i[mV])",disc));
	     gr->GetYaxis()->SetTitle(Form("Offset of Disc %i[mV])",disc));
	     gr->SetTitle(Form("Digital Offset Correlation Disc %i - Disc %i, Adder %c, Channel %i",disc,discy, 'A'+sum, channel));
	     
	     gr->SetMarkerStyle(20);
	     gr->SetMarkerSize(0.5);
	     gr->SetMarkerColor(38);
	     gr->Draw("ap");
	     
	     TFitResultPtr r= gr->Fit("pol1","qS","");
	     gr->GetFunction("pol1")->SetLineColor(38);
	     double corrdigdisc = gr->GetCorrelationFactor();
	     double chi2digdisc = gr->GetFunction("pol1")->GetChisquare();
	     double ndfdigdisc = gr->GetFunction("pol1")->GetNDF();
	     
	     TCanvas *c2 = new TCanvas();
	     
	     TGraph *gr2 =  new TGraph(asics->GetEntries(Form("disc == %i && sum == %i && channel == %i && noise !=0 && digoffset !=0 && noise < 20 && digoffset < 40",disc,sum,channel)), asics->GetV2(), asicsF->GetV2());
	     
	     gr2->GetXaxis()->SetTitle(Form("Noise of Disc %i[mV])",disc));
	     gr2->GetYaxis()->SetTitle(Form("Noise of Disc %i[mV])",disc));
	     gr2->SetTitle(Form("Noise Correlation Disc %i - Disc %i, Adder %c, Channel %i",disc,discy, 'A'+sum, channel));
	     
	     gr2->SetMarkerStyle(20);
	     gr2->SetMarkerSize(0.5);
	     gr2->SetMarkerColor(93);
	     gr2->Draw("ap");
	     
	     TFitResultPtr r= gr2->Fit("pol1","qS","");
	     gr2->GetFunction("pol1")->SetLineColor(93);
	     double corrnoisedisc = gr2->GetCorrelationFactor();
	     double chi2noisedisc = gr2->GetFunction("pol1")->GetChisquare();
	     double ndfnoisedisc = gr2->GetFunction("pol1")->GetNDF();
	     

	     data3->Fill(corrdigdisc,chi2digdisc,ndfdigdisc,corrnoisedisc,chi2noisedisc,ndfnoisedisc);
	     c->SaveAs(Form("DIGOFF-CH%iSUM%cDISC%iDISC%i.gif",channel,'A'+sum,disc,discy));
	     c2->SaveAs(Form("NOISE-CH%iSUM%cDISC%iDISC%i.gif",channel,'A'+sum,disc,discy));
	     
	     
	   }
	 }
       }
     }
   }
   

   data3->Draw("digfactordisc","");

   /*TH2F *h=gPad->FindObject("htemp");
 cout << h->GetMean() <<"\t" << h->GetRMS() << endl;

 data3->Draw("digchi2disc","");
 
 TH2F *h2=gPad->FindObject("htemp");
 cout << h2->GetMean() <<"\t" << h2->GetRMS() <<  endl;

 data3->Draw("digndfdisc","");

 TH2F *h3=gPad->FindObject("htemp");
 cout << h3->GetMean() <<"\t" << h3->GetRMS() << endl;

 data3->Draw("noisefactordisc","");

 TH2F *h4=gPad->FindObject("htemp");
 cout << h4->GetMean() <<"\t" << h4->GetRMS() << endl;

 data3->Draw("noisechi2disc","");

 TH2F *h5=gPad->FindObject("htemp");
 cout << h5->GetMean() <<"\t" << h5->GetRMS() << endl;

 data3->Draw("noisendfdisc","");

 TH2F *h6=gPad->FindObject("htemp");
 cout << h6->GetMean() <<"\t" << h6->GetRMS() << endl;*/

   
 
   


 delete ff;
	 

	 


}
   

 
