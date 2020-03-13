{
  gInterpreter->Load("macro_util.C+");


  TH1D histo;histo.SetBins(200,-10,10);
  
  for(int i=1;i<=histo.GetNbinsX();i++){
    double x=histo.GetXaxis()->GetBinCenter(i);
    histo.SetBinContent(i,200.0*gaus(x,0,2.10));

    //histo.SetBinContent(i,200.0*(fabs(x)<3.5?1:0));
  }

  TH1D c=histo;
  //  convolution(c,0.333);
  convolution(c,0.1);

}
