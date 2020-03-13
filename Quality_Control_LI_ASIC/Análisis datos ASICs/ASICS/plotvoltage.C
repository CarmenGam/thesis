{
  gROOT->Reset();
 
  // Save data substracted from DATASHEETS

  // Data from VOLTAGE TEST, for calculating FIT OFFSET
  TFile in_file("voltage.root","RECREATE"); 
  TNtuple* voltage_tupleP=new TNtuple("Voltage","Voltage","asic:channel:discriminator:mv:sumA:sumB:sumC");
  TNtuple &voltage_tuple=*voltage_tupleP; // Carlos is lazy, para no tener que escribir ->
  voltage_tuple.ReadFile("voltage.txt");
  voltage_tuple.Write();

  //Data from ANALOG offset test

  TFile fanalog("analog_offset.root","RECREATE");
  TNtuple* analog_tupleP=new TNtuple("Analog","Analog","asic:channel:sumA:sumB:sumC");
  TNtuple &analog_tuple=*analog_tupleP;
  analog_tuple.ReadFile("analog_offset.txt");
  analog_tuple.Write();

  // Data from DIGITAL offset test
  TFile fdig("offset.root","RECREATE");
  TNtuple* dig_tupleP=new TNtuple("Offset","Offset", "asic:channel:comp:sum:max:min:noise:offset");
  TNtuple &dig_tuple=*dig_tupleP;
  dig_tuple.ReadFile("offset.txt");
  dig_tuple.Write();

  int marker[3]={20,21,25};// Asignamos colores y  forma a los markers
  int color[3]={1,2,4};

  TCanvas generalC; // Creamos un Canvas multiple para ver todos los graficos
  generalC.Divide(4,4);// a la vez
  int where=1;// where nos va a decir en que grafico estamos (hay 14) 

  TGraph *gfa[7][2][3]; // Creamos el grafico que usaremos luego para hacer Fit
  double fit_result[7][2][3][4];

  double asic, fit, fiterr, analog,gain, gainerr, dig, noise;

  ofstream out_file("offset_diff.txt");
  
  for(int disc=0;disc<2;disc++){
    for(int channel=1;channel<=7;channel++){ //Loops a canales, sumadores y discriminadores
      TString t=Form("Channel %i Disc %i",channel,disc);// Form sustituye %i, %l, etc
      //TCanvas *canvas=new TCanvas(t,t);
      TLegend *l=new TLegend(0.15,0.6,0.43,0.85);//Leyenda, tamaño de la leyenda
      generalC.cd(where++);//Aqui le decimos en que parte del Canvas graficar

      for(int sum=0;sum<3;sum++){//Vamos a poner los 3 sumadores en cada grafica

	//De los test analogico y digital simplemente necesitamos valores
	analog_tuple.Draw(
			  Form("asic:sum%c",'A'+sum),
			  Form("channel==%i", channel),
			  "goff");
	
	asic = *analog_tuple.GetV1();
	analog = *analog_tuple.GetV2();


	dig_tuple.Draw(
		       "offset:noise",
			Form("comp==%i && channel==%i &&  sum==%i",disc,channel,sum),
			"goff");

	
	dig = *dig_tuple.GetV1();
	noise = *dig_tuple.GetV2();


	//Del test voltage necesitamos hacer un fit lineal para extraer voltaje y ganancia.
	voltage_tuple.SetMarkerSize(0.7);
	voltage_tuple.SetMarkerStyle(marker[sum]); //Para cada sumador un marker
	voltage_tuple.SetMarkerColor(color[sum]);
	
	voltage_tuple.Draw(
		      Form("1000*sum%c:mv",'A'+sum),//Dibuja sumador frente a señal de entrada
		      Form("channel==%i && discriminator==%i",channel,disc),
		      (sum==0?"p":"p same") //Pintar los ejes solo la primera vez
		      );



	TIter next(gPad->GetListOfPrimitives()); //Esta parte de codigo es para poder extraer la grafica 
	//con la que podremos hacer fits y analisis

	TObject *who=0;
	TObject *temp;
	while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;

	gfa[channel-1][disc][sum]=(TGraph*)who; //Asigna las graficas a un array de graficas
	
	l->AddEntry(who, //Entradas de la leyenda
		    Form("Adder %c",'A'+sum),
		    "p");

	TFitResultPtr r=gfa[channel-1][disc][sum]->Fit("pol1","0qS","",0,300);//Hacemos el fit linear a cada grafico
	fit=r->Value(0);//Offset
	gain=r->Value(1);//Gain
	fiterr=r->Error(0);//Error Offset
	gainerr=r->Error(1);//Error Gain

	out_file<< asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << 
	  fit << "\t" << analog << "\t" << fiterr << "\t" << fit-analog << "\t" << 
	  (fit-analog)/fiterr << "\t" << gain << "\t" << gainerr << "\t" << dig << "\t" << noise << endl;
      }

      TH2F *h=gPad->FindObject("htemp"); //Asignamos los textos de los graficos
      
      h->GetXaxis()->SetTitle("Input Voltage [mV]");
      h->GetYaxis()->SetTitle("Rate Scan Result [mV]");
      h->SetTitle(t);

      l->Draw();//Dibuja la leyenda
      
      gPad->Modified();
      gPad->Update();

    }        
  }
  //generalC->SaveAs("voltage.pdf");
}
