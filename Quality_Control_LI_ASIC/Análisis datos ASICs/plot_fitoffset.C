
{
  gROOT->Reset();
 
  // Read back the ntuple
  TFile in_file("fit_offset.root");
  TNtuple* my_tupleP=(TNtuple*)in_file.Get("OffsetFit");
  TNtuple &my_tuple=*my_tupleP; // Carlos is lazy, para no tener que escribir ->

  int lines = my_tuple.GetEntries();
  int channels = my_tuple.GetEntries("disc==0 && sum==0");
  int sums = my_tuple.GetEntries("disc==0 && channel==0");
  int discs = my_tuple.GetEntries("sum==0 && channel==0");

  //cout<< lines << " " << channels << " " << sums << " " << discs << endl;
   

  float channel[channels], offsetA_0[channels], offsetA_0_err[channels], offsetA_1[channels], offsetA_1_err[channels], offsetB_0[channels], offsetB_0_err[channels], offsetB_1[channels], offsetB_1_err[channels],offsetC_0[channels], offsetC_0_err[channels], offsetC_1[channels], offsetC_1_err[channels] ;
  float* row_content;

  //Datos Discriminador 0 y Adder A
 
    for (int irow=0; irow <lines;irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      channel[irow/6]=row_content[0]+1;
      offsetA_0[irow/6]=row_content[4];
      offsetA_0_err[irow/6]=row_content[6];
      
      //cout<< channel[irow/6]<< "  " << offsetA_0[irow/6] << "  " << offsetA_0_err[irow/6] <<  endl;
    }


// Datos Discriminador 1 y Adder A

 for (int irow=3; irow <my_tuple.GetEntries();irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      channel[irow/6]=row_content[0]+1;
      offsetA_1[irow/6]=row_content[4];
      offsetA_1_err[irow/6]=row_content[6];
      
      //cout<< channel[irow/6]<< "  " << offsetA_1[irow/6] << "  " << offsetA_1_err[irow/6] <<  endl;
    }

 // Datos Discriminador 0 y Adder B

for (int irow=1; irow <my_tuple.GetEntries();irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      offsetB_0[irow/6]=row_content[4];
      offsetB_0_err[irow/6]=row_content[6];
      
      //cout<< channel[irow/6]<< "  " << offsetB_0[irow/6] << "  " << offsetB_0_err[irow/6] <<  endl;
 }

  for (int irow=4; irow <my_tuple.GetEntries();irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      offsetB_1[irow/6]=row_content[4];
      offsetB_1_err[irow/6]=row_content[6];
      
      // cout<< channel[irow/6]<< "  " << offsetB_1[irow/6] << "  " << offsetB_1_err[irow/6] <<  endl;
 }

for (int irow=2; irow <my_tuple.GetEntries();irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      offsetC_0[irow/6]=row_content[4];
      offsetC_0_err[irow/6]=row_content[6];
      
      // cout<< channel[irow/6]<< "  " << offsetC_0[irow/6] << "  " << offsetC_0_err[irow/6] <<  endl;
 }

  for (int irow=5; irow <my_tuple.GetEntries();irow=irow+6){
 
      my_tuple->GetEntry(irow);
      row_content = my_tuple.GetArgs();
      offsetC_1[irow/6]=row_content[4];
      offsetC_1_err[irow/6]=row_content[6];
      
      // cout<< channel[irow/6]<< "  " << offsetC_1[irow/6] << "  " << offsetC_1_err[irow/6] <<  endl;
 }

   TCanvas *c1 = new TCanvas("Fit Offset", "Fit Offset",1000,800);
   c1.Divide(1,2);

   c1.cd(1);
  TMultiGraph *mg= new TMultiGraph();

  TGraphErrors *gr1 = new TGraphErrors(channels,channel,offsetA_0,0,offsetA_0_err);
  gr1->SetMarkerColor(1);
  gr1->SetMarkerStyle(21);
  mg->Add(gr1);

  TGraphErrors *gr2 = new TGraphErrors(channels,channel,offsetB_0,0,offsetB_0_err);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(20);
  mg->Add(gr2);

  TGraphErrors *gr3 = new TGraphErrors(channels,channel,offsetC_0,0,offsetC_0_err);
  gr3->SetTitle("Discriminator 0");
  gr3->SetMarkerColor(4);
  gr3->SetMarkerStyle(22);
  mg->Add(gr3);

  mg->Draw("ap1");
  mg->GetXaxis()->SetTitle("Channel");
  mg->GetYaxis()->SetTitle("Offset[mV]");
  

  TLegend l(.77,0.79,.97,.99);
  l.SetFillColor(0);
  l.AddEntry(gr1,"Adder A","1p");
  l.AddEntry(gr2,"Adder B","1p");
  l.AddEntry(gr3,"Adder C","1p");

  l.DrawClone();

  gPad->Update();
  gPad->Modified();

  c1.cd(2);

   TMultiGraph *mg2= new TMultiGraph();

  TGraphErrors *gr1_2 = new TGraphErrors(channels,channel,offsetA_1,0,offsetA_1_err);
  gr1_2->SetMarkerColor(1);
  gr1_2->SetMarkerStyle(21);
  mg2->Add(gr1_2);

  TGraphErrors *gr2_2 = new TGraphErrors(channels,channel,offsetB_1,0,offsetB_1_err);
  gr2_2->SetMarkerColor(2);
  gr2_2->SetMarkerStyle(20);
  mg2->Add(gr2_2);

  TGraphErrors *gr3_2 = new TGraphErrors(channels,channel,offsetC_1,0,offsetC_1_err);
  gr3_2->SetMarkerColor(4);
  gr3_2->SetMarkerStyle(22);
  gr3_2->SetTitle("Discriminator 0");
  mg2->Add(gr3_2);

  mg2->Draw("ap1");
  mg2->GetXaxis()->SetTitle("Channel");
  mg2->GetYaxis()->SetTitle("Offset[mV]");
  mg2->SetTitle("Discriminator 1");

  TLegend l(.77,0.79,.97,.99);
  l.SetFillColor(0);
  l.AddEntry(gr1_2,"Adder A","1p");
  l.AddEntry(gr2_2,"Adder B","1p");
  l.AddEntry(gr3_2,"Adder C","1p");

  l.DrawClone();

  c1->SaveAs("fitoffset.pdf");

  gPad->Update();
  gPad->Modified();


}







