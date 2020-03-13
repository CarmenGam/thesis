//This MACRO plots the digital Noise measured in function of the channel. 

{
  gROOT->Reset();
 
  // Read back the ntuple
  TFile in_file("offset.root");
  TNtuple* my_tupleP=(TNtuple*)in_file.Get("Offset");
  TNtuple &my_tuple=*my_tupleP; // Carlos is lazy, para no tener que escribir ->
  
  
  int marker[3]={20,21,25};// Asignamos colores y  forma a los markers
  int color[3]={1,2,4};

  TCanvas *generalC= new TCanvas("Noise","Noise", 1000,800); // Creamos un Canvas multiple para ver todos los graficos
  
  generalC.Divide(1,2);// a la vez
  int where=1;// where nos va a decir en que grafico estamos (hay 14) 
  generalC.SetGrid();
  TGraph *gr[2];
    
    for(int disc=0;disc<2;disc++){

      TString t=Form("Digital Noise \n Discriminator %i", disc);
      
      TLegend *l=new TLegend(0.1,0.74,0.23,0.90);

      generalC.cd(where++);      

	my_tuple.SetMarkerStyle(marker[1]);
	my_tuple.SetMarkerColor(color[1]);

	my_tuple.Draw(
		      Form("noise:channel"),
		      Form("sum==1 && comp==%i",disc)
		      
		      );

	TIter next(gPad->GetListOfPrimitives());

	TObject *who=0;
	TObject *temp;
	while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;

	
	gr[disc] = (TGraph*)who;

	l->AddEntry(who,
		    Form("Adder A"),
		    "p");

      
      	TH2F *h=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      h->GetXaxis()->SetTitle("Channel");
      h->GetYaxis()->SetTitle("Offset [mV]");
      h->SetTitle(t);

      l->Draw();//Dibuja la leyenda

      gPad->Modified();
      gPad->Update();

    }

    
  }
	


