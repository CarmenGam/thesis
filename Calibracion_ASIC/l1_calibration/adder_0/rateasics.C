{

  TNtuple t("voltage","voltage","asic:channel:disc:input:sumA:sumB:sumC");
  t.ReadFile("voltage_all.txt");

  int asics[31]={

    121, 113,  91,  119,
    93,  86,   70,
    69,  89,  100,  101,
    66,  79,  111,  105,
    112, 68,  107,  114,
    10, 105, 112,
    63,  88,  100 ,  
    99,  96,  82,
    114, 110,  102 };

  TGraph *gr[100];
  double offset[100];
  double slope[100];
  double chi2[100];
  TNtuple ntp("","","chi2:offset:slope:asic");
  
  for (int asic=0; asic < 30; asic++){
    
   int n =  t->Draw("sumA*1000:input",Form("asic==%i && channel == 4 && disc == 0",asics[asic]));
   if(n<3) continue;
   gr[asic]=new TGraph(n,t.GetV2(),t.GetV1());   
   gr[asic]->SetMarkerStyle(20);
   gr[asic]->Draw("ap");
   
   TFitResultPtr ret=gr[asic]->Fit("pol1","S","same",0,300);
   double *pars=ret->GetParams();
   offset[asic]=pars[0];
   slope[asic]=pars[1];
   chi2[asic]=ret->Chi2();
   ntp.Fill(chi2[asic],offset[asic],slope[asic],asic[asic]);

  
   
   gPad->Update();    
   gPad->Modified();
   

  }

  for (int asic=0; asic < 30; asic++){
    cout << asics[asic] <<"\t" << slope[asic] << "\t" << offset[asic] << endl;
  }
  
  ntp.Draw("slope");
  TH2F *h=gPad->FindObject("htemp");
  h->GetMean();
  


}
