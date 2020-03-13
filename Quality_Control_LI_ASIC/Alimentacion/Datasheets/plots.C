{
  gROOT->Reset();
  TFile fin("outliers.root");
  TNtuple *nt=(TNtuple*)fin.Get("nt");
  TNtuple *out=(TNtuple*)fin.Get("out");
  TFile fall("gain.root");
  TNtuple *all=(TNtuple*)fall.Get("nt");

  TCanvas *c =  new TCanvas ("c","c");
  c->Divide(2,1);
  TCanvas *c2 =  new TCanvas ("c2","c2");
  

  double mgain[5];
  double rms[5];
  double mgainall[5];
  double rmsall[5];
  double v[5];
  double nout[5];

  for (int i=0; i<5; i++){
    double volt = 3+i*0.1;
    v[i]=volt;

    TString t1 = Form("Gain for power supply = %f V",volt);
    TString t2 = Form("Outliers power supply = %f V",volt);

    out->SetLineColor(2);
    c->cd(1);
    nt->Draw("gain",Form("v > %f-0.00001 && v < %f+0.00001 && channel < 7",volt,volt));
    h=(TH2F*)gPad->FindObject("htemp");
    mgain[i] = h->GetMean();
    rms[i] = h->GetRMS();

    h->SetTitle(t1);
    h->SetFillColor(kBlue-7);
    c->cd(2);
    out->Draw("gain",Form("v > %f-0.00001 && v < %f+0.00001 && channel < 7",volt,volt));

    ho=(TH2F*)gPad->FindObject("htemp");
    ho->SetTitle(t2);
    ho->SetFillColor(kRed-7);
    if (i==3) ho->Reset();
    nout[i] = out->GetEntries(Form("v > %f-0.00001 && v < %f+0.00001 && channel < 7",volt,volt));

    c2->cd();

    all->Draw("gain",Form("v > %f-0.00001 && v < %f+0.00001 && channel < 7",volt,volt));
    hh=(TH2F*)gPad->FindObject("htemp");
    mgainall[i] = hh->GetMean();
    rmsall[i] = hh->GetRMS();
    
    c->SaveAs(Form("histogain3_%i.pdf",i));

    gPad->Update();
    gPad->Modified();
    //gPad->WaitPrimitive();

  }


  TLegend *l=new TLegend(0.522923,0.172996,0.858166,0.348101);//Leyenda, tamaño de la leyenda

  TCanvas *other = new TCanvas("other","other");
  TGraphErrors *g = new TGraphErrors(5,v,mgain,0,rms);
  TGraphErrors *gall =  new TGraphErrors(5,v,mgainall,0,rmsall);
  
  g->SetMarkerStyle(20);
  gall->SetMarkerStyle(21);
  gall->SetMarkerColor(2);
  gall->SetTitle("Gain vs power supply");
  gall->GetXaxis()->SetTitle("V (V)");
  gall->GetYaxis()->SetTitle("Gain");
  l->AddEntry(g,"Gain without outliers","lep");
  l->AddEntry(gall,"Gain with outliers","lep");
 
  gall->Draw("ap");
  g->Draw("p same");
  
  l->Draw();
  other->SaveAs("gain.pdf");

  TCanvas *co = new TCanvas("co","co");
  TGraph *go = new TGraph(5,v,nout);
  go->SetMarkerStyle(22);
  go->SetMarkerColor(2);
  go->SetMarkerSize(2);
  go->SetTitle("Number of outliers");
  go->GetXaxis()->SetTitle("V (V)");
  go->GetYaxis()->SetTitle("N of Outliers");
  go->Draw("ap");

  co->SaveAs("nouts.pdf");
}
