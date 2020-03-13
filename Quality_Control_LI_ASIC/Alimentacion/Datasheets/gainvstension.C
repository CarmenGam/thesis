{
  gROOT->Reset();
  TFile fin("gain.root");
  TNtuple *nt=(TNtuple*)fin.Get("nt");
  float *row_content;
  //Find outliers


  TFile fout("outliers.root","RECREATE");
  TNtuple *outliers = new TNtuple("out","out","asic:v:channel:disc:sum:gain:offset");
  TNtuple *buenos = new TNtuple("nt","nt","asic:v:channel:disc:sum:gain:offset");
  for (int irow = 0; irow < nt->GetEntries(); irow++){
    nt->GetEntry(irow);
    row_content=nt->GetArgs();
    if ( row_content[5] < 0.3 || fabs(row_content[5]) > 1.2) {
      outliers->Fill(row_content[0],row_content[1],row_content[2],row_content[3],row_content[4],row_content[5],row_content[6]);
      for(int i=0; i<7; i++) cout << row_content[i] <<"\t";
      cout << endl;
    }
    else {  buenos->Fill(row_content[0],row_content[1],row_content[2],row_content[3],row_content[4],row_content[5],row_content[6]);}
    
  }
  buenos->Write();
  outliers->Write();

}
