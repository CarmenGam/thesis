{

  TNtuple t("t","","asic:id:slopeidA:slopeasicA:offsetidA:offsetasicA:slopeidB:slopeasicB:offsetidB:offsetasicB:slopeidC:slopeasicC:offsetidC:offsetasicC");

  
  TGraph *gr;
  t.ReadFile("adders.txt");
  
  t.Draw("slopeidB/slopeasicB:slopeidC/slopeasicC","slopeidB != 0 && slopeidB < 100 && slopeidC < 100 && slopeidC != 0");
  //t.Draw("slopeasicA:slopeasicB","slopeasicA > 0 && slopeasicB > 0" );

  int entries = t.GetEntries("slopeidB != 0 && slopeidB < 100 && slopeidC < 100 && slopeidC != 0");

  TCanvas *c = new TCanvas("Correlation","Correlation");
  //c.Divide(1,2);
  //c.cd(1);
  gr = new TGraph(entries,t.GetV2(),t.GetV1());
  gr.SetMarkerStyle(5);
  gr.SetMarkerSize(1);
  gr.SetMarkerColor(4);
  gr.SetTitle("Correlation Adder B-C");
  gr->GetXaxis()->SetTitle("Slope Adder C/Gain Adder C");
  gr->GetYaxis()->SetTitle("Slope Adder B/Gain Adder B");
  gr->GetXaxis()->SetRangeUser(20,80);
  gr->GetYaxis()->SetRangeUser(20,80);
  gr->Draw("ap");

  TFitResultPtr fit=gr->Fit("pol1","S","same");
  const double *pars=fit->GetParams();
  double p0 = pars[0];
  double p1 = pars[1];
  TF1 *f = gr->GetFunction("pol1");

  double x, y, resx[entries];
  double res[entries];
  
  for (int i = 0; i< entries; i++){
    gr->GetPoint(i, x, y);
    resx[i] = x;
    res[i] = y - f->Eval(x);
      }
  
  TGraph *r = new TGraph(30,resx,res);
  r->SetMarkerStyle(20);
  r->SetMarkerSize(0.5);
  r->GetXaxis()->SetRangeUser(20,80);
  //c.cd(2);
  //r->Draw("ap");

  gPad->Modified();
  gPad->Update();

  
}
