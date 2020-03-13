{
  gROOT->Reset();
 
  // En primer lugar leemos las Ntuplas de las señales que vamos a representar

    TFile finput("input_signal.root");
  TNtuple* input_tupleP=(TNtuple*)finput.Get("Input");
  TNtuple &input_tuple=*input_tupleP; // Carlos is lazy, para no tener que escribir ->

    TFile fadder("adder.root");
  TNtuple* adder_tupleP=(TNtuple*)fadder.Get("Adder");
  TNtuple &adder_tuple=*adder_tupleP; // Carlos is lazy, para no tener que escribir ->
    
   TFile fcomp("comp.root");
  TNtuple* comp_tupleP=(TNtuple*)fcomp.Get("Comparator");
  TNtuple &comp_tuple=*comp_tupleP; // Carlos is lazy, para no tener que escribir ->
  

  ////////////////////////DATOS INPUT SIGNALS////////////////////////////

  int lines = input_tuple.GetEntries();

  float time[lines], channel1[lines], channel2[lines], channel3[lines], channel4[lines], channel5[lines], channel6[lines], channel7[lines], threshold[lines];

  float* row_content;

  for(int irow=0; irow<lines;++irow){

    input_tuple->GetEntry(irow);
    row_content = input_tuple.GetArgs();
    time[irow] = row_content[0];
    channel1[irow] = row_content[1];
    channel2[irow] = row_content[2];
    channel3[irow] = row_content[3];  
    channel4[irow] = row_content[4];
    channel5[irow] = row_content[5];
    channel6[irow] = row_content[6];
    channel7[irow] = row_content[7];
    threshold[irow] = row_content[8];

    // cout << time[irow] << "   " << threshold[irow] << endl;
  }

  
  float adderA[lines], adderB[lines], adderC[lines];

  for (irow=0; irow < lines; irow++){
    
    adder_tuple->GetEntry(irow);
    row_content = adder_tuple.GetArgs();
    adderA[irow] = row_content[1];
    adderB[irow] = row_content[2];
    adderC[irow] = row_content[3];

    // cout << time[irow] << "   " << adderC[irow] << endl;
    
  }
  
  float comp1[lines], comp2[lines], comp3[lines];

  for (irow=0; irow < lines; irow++){
    
    comp_tuple->GetEntry(irow);
    row_content = comp_tuple.GetArgs();
    comp1[irow] = row_content[1];
    comp2[irow] = row_content[2];
    comp3[irow] = row_content[3];

    //  cout << time[irow] << "   " << comp3[irow] << endl;
    
  }

  TCanvas *c1 = new TCanvas("ASIC","ASIC", 2000,1600);
  
  c1.Divide(2,2);
  
  c1.cd(1);
  TMultiGraph *mg1 = new TMultiGraph();

  TGraphErrors *gr0 = new TGraphErrors(lines,time,threshold,0,0);

   gr0->SetLineColor(9);
   gr0->SetLineWidth(2);
   gr0->SetMarkerStyle(1);
   mg1->Add(gr0);

  TGraphErrors *gr1 = new TGraphErrors(lines, time, channel1,0,0);

   gr1->SetMarkerColor(1);
   gr1->SetLineColor(1);
   gr1->SetLineWidth(1);
   gr1->SetMarkerStyle(1);
   mg1->Add(gr1);

   TGraphErrors *gr2 = new TGraphErrors(lines, time, channel2,0,0);

   gr2->SetMarkerColor(2);
   gr2->SetLineColor(2);
   gr2->SetMarkerStyle(1);
   mg1->Add(gr2);

    TGraphErrors *gr3 = new TGraphErrors(lines, time, channel3,0,0);

   gr3->SetMarkerColor(3);
   gr3->SetLineColor(3);
   gr3->SetMarkerStyle(1);
   mg1->Add(gr3);

   TGraphErrors *gr4 = new TGraphErrors(lines, time, channel4,0,0);

   gr4->SetMarkerColor(4);
   gr4->SetLineColor(4);
   gr4->SetMarkerStyle(1);
   mg1->Add(gr4);

   TGraphErrors *gr5 = new TGraphErrors(lines, time, channel5,0,0);

   gr5->SetMarkerColor(5);
   gr5->SetLineColor(5);
   gr5->SetMarkerStyle(1);
   mg1->Add(gr5);

   TGraphErrors *gr6 = new TGraphErrors(lines, time, channel6,0,0);

   gr6->SetMarkerColor(6);
   gr6->SetLineColor(6);
   gr6->SetMarkerStyle(1);
   mg1->Add(gr6);

   TGraphErrors *gr7 = new TGraphErrors(lines, time, channel7,0,0);

   gr7->SetMarkerColor(7);
   gr7->SetLineColor(7);
   gr7->SetMarkerStyle(1);
   mg1->Add(gr7);


    mg1->Draw("AC");
    mg1->SetTitle("Input Signals");
    mg1->GetXaxis()->SetTitle("Time(ns)");
    mg1->GetYaxis()->SetTitle("Amplitude(mV)");
    mg1->GetXaxis()->SetTitleSize(0.045);
    mg1->GetYaxis()->SetTitleSize(0.045);
    

    TLegend leg1(.720885,0.516947,.900202,.898816);
    leg1.SetFillColor(0);
    leg1.AddEntry(gr0,"Threshold","l");
    leg1.AddEntry(gr1,"Channel 1","l");
    leg1.AddEntry(gr2,"Channel 2", "l");
    leg1.AddEntry(gr3,"Channel 3","l");
    leg1.AddEntry(gr4,"Channel 4","l");
    leg1.AddEntry(gr5,"Channel 5","l");
    leg1.AddEntry(gr6,"Channel 6","l");
    leg1.AddEntry(gr7,"Channel 7","l");
    

    leg1.DrawClone();

    gPad->Update();
    gPad->Modified();

  
  c1.cd(2);
  TMultiGraph *mg2 = new TMultiGraph();
  mg2->Add(gr0);
   TGraphErrors *gr8 = new TGraphErrors(lines, time, adderA,0,0);

   gr8->SetLineColor(1);
   gr8->SetLineWidth(1);
   gr8->SetMarkerStyle(1);
   mg2->Add(gr8);
   
   TGraphErrors *gr9 = new TGraphErrors(lines, time, adderB,0,0);

   gr9->SetLineColor(2);
   gr9->SetLineWidth(1);
   gr9->SetMarkerStyle(1);
   mg2->Add(gr9);

   TGraphErrors *gr10 = new TGraphErrors(lines, time, adderC,0,0);

   gr10->SetLineColor(4);
   gr10->SetLineWidth(1);
   gr10->SetMarkerStyle(1);
   mg2->Add(gr10);


    mg2->Draw("AC");
    mg2->SetTitle("Adder outputs");
    mg2->GetXaxis()->SetTitle("Time(ns)");
    mg2->GetYaxis()->SetTitle("Amplitude(mV)");
    mg2->GetXaxis()->SetTitleSize(0.045);
    mg2->GetYaxis()->SetTitleSize(0.045);

    TLegend leg2(.719255,0.702232,.900202,.901076);
    leg2.SetFillColor(0);
    leg2.AddEntry(gr0,"Threshold","l");
    leg2.AddEntry(gr8,"Adder A","l");
    leg2.AddEntry(gr9,"Adder B", "l");
    leg2.AddEntry(gr10,"Adder C", "l");
    

    leg2.DrawClone();

    gPad->Update();
    gPad->Modified();

    c1.cd(3);

   TMultiGraph *mg3 = new TMultiGraph();
   mg3->Add(gr0);
   TGraphErrors *gr11 = new TGraphErrors(lines, time, comp1,0,0);

   gr11->SetLineColor(1);
   gr11->SetLineWidth(1);
   gr11->SetMarkerStyle(1);
   mg3->Add(gr11);

   TGraphErrors *gr12 = new TGraphErrors(lines, time, comp2,0,0);

   gr12->SetLineColor(2);
   gr12->SetLineWidth(1);
   gr12->SetMarkerStyle(1);
   mg3->Add(gr12);

   TGraphErrors *gr13 = new TGraphErrors(lines, time, comp3,0,0);

    gr13->SetLineColor(4);
    gr13->SetLineWidth(1);
    gr13->SetMarkerStyle(1);
    mg3->Add(gr13);

    mg3->Draw("AL");
    mg3->SetTitle("Discriminator Output");
    mg3->GetXaxis()->SetTitle("Time(ns)");
    mg3->GetYaxis()->SetTitle("Amplitude(mV)");
    mg3->GetXaxis()->SetTitleSize(0.045);
    mg3->GetYaxis()->SetTitleSize(0.045);

    TLegend leg3(.66383,0.71353,.900202,.898816);
    leg3.SetFillColor(0);
    leg3.AddEntry(gr0,"Threshold","l");
    leg3.AddEntry(gr11,"Discriminator 1","l");
    leg3.AddEntry(gr12,"Discriminator 2", "l");
    leg3.AddEntry(gr13,"Discriminator 3", "l");
    

    leg3.DrawClone();
    c1->SaveAs("plotsASIC.gif");

    c1->SaveAs("plotsASIC.pdf");
    
    
    
    gPad->Update();
    gPad->Modified();



}
