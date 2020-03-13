


{

  gROOT->Reset();
  

  ///Create root files, run only one /////

  //TFile frs("ratescancold.root","RECREATE");
  //TNtuple rs("RS","RS", "disc:sum:input:rs");
  //rs.ReadFile("ratescancold.txt");
  //rs.Write();

  TFile fvol("voltage.root","RECREATE");
  TNtuple voltage("Voltage","Voltage", "asic:channel:disc:input:sumA:sumB:sumC");
  voltage.ReadFile("voltage.txt");
  voltage.Write();

  //Para el rate scan variando la ganancia:

  //TFile frs("ratescangain.root","RECREATE");
  //TNtuple rs("RS","RS", "ch:sum:gain:rs");
  //rs.ReadFile("ratescangain.txt");
  //rs.Write();

  TFile frs("ratescan2.root","RECREATE");
  TNtuple rs("RS","RS", "ch:sum:gain:rs");
  rs.ReadFile("ratescan2.txt");
  rs.Write();
  

  
  //////////////////////////////////////////

  //TFile a_file("ratescan.root");
  //TNtuple* rsP=(TNtuple*)a_file.Get("RS");
  //TNtuple &rs=*rsP;

  TFile b_file("voltage.root");
  TNtuple* voltageP=(TNtuple*)b_file.Get("Voltage");
  TNtuple &voltage=*voltageP;

  // Con ganancias
  
  //TFile c_file("ratescangain.root");
  //TNtuple* rsP=(TNtuple*)c_file.Get("RS");
  //TNtuple &rs=*rsP;
  
  TFile c_file("ratescan2.root");
  TNtuple* rsP=(TNtuple*)c_file.Get("RS");
  TNtuple &rs=*rsP;


  
  TCanvas *c1 = new TCanvas();
  c1->Divide(2,2);

  int here = 1;
  int channel = 4;
  

  for (int sum = 0; sum < 3; sum++){
    
    //TCanvas *c1 = new TCanvas(Form("Adder %c",sum+'A'),Form("Adder %c",sum+'A'));
    
    c1->cd(here);
    
    rs.SetMarkerStyle(24);  
    voltage.SetMarkerStyle(20);
    voltage.SetMarkerColor(2);
    
    //Dibujar los dos ratescans//////
    voltage.Draw(Form("sum%c*1000:input",sum+'A'),Form("disc == 0 && channel == %i && input",channel), "p");
    rs.Draw("rs*4.8:gain",Form("sum==%i && (ch == %i || ch == 0)",sum,channel),"p same");
    
    TH2F *h=gPad->FindObject("htemp");
    h->SetTitle(Form("ADDER %c",sum+'A'));
    h->GetXaxis()->SetTitle("Threshold[mV]");
    h->GetYaxis()->SetTitle("Input[mV]");
    
    /////////////////////
    
    /////Calcular los parametros de los fits//////////////
    TCanvas *c2 = new TCanvas();
    voltage.Draw(Form("sum%c*1000:input",sum+'A'),Form("disc == 0 && channel == %i && input < 600",channel), "p");
    TGraph *gr = gPad->FindObject("Graph");
    TFitResultPtr r=gr->Fit("pol1","qS");
    cout << "Datasheet:" << sum << "  " <<   r->Value(0) << "  " << r->Value(1) << endl;
    
    
    gPad->Modified();
    gPad->Update();
    rs.Draw("rs*4.8:gain",Form("sum==%i && (ch == %i || ch == 0) && gain",sum,channel),"p");
    TGraph *gr2 = gPad->FindObject("Graph");
    
    TFitResultPtr r2=gr2->Fit("pol1","qS");
    
    cout <<"Ratescan: " <<  sum << "  " <<  r2->Value(0) << "  " << r2->Value(1) << endl;
    
    gPad->Modified();
    gPad->Update();
    
    
    c1->cd(here);
    TPaveText *pt = new TPaveText(739.828,97.67,1017,245,"br");
    text = pt->AddText("                Offset  Gain");
    text = pt->AddText(Form("Datasheet: %2.2f  %2.2f",r->Value(0),r->Value(1)));
    text = pt->AddText(Form("Ratescan: %2.2f  %2.2f",r2->Value(0),r2->Value(1)));
    text = pt->AddText("Fit DS < 500 mV");
    // text = pt->AddText("RS Input > 100 mV");
    pt->Draw();
    here++;
   

    gPad->Modified();
    gPad->Update();
   
    
  }
  //c1->SaveAs("ratescanall_fit500.pdf");
 
  
}
