{
  gROOT->Reset();

// Read back the ntuple for Adder data
  TFile fadder("adders.root");
  TNtuple* adder_tupleP=(TNtuple*)fadder.Get("Adders");
  TNtuple &adder_tuple=*adder_tupleP; // Carlos is lazy, para no tener que escribir ->

  int lines = adder_tuple.GetEntries();
  float adders[3]={1,2,3};
  int points = 3;

  float asic, sum0_400_M2[3], sum0_800_M2[3], sum1_400_M2[3], sum1_800_M2[3],
    sum0_400_M3[3],sum0_800_M3[3], sum1_400_M3[3], sum1_800_M3[3],
    sum0_400_M4[3],sum0_800_M4[3], sum1_400_M4[3], sum1_800_M4[3];

  float* row_content;

  int i;
  

  for (int irow=0; irow<lines; ++irow){

    adder_tuple->GetEntry(irow);
    row_content = adder_tuple.GetArgs();
    asic = row_content[0];
    if (row_content[1] == 2 && row_content[2]==0 && row_content[3]==400){
      sum0_400_M2[0]=row_content[4];
      sum0_400_M2[1]=row_content[5];
      sum0_400_M2[2]=row_content[6];

    }
    
    if (row_content[1] == 2 && row_content[2]==0 && row_content[3]==800){
      sum0_800_M2[0]=row_content[4];
      sum0_800_M2[1]=row_content[5];
      sum0_800_M2[2]=row_content[6];
    
    }
    
if (row_content[1] == 2 && row_content[2]==1 && row_content[3]==400){
      sum1_400_M2[0]=row_content[4];
      sum1_400_M2[1]=row_content[5];
      sum1_400_M2[2]=row_content[6];

    }
    
    if (row_content[1] == 2 && row_content[2]==1 && row_content[3]==800){
      sum1_800_M2[0]=row_content[4];
      sum1_800_M2[1]=row_content[5];
      sum1_800_M2[2]=row_content[6];
    
    }
  

  /* for (i=0; i<3; i++)
     cout << sum0_400_M2[i] << "   " << sum0_800_M2[i]<< "  " << sum1_400_M2[i]<< "  " <<sum1_800_M2[i]<< endl;*/
    
    if (row_content[1] == 3 && row_content[2]==0 && row_content[3]==400){
      sum0_400_M3[0]=row_content[4];
      sum0_400_M3[1]=row_content[5];
      sum0_400_M3[2]=row_content[6];

    }
    
    if (row_content[1] == 3 && row_content[2]==0 && row_content[3]==800){
      sum0_800_M3[0]=row_content[4];
      sum0_800_M3[1]=row_content[5];
      sum0_800_M3[2]=row_content[6];
    
    }
    
if (row_content[1] == 3 && row_content[2]==1 && row_content[3]==400){
      sum1_400_M3[0]=row_content[4];
      sum1_400_M3[1]=row_content[5];
      sum1_400_M3[2]=row_content[6];

    }
    
    if (row_content[1] == 3 && row_content[2]==1 && row_content[3]==800){
      sum1_800_M3[0]=row_content[4];
      sum1_800_M3[1]=row_content[5];
      sum1_800_M3[2]=row_content[6];
    
    }

    if (row_content[1] == 4 && row_content[2]==0 && row_content[3]==400){
      sum0_400_M4[0]=row_content[4];
      sum0_400_M4[1]=row_content[5];
      sum0_400_M4[2]=row_content[6];

    }
    
    if (row_content[1] == 4 && row_content[2]==0 && row_content[3]==800){
      sum0_800_M4[0]=row_content[4];
      sum0_800_M4[1]=row_content[5];
      sum0_800_M4[2]=row_content[6];
    
    }
    
if (row_content[1] == 4 && row_content[2]==1 && row_content[3]==400){
      sum1_400_M4[0]=row_content[4];
      sum1_400_M4[1]=row_content[5];
      sum1_400_M4[2]=row_content[6];

    }
    
    if (row_content[1] == 4 && row_content[2]==1 && row_content[3]==800){
      sum1_800_M4[0]=row_content[4];
      sum1_800_M4[1]=row_content[5];
      sum1_800_M4[2]=row_content[6];
    
    }
  }

  TCanvas *c1 = new TCanvas("All Offsets", "All Offsets", 1200,500);

  c1.Divide(3,2);
  c1.cd(1);


  ////////MODO 2
  TMultiGraph *mg1= new TMultiGraph();
   
  TGraphErrors *gr1= new TGraphErrors(3,adders, sum0_400_M2,0,0);

   gr1->SetMarkerColor(1);
   gr1->SetMarkerStyle(20);
   mg1->Add(gr1);


   TGraphErrors *gr3= new TGraphErrors(3,adders , sum1_400_M2,0,0);

   gr3->SetMarkerColor(2);
   gr3->SetMarkerStyle(21);
   mg1->Add(gr3);


    mg1->Draw("ap1");
    mg1->SetTitle("Mode 2");
    mg1->GetXaxis()->SetTitle("Adder");
    mg1->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg1(.099,0.867,.392,.994);
    leg1.SetFillColor(0);
    leg1.AddEntry(gr1,"400 mV, Disc 0","1p");
    leg1.AddEntry(gr3,"400 mV, Disc 1","1p");
   
    leg1.DrawClone();

    gPad->Update();
    gPad->Modified();


    c1.cd(2);

    TMultiGraph *mg2= new TMultiGraph();
    
   TGraphErrors *gr2= new TGraphErrors(3, adders , sum0_800_M2,0,0);

   gr2->SetMarkerColor(1);
   gr2->SetMarkerStyle(20);
   mg2->Add(gr2);

  

   TGraphErrors *gr4= new TGraphErrors(3,adders , sum1_800_M2,0,0);

   gr4->SetMarkerColor(2);
   gr4->SetMarkerStyle(21);
   mg2->Add(gr4);

    mg2->Draw("ap1");
    mg2->SetTitle("Mode 2");
    mg2->GetXaxis()->SetTitle("Adder");
    mg2->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg2(.099,0.867,.392,.994);
    leg2.SetFillColor(0);
    leg2.AddEntry(gr2,"800 mV Disc 0","1p");
    leg2.AddEntry(gr4,"800 mV, Disc 1","1p");
   
    leg2.DrawClone();

    gPad->Update();
    gPad->Modified();


    c1.cd(3);


  ////////MODO 3
  TMultiGraph *mg3= new TMultiGraph();
   
  TGraphErrors *gr5= new TGraphErrors(3,adders , sum0_400_M3,0,0);

   gr5->SetMarkerColor(1);
   gr5->SetMarkerStyle(20);
   mg3->Add(gr5);

   TGraphErrors *gr7= new TGraphErrors(3,adders , sum1_400_M3,0,0);

   gr7->SetMarkerColor(2);
   gr7->SetMarkerStyle(21);
   mg3->Add(gr7);

     mg3->Draw("ap1");
    mg3->SetTitle("Mode 3");
    mg3->GetXaxis()->SetTitle("Adder");
    mg3->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg3(.099,0.867,.392,.994);
    leg3.SetFillColor(0);
    leg3.AddEntry(gr5,"400 mV, Disc 0","1p");
    leg3.AddEntry(gr7,"400 mV, Disc 1","1p");
    
    leg3.DrawClone();

    gPad->Update();
    gPad->Modified();


    c1.cd(4);
    TMultiGraph *mg4= new TMultiGraph();

   TGraphErrors *gr6= new TGraphErrors(3,adders , sum0_800_M3,0,0);

   gr6->SetMarkerColor(1);
   gr6->SetMarkerStyle(20);
   mg4->Add(gr6);
   
   TGraphErrors *gr8= new TGraphErrors(3,adders , sum1_800_M3,0,0);

   gr8->SetMarkerColor(2);
   gr8->SetMarkerStyle(21);
   mg4->Add(gr8);

    mg4->Draw("ap1");
    mg4->SetTitle("Mode 3");
    mg4->GetXaxis()->SetTitle("Adder");
    mg4->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg4(.099,0.867,.392,.994);
    leg4.SetFillColor(0);
    leg4.AddEntry(gr6,"800 mV Disc 0","1p");
    leg4.AddEntry(gr8,"800 mV, Disc 1","1p");

    leg4.DrawClone();

    gPad->Update();
    gPad->Modified();


    c1.cd(5);

    ////////MODO 4
  TMultiGraph *mg5= new TMultiGraph();
   
  TGraphErrors *gr9= new TGraphErrors(3,adders , sum0_400_M4,0,0);

   gr9->SetMarkerColor(1);
   gr9->SetMarkerStyle(20);
   mg5->Add(gr9);

   TGraphErrors *gr11= new TGraphErrors(3,adders , sum1_400_M4,0,0);

   gr11->SetMarkerColor(2);
   gr11->SetMarkerStyle(21);
   mg5->Add(gr11);


    mg5->Draw("ap1");
    mg5->SetTitle("Mode 4");
    mg5->GetXaxis()->SetTitle("Adder");
    mg5->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg5(.099,0.867,.392,.994);
    leg5.SetFillColor(0);
    leg5.AddEntry(gr9,"400 mV, Disc 0","1p");
    leg5.AddEntry(gr11,"400 mV, Disc 1","1p");

    leg5.DrawClone();

    gPad->Update();
    gPad->Modified();

    
    c1.cd(6);

     TMultiGraph *mg6= new TMultiGraph();

   TGraphErrors *gr10= new TGraphErrors(3,adders , sum0_800_M4,0,0);

   gr10->SetMarkerColor(1);
   gr10->SetMarkerStyle(20);
   mg6->Add(gr10);   


   TGraphErrors *gr12= new TGraphErrors(3,adders , sum1_800_M4,0,0);

   gr12->SetMarkerColor(2);
   gr12->SetMarkerStyle(21);
   mg6->Add(gr12);

    mg6->Draw("ap1");
    mg6->SetTitle("Mode 4");
    mg6->GetXaxis()->SetTitle("Adder");
    mg6->GetYaxis()->SetTitle("Output voltage[mV]");

    TLegend leg6(.099,0.867,.392,.994);
    leg6.SetFillColor(0);
    leg6.AddEntry(gr10,"800 mV Disc 0","1p");
    leg6.AddEntry(gr12,"800 mV, Disc 1","1p");

    leg6.DrawClone();

    gPad->Update();
    gPad->Modified();
    


}
