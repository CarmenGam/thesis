{
  gROOT->Reset();
 
  // Read back the ntuple
  TFile in_file("analog_offset.root");
  TNtuple* my_tupleP=(TNtuple*)in_file.Get("Analog");
  TNtuple &my_tuple=*my_tupleP; // Carlos is lazy, para no tener que escribir ->
  
  int lines = my_tuple.GetEntries();

  float asic, channel[lines], sumA[lines], sumB[lines], sumC[lines];
  float* row_content;

  for(int irow=0; irow<my_tuple.GetEntries();++irow){
    my_tuple->GetEntry(irow);
    row_content = my_tuple.GetArgs();
    asic = row_content[0];
    channel[irow] = row_content[1];
    sumA[irow] = row_content[2];
    sumB[irow] = row_content[3];
    sumC[irow] = row_content[4];

    // cout << asic <<"\t" << channel[irow] << "\t" << sumA[irow] << "\t" << sumB[irow] << "\t" << sumC[irow] << endl;
  }

  TCanvas *c1 = new TCanvas("Analog Offset","Analog Offset",700,500);
  //c1->SetGrid();

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors *gr1 = new TGraphErrors(lines,channel,sumA,0,0);
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(21);
  mg->Add(gr1);

  
  TGraphErrors *gr2 = new TGraphErrors(lines,channel,sumB,0,0);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(20);
  mg->Add(gr2);

  TGraphErrors *gr3 = new TGraphErrors(lines,channel,sumC,0,0);
  gr3->SetMarkerColor(kBlack);
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

  c1->SaveAs("analog.pdf");

  gPad->Update();
  gPad->Modified();


}
