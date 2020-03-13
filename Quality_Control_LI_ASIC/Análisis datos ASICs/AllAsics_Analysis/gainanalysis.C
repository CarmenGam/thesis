{
  gROOT->Reset();


 // Read back the ntuple 
  TFile in_file("allasicsdata.root");
  TNtuple* asicsP=(TNtuple*)in_file.Get("Asics");
  TNtuple &asics=*asicsP; // Carlos is lazy, para no tener que escribir ->
  ofstream a_file("gainall.txt");
  int marker[6]={20,21,22};
   int color[3]={1,2,4};
  

  for (int disc=0; disc < 2; disc ++){
    for (int channel = 0; channel < 7; channel++){
      for (int sum = 0; sum < 3; sum++){
	TString t= Form(" Gain, Channel %i, Disc %i Adder %c", channel, disc,'A'+sum);

	TCanvas *generalC = new TCanvas(t,t,1000,700);

	  asics.Draw(
		     "gain",
		     Form("channel==%i && disc==%i && sum==%i",channel ,disc, sum));

      TH2F *h=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h->GetXaxis()->SetTitle("Gain [mV]");
      h->SetTitle(t);
      h->SetFillColor(30);
      
      

      a_file << disc << "\t" << channel << "\t" << sum <<"\t" <<  h->GetRMS() << "\t" << h->GetMean() << endl;
      

      gPad->Modified();
      gPad->Update();
	  

      }
    }
  }

  for (int disc=0; disc < 2; disc ++){
    
      for (int sum = 0; sum < 3; sum++){

	TString t2= Form("Gain Disc %i Adder %c", disc,'A'+sum);
	TCanvas *c2 = new TCanvas(t2,t2);
 
	asics->SetMarkerStyle(marker[sum]);
	asics->SetMarkerColor(color[sum]);
	asics.Draw(
		     "gain:channel",
		     Form("disc==%i && sum==%i",disc, sum)
		   
		   );

      TH2F *h2=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h2->GetXaxis()->SetTitle("Gain [mV]");
      h2->SetTitle(t2);
      h2->GetXaxis()->SetRangeUser(-1,7);
      gPad->Modified();
      gPad->Update();

      c2->SaveAs(Form("Gain-ChannelDISC%iADDER%i.gif",disc,sum));
      
	
      }
  }

    TFile fgain("gainstats.root","RECREATE");
    TNtuple *gain = new TNtuple("Gain","Gain","disc:channel:sum:rms:mean");
    gain.ReadFile("gainall.txt");
    gain.Write();

       
    for (disc=0; disc < 2; disc ++){

      TString t3=Form("Gain mean, Disc %i",disc);
      TCanvas *cgain= new TCanvas(t3,t3);
       TLegend *l=new TLegend(0.704871,0.698312,0.901146,0.900844);//Leyenda, tamaño de la leyenda
      for (sum = 0; sum < 3; sum++){
	

	gain->SetMarkerStyle(marker[sum]);
	 gain->SetMarkerColor(color[sum]);

	gain->Draw("mean:channel",
		   Form("sum==%i && disc==%i",sum,disc),
		   (sum==0?"p":"p same")
		   );  

	TIter next(gPad->GetListOfPrimitives()); //Esta parte de codigo es para poder extraer la grafica 
	//con la que podremos hacer fits y analisis

	TObject *who=0;
	TObject *temp;
	while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;
	l->AddEntry(who, //Entradas de la leyenda
		    Form("Adder %c",'A'+sum),
		    "p");
	
	
	       
	h=(TH2F*)gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      
      h->GetXaxis()->SetTitle("Channel");
      h->GetYaxis()->SetTitle("Gain Mean [mV]");
      h->SetTitle(t3);
      h->GetYaxis()->SetRangeUser(0.8,0.88);

      l->Draw();//Dibuja la leyenda
      

	gPad->Modified();
	gPad->Update();
	cgain->SaveAs(Form("GMean-ChannelDISC%i",disc));

      }
      

    }

}
