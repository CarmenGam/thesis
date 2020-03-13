
{
  gROOT->Reset();
 
  // Save data substracted from DATASHEETS

  // Data from VOLTAGE TEST, for calculating FIT OFFSET
  TFile in_file("voltage.root","RECREATE"); 
  TNtuple* voltage_tupleP=new TNtuple("Voltage","Voltage","asic:v:channel:disc:voltage:sumA:sumB:sumC");
  TNtuple &vtuple=*voltage_tupleP; // Carlos is lazy, para no tener que escribir ->
  vtuple.ReadFile("voltages.txt");
  vtuple.Write();
  
  TFile out_file("gain.root","RECREATE");
  TNtuple out("nt","nt","asic:v:channel:disc:sum:gain:offset");
  
  int marker[3]={20,21,25};// Asignamos colores y  forma a los markers
  int color[3]={1,2,4};

  TGraph *gfa[7][2][5][3]; // Creamos el grafico que usaremos luego para hacer Fit
  double fit_result[7][2][5][3];

  TCanvas generalC; // Creamos un Canvas multiple para ver todos los graficos
  int where=1;// where nos va a decir en que grafico estamos (hay 14) 
  vector<int> asics;

  float *row_content;
  int count = 0;
  for (int i=0; i<vtuple.GetEntries(); i++){
    vtuple.GetEntry(i);
    row_content=vtuple.GetArgs();
    int nasic =  row_content[0];
    
    if (asics.size() == 0) {asics.push_back(nasic); count++;}
    else if (asics[count - 1] != nasic) {cout << row_content[0] << endl; asics.push_back(nasic); count++;}

    if (nasic == asics[0] && count > 1) break;

  }

  double fit, fiterr,gain, gainerr;
  for (int n=0; n<asics.size(); n++){
    for (int disc=0; disc < 2; disc++){
      for (int channel = 1; channel <= 7; channel++){
	for (int v=0; v < 5; v++){
	  for (int sum=0; sum<3; sum++){
	    double vol = 3+v*0.1;
	    int asic = asics[n];
	    vtuple.SetMarkerStyle(marker[sum]);
	    vtuple.SetMarkerColor(color[sum]);
	    vtuple.Draw(
			Form("1000*sum%c:voltage",'A'+sum),
			Form("asic==%i && channel==%i && disc==%i && v>(%f-0.0001) && v < %f+0.00001",asic,channel,disc,vol,vol),
			(sum==0?"p":"p same") //Pintar los ejes solo la primera vez
			);	
	    
	    TIter next(gPad->GetListOfPrimitives());
	    
	    TObject *who=0;
	    TObject *temp;
	    while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;
	    
	    gfa[channel-1][disc][v][sum]=(TGraph*)who; //Asigna las graficas a un array de graficas
	    
	    TFitResultPtr r=gfa[channel-1][disc][v][sum]->Fit("pol1","0qS","",0,300);//Hacemos el fit linear a cada grafico
	    fit=r->Value(0);//Offset
	    gain=r->Value(1);//Gain
	    fiterr=r->Error(0);//Error Offset
	    gainerr=r->Error(1);//Error Gain
	    
	    gPad->Modified();
	    gPad->Update();
	    
	    
	    out.Fill(asic,vol,channel,disc,sum,gain,fit);
	    // cout << asic << "\t" << vol << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << fit << "\t" << gain << endl;
	    
	  }
	  //gPad->WaitPrimitive();
	}
      }
    }
  }  
  out.Write();  
}
