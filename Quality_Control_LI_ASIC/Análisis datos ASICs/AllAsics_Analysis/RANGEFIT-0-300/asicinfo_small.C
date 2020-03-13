void asicinfo_small(){

  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP;
  
  TFile ftypo("typicalasic.root","RECREATE");
  TNtuple typical("Typical","Typical","disc:channel:sum:gain:rmsgain:analog:rmsanalog:dig:rmsdig:fit:rmsfit:noise:rmsnoise");
  typical.ReadFile("typicalasic.txt");
  typical.Write();

  ////////////////////////////////////// NORMALIZACION ASIC TIPICO////////////////////////////////////////
  
  float *row_content;
  int lines = typical.GetEntries();
  double gain[2][7][3], rmsgain[2][7][3],analog[2][7][3],rmsanalog[2][7][3],noise[2][7][3],rmsnoise[2][7][3], normalgain[7],channel[7], normalanalog[7], normalnoise[7],normalrmsgain[7], normalrmsanalog[7], normalrmsnoise[7];
  int disc, sum, ch,here = 1;


  for (int irow=0; irow < lines ; irow++){
    typical.GetEntry(irow);
    row_content = typical.GetArgs();
    disc = row_content[0];
    ch = row_content[1]-1;
    sum = row_content[2];
    
   
    gain[disc][ch][sum] = row_content[3];
    rmsgain[disc][ch][sum] = row_content[4];
    analog[disc][ch][sum] = row_content[5];
    rmsanalog[disc][ch][sum] = row_content[6];
    noise[disc][ch][sum] = row_content[11];
    rmsnoise[disc][ch][sum] = row_content[12];
    
  }
  
  int const lines2 = asics.GetEntries();
  int asic;
  double again[lines2][2][7][3],aanalog[lines2][2][7][3],anoise[lines2][2][7][3], normalagain[7], normalaanalog[7], normalanoise[7];
  
  for (int irow=0; irow < lines2 ; irow++){
    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    disc = row_content[1];
    ch = row_content[2]-1;
    sum = row_content[3];      
    again[asic][disc][ch][sum] = row_content[9];
    aanalog[asic][disc][ch][sum] = row_content[5];
    anoise[asic][disc][ch][sum] = row_content[12];

    //cout << again[asic][disc][ch][sum] <<"\t" << aanalog[asic][disc][ch][sum]<< "\t" << anoise[asic][disc][ch][sum] <<  endl;


  }    


  for (int asic = 67; asic < 68 ; asic++){
    TCanvas *c1 = new TCanvas(Form("ASIC %i",asic),Form("ASIC %i",asic));
    c1->Divide(2,3);

    for (int disc = 0; disc < 2; disc++){
      for (int sum = 0; sum < 3; sum++){
	
	c1->cd(here);
	float mingain = gain[disc][0][sum]-rmsgain[disc][0][sum];
	float maxgain = gain[disc][0][sum]+rmsgain[disc][0][sum];
	float minanalog = analog[disc][0][sum]-rmsanalog[disc][0][sum];
	float maxanalog = analog[disc][0][sum]+rmsanalog[disc][0][sum];
	float minnoise = noise[disc][0][sum]- rmsnoise[disc][0][sum];
	float maxnoise = noise[disc][0][sum]+ rmsnoise[disc][0][sum];
	
	
	
	for (int i =0; i < 7; i++){
	  channel[i]=i+1;	  
	  if (gain[disc][i][sum] < mingain)
	    mingain=gain[disc][i][sum]-rmsgain[disc][i][sum];
	  if (analog[disc][i][sum] < minanalog)
	    minanalog=analog[disc][i][sum]-rmsanalog[disc][i][sum];
	  if (noise[disc][i][sum] < minnoise)
	    minnoise=noise[disc][i][sum]- rmsnoise[disc][i][sum];	  
	  if (gain[disc][i][sum] > maxgain)
	    maxgain=gain[disc][i][sum]+rmsgain[disc][i][sum];
	  if (analog[disc][i][sum] > maxanalog)
	    maxanalog=analog[disc][i][sum]+rmsanalog[disc][i][sum];
	  if (noise[disc][i][sum] > maxnoise)
	    maxnoise=noise[disc][i][sum]+rmsnoise[disc][i][sum];  

	}



	for (ch =0; ch < 7; ch++){
	  normalgain[ch]=(gain[disc][ch][sum]-mingain)/(maxgain-mingain);
	  normalanalog[ch]=(analog[disc][ch][sum]-minanalog)/(maxanalog-minanalog);
	  normalnoise[ch]=(noise[disc][ch][sum]-minnoise)/(maxnoise-minnoise);
	  normalrmsgain[ch] = rmsgain[disc][ch][sum]/(maxgain-mingain);
	  normalrmsanalog[ch] = rmsanalog[disc][ch][sum]/(maxanalog-minanalog);
	  normalrmsnoise[ch] = rmsnoise[disc][ch][sum]/(maxnoise-minnoise);


	  // cout << normalgain[ch] << endl;

	}

	

	//cout << mingain << "\t" << maxgain << endl;

		TMultiGraph *mg = new TMultiGraph;

	TGraphErrors *gr = new TGraphErrors(7,channel,normalgain,0,normalrmsgain);
	gr->SetMarkerStyle(20);
	//gr->SetMarkerSize(4);
	gr->SetMarkerColor(2);
	gr->SetLineColor(2);
	//gr->SetLineWidth(4);
	mg->Add(gr);
	

	TGraphErrors *gr2 = new TGraphErrors(7,channel,normalanalog,0,normalrmsanalog);
	gr2->SetMarkerStyle(21);
	//gr2->SetMarkerSize(4);
	gr2->SetMarkerColor(4);
	gr2->SetLineColor(4);
	//gr2->SetLineWidth(2);
	mg->Add(gr2);

	TGraphErrors *gr3 = new TGraphErrors(7,channel,normalnoise,0,normalrmsnoise);
	gr3->SetMarkerStyle(22);
	//gr3->SetMarkerSize(4);
	gr3->SetMarkerColor(1);
	gr3->SetLineColor(1);	
	
	mg->Add(gr3);
		

	/////////////////////////////////////////////////////////////////////////////////


	///////////////////////////// NORMALIZACION DE CADA ASIC ///////////////////////

	float minagain = again[asic][disc][0][sum];//-rmsgain[disc][0][sum];
	float maxagain = again[asic][disc][0][sum];//+rmsgain[disc][0][sum];
	float minaanalog = aanalog[asic][disc][0][sum];//-rmsanalog[disc][0][sum];
	float maxaanalog = aanalog[asic][disc][0][sum];//+rmsanalog[disc][0][sum];
	float minanoise = anoise[asic][disc][0][sum];//-rmsnoise[disc][0][sum];
	float maxanoise = anoise[asic][disc][0][sum];//+rmsnoise[disc][0][sum];

	
	
	for (int i =0; i < 7; i++){
	  
	  if (again[asic][disc][i][sum] < minagain)
	    minagain=again[asic][disc][i][sum];//-rmsgain[disc][i][sum];

	  if (aanalog[asic][disc][i][sum] < minaanalog)
	    minaanalog=aanalog[asic][disc][i][sum];//-rmsanalog[disc][i][sum];

	  if (anoise[asic][disc][i][sum] < minnoise)
	    minanoise=anoise[asic][disc][i][sum];//-rmsnoise[disc][i][sum];
	  
	  if (again[asic][disc][i][sum] > maxagain)
	    maxagain=again[asic][disc][i][sum];//+rmsgain[disc][i][sum];

	  if (aanalog[asic][disc][i][sum] > maxaanalog)
	    maxaanalog=aanalog[asic][disc][i][sum];//+rmsanalog[disc][i][sum];

	  if (anoise[asic][disc][i][sum] > maxanoise)
	    maxanoise=anoise[asic][disc][i][sum];//+rmsnoise[disc][i][sum];  

	}

	
	cout << minagain << "\t" << maxagain << endl;


	for (ch =0; ch < 7; ch++){
	  normalagain[ch]=(again[asic][disc][ch][sum]-minagain)/(maxagain-minagain);
	  normalaanalog[ch]=(aanalog[asic][disc][ch][sum]-minaanalog)/(maxaanalog-minaanalog);
	  normalanoise[ch]=(anoise[asic][disc][ch][sum]-minanoise)/(maxanoise-minanoise);

	}




	TGraphErrors *gr4 = new TGraphErrors(7,channel,normalagain,0,0);
	gr4->SetMarkerStyle(24);
	//gr4->SetMarkerSize(2);
	gr4->SetMarkerColor(2);
	gr4->SetLineColor(2);
	//gr4->SetLineWidth(4);
	mg->Add(gr4);
	

	TGraphErrors *gr5 = new TGraphErrors(7,channel,normalaanalog,0,0);
	gr5->SetMarkerStyle(25);
	//gr5->SetMarkerSize(2);
	gr5->SetMarkerColor(4);
	gr5->SetLineColor(4);
	//gr5->SetLineWidth(2);
	mg->Add(gr5);

	TGraphErrors *gr6 = new TGraphErrors(7,channel,normalanoise,0,0);
	gr6->SetMarkerStyle(26);
	//gr6->SetMarkerSize(2);
	gr6->SetMarkerColor(1);
	gr6->SetLineColor(1);	
	
	mg->Add(gr6);
	

	
	
	mg->Draw("ap");

	here++;
      }
    }        
  }  
  //c1->SaveAs(Form("ASIC%i_small.pdf",asic));


}  

