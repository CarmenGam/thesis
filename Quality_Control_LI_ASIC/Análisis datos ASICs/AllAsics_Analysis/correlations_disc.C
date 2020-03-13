{
  gROOT->Reset();


 // Read back the ntuple
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->

  TGraph *gr[2][7][3];
  TGraph *gr2[2][7][3];
  
  int lines = asics.GetEntries();
  int Nasics = asics.GetEntries("disc==0 && channel == 0 && sum == 0");

  double x[Nasics], y[Nasics], x2[Nasics], y2[Nasics];

  double off[lines][2][7][3];
  double diff[lines][2][7][3];
  
  ofstream a_file ("badpoints.txt");

  int asic, disc, channel, sum, channely, sumy, discy;

  float *row_content;
 a_file<<"#asic/disc/channel/sum/fitoffset/analogoffset/diff/gain" << endl;
  for (int irow=0; irow < lines ; irow++){

    asics.GetEntry(irow);
    row_content = asics.GetArgs();
    asic = row_content[0];
    disc = row_content[1];
    channel= row_content[2];
    sum = row_content[3];


    off[asic][disc][channel][sum] = row_content[4];
    diff[asic][disc][channel][sum] = row_content[7];
    //cout << off[asic][0][0][0] << endl;

   
    /* 
    if ((row_content[4] > 40.) || (row_content[4] < -55.)){

       cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      
      }

 if ((row_content[9] < 0.7) || (row_content[9] > 1.0)){

       cout << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;
      a_file << asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << row_content[4]<<"\t" <<  row_content[5] << "\t" << row_content[7] << "\t" << row_content[9] << endl;

      }*/


    
    //cout << off[asic][disc][channel][sum] << endl;
  }


  
for (disc = 0; disc < 2; disc++){
  for (discy = 0; discy < 2; discy++){
    for(channel = 0; channel < 7; channel++){
      for (sum = 0; sum < 3 ; sum++){


      if (discy != disc){
	
	

	TString t= Form("Correlation Offset, Disc %i - %i, Channel %i, Adder %c",disc, discy, channel, 'A'+sum);
		TCanvas *canvas = new TCanvas(t,t);

	
	for(int i=0; i< Nasics ; i++){

	  x[i] = off[i+61][disc][channel][sum];
	  y[i] = off[i+61][discy][channel][sum];
	  x2[i] = diff[i+61][disc][channel][sum];
	  y2[i] = diff[i+61][discy][channel][sum];
	
	  // cout<< x2[i] << ""<< y2[i] << endl;
	}
	

	TMultiGraph *mg = new TMultiGraph();

	TGraph *gr[disc][channel][sum]= new TGraph(Nasics,x,y);
	
	//gr[disc][channel][sum]->SetTitle(t);
	//gr[disc][channel][sum]->GetXaxis()->SetTitle(Form("Channel %i[mV]",channel));
        //gr[disc][channel][sum]->GetYaxis()->SetTitle(Form("Channel %i[mV]",channely));
	gr[disc][channel][sum]->SetMarkerColor(38);
	gr[disc][channel][sum]->SetMarkerStyle(20);
	gr[disc][channel][sum]->SetMarkerSize(0.5);
      	mg->Add(gr[disc][channel][sum]);

	

	    
	//gr[disc][channel][sum]->Draw("ap");
	
	
			    
	gPad->Modified();
	gPad->Update();

	TGraph *gr2[disc][channel][sum]= new TGraph(Nasics,x2,y2);
	
	
	gr2[disc][channel][sum]->SetMarkerColor(46);
	gr2[disc][channel][sum]->SetMarkerStyle(20);
	gr2[disc][channel][sum]->SetMarkerSize(0.5);
      	mg->Add(gr2[disc][channel][sum]);


    TLegend leg(.098,0.818,.405,.900);
    leg.SetFillColor(0);
    leg.AddEntry(gr[disc][channel][sum],"Fit Offset","p0");
    leg.AddEntry(gr2[disc][channel][sum],"Fit Offset - Analog Offset","p0");
    
    


	mg->Draw("ap");
	mg->SetTitle(t);
	mg->GetXaxis()->SetTitle(Form("Disc %i[mV]",disc));
	mg->GetYaxis()->SetTitle(Form("Disc %i[mV]",discy));





	leg->Draw();
	//canvas->SaveAs(Form("OFFSET-CH%iCH%iDISC%iSUM%i.png",channel,channely,disc,sum));
	canvas->SaveAs(Form("DISCSCORR-DISC%iDISC%iCH%iADD%c.png",disc,discy,channel,'A'+sum));

	}
      }
    }
  }
 }


}



