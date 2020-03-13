 {

   gROOT->Reset();
  //TFile file("linearity.root","RECREATE");
  //TNtuple linear("voltage","voltage","asic:channel:disc:input:sumA:sumB:sumC");
  //linear.ReadFile("voltage.txt");
  //linear.Write();

 
  TFile a_file("linearity.root");
  TNtuple* linP=(TNtuple*)a_file.Get("voltage");
  TNtuple &lin=*linP;

  TGraph *gfa[7][2][3];
  double x, y, maxx, maxy;
  double gain, off;
  double d, dmax, dmaxX;
  int method = 1;
  int pointmax;

  TH1D *h1 = new TH1D("  300 mV","Deviations = 300 mV",100,-20,150);
  TH1D *h2 = new TH1D("  500 mV","Deviations = 500 mV",100,-20,150);
  TH1D *h3 = new TH1D("  800 mV","Deviations = 800 mV",100,-20,150);
  TH1D *h4 = new TH1D("  1000 mV","Deviations = 1000 mV",100,-20,150);

  TH1D *h = new TH1D(" Max dev", "Max. Deviation",100,0,60);
  h->SetFillColor(30);
  h->GetXaxis()->SetTitle("Max deviation from fit line [mV]");

  /*TH1D *h1 = new TH1D("  < 300 mV","Deviations < 300 mV",100,-20,150);
  TH1D *h2 = new TH1D("  < 500 mV","Deviations < 500 mV",100,-20,150);
  TH1D *h3 = new TH1D("  < 800 mV","Deviations < 800 mV",100,-20,150);
  TH1D *h4 = new TH1D("  < 1000 mV","Deviations < 1000 mV",100,-20,150);*/
  

  
  h1->SetFillColor(30);
  h1->GetXaxis()->SetTitle("Deviation from fit line [mV]");
  h2->SetFillColor(30);
  h2->GetXaxis()->SetTitle("Deviation from fit line [mV]");
  h3->SetFillColor(30);
  h3->GetXaxis()->SetTitle("Deviation from fit line [mV]");
  h4->SetFillColor(30);
  h4->GetXaxis()->SetTitle("Deviation from fit line [mV]");

  ofstream file("dev.txt",ios::app);


  for (int asic = 401; asic < 452; asic++){

    if (asic == 120 || asic == 412 || asic == 264) asic++;
    for (int disc = 0; disc < 2; disc++){
      for (int sum = 0; sum < 3; sum++){
	for (int channel = 1; channel <= 7; channel ++){

	  
	  /////////////Metodo 1////////////////////

	  if (method == 1){
	    
	    lin.SetMarkerStyle(20);
	    lin.Draw(Form("sum%c*1000:input",sum+'A'),Form(" asic == %i && disc == %i && channel == %i",asic,disc,channel),"p");
	    
	    TIter next(gPad->GetListOfPrimitives());
	    TObject *who=0;
	    TObject *temp;
	    while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;
	    gfa[channel-1][disc][sum]=(TGraph*)who;
	    
	    TFitResultPtr r=gfa[channel-1][disc][sum]->Fit("pol1","0qS","",0,300);
	    gain = r->Value(1);
	    off = r->Value(0);
	    
	    TF1 *fit = new TF1("fit","[1]*x + [0]",0,1000);
	    fit->SetParameter(0,off);
	    fit->SetParameter(1,gain);
	    fit->Draw("same");	  
	    
	    for (int point = 0; point < 10; point ++){
	      gfa[channel-1][disc][sum]->GetPoint(point,x,y);
	      //cout << x << "," << y << endl;
	      d = sqrt((gain*x-y+off)*(gain*x-y+off)) / sqrt(gain*gain + 1);
	      //cout << d << endl;
	      
	      /*if (x < 300){	      
		h1->Fill(d);
	      }
	      
	      if (x < 500){
		h2->Fill(d);
	      }
	      if (x < 800){
		h3->Fill(d);
	      }
	      if (x < 1000){
		h4->Fill(d);
		}	 */ 	
	      
	      if (x == 300){	      
		h1->Fill(d);
		}
		
		if (x == 500){
		h2->Fill(d);
		}
		if (x == 800){
		h3->Fill(d);
		}
		if (x == 1000){
		h4->Fill(d);
		}	 	  
	      
	    }
	  }

	  if (method == 2){
	    
	    for (int i =0; i < 9; i++){

	      lin.SetMarkerStyle(20);
	      lin.Draw(Form("sum%c*1000:input",sum+'A'),Form(" asic == %i && disc == %i && channel == %i",asic,disc,channel),"p");
	  
	      TIter next(gPad->GetListOfPrimitives());
	      TObject *who=0;
	      TObject *temp;
	      while(temp=next()) if(temp->GetName()==TString("Graph")) who=temp;
	      gfa[channel-1][disc][sum]=(TGraph*)who;

	      gfa[channel-1][disc][sum]->RemovePoint(i);

	      TFitResultPtr r=gfa[channel-1][disc][sum]->Fit("pol1","0qS","");
	      gain = r->Value(1);
	      off = r->Value(0);
	      
	      TF1 *fit = new TF1("fit","[1]*x + [0]",0,1000);
	      fit->SetParameter(0,off);
	      fit->SetParameter(1,gain);
	      fit->Draw("same");
	      
	      
	      for (int point = 0; point < 9; point ++){
		gfa[channel-1][disc][sum]->GetPoint(point,x,y);
		d = sqrt((gain*x-y+off)*(gain*x-y+off)) / sqrt(gain*gain + 1);
		if (point == 0) {dmax = d; pointmax = point;}
		if (d > dmax) {dmax = d; pointmax = point;}

		//cout << i << "  " << point << " " <<  d << endl;
		
	      }
	      
	      if (i == 0) dmaxX = dmax;
	      if (dmax > dmaxX)  {dmaxX = dmax; gfa[channel-1][disc][sum]->GetPoint(pointmax,maxx,maxy);}
	      


	      //gfa[channel-1][disc][sum]->GetPoint(i,x,y);
	      //cout << i << "  " << dmaxX << "  "  << x << "  " << y << endl;  
	      
	    }

	    //cout << asic << "  " << dmaxX << "  " << maxx << "  " << maxy << endl;
	    file << asic << "  " << dmaxX << "  " << maxx << "  " << maxy << endl;
	    //h->Fill(dmaxX);

	  //cout << r->Value(0) << "  " << r->Value(1) << endl;

	  }
	}
      }
    }
  }
      
    if (method == 1){
      TCanvas *c1 = new TCanvas();
      c1->Divide(2,2);
      
      c1->cd(1);
      h1->Draw();
      c1->cd(2);
      h2->Draw();
      c1->cd(3);
      h3->Draw();
      c1->cd(4);
      h4->Draw();
      
      c1->SaveAs("linearity_eq.pdf");
    }    
    if (method == 2){
      TCanvas *c1 = new TCanvas();
      h->Draw();
      c1->SaveAs("linearity_maxdev.pdf");
    }

  
 }
