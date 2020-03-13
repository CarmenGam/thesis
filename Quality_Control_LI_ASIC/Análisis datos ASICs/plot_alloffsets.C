//This Macro plots all the offsets in the same graph. 

{
  gROOT->Reset();

  //Primero guardamos las tuplas de todos.

 // Read back the ntuple for Analog Offset data
  TFile analog("analog_offset.root");
  TNtuple* analog_tupleP=(TNtuple*)analog.Get("Analog");
  TNtuple &analog_tuple=*analog_tupleP; // Carlos is lazy, para no tener que escribir ->

  // Read back the ntuple for Digital Offset data
  TFile offset("offset.root");
  TNtuple* offset_tupleP=(TNtuple*)offset.Get("Offset");
  TNtuple &offset_tuple=*offset_tupleP; // Carlos is lazy, para no tener que escribir ->
  
 // Read back the ntuple for Fit Offset data

   TFile fitoff("fit_offset.root");
  TNtuple* fitoff_tupleP=(TNtuple*)fitoff.Get("OffsetFit");
  TNtuple &fitoff_tuple=*fitoff_tupleP; // Carlos is lazy, para no tener que escribir ->

  //////////////////////////DATOS ANALOG OFFSET////////////////////////////


  int lines = analog_tuple.GetEntries();

float asic, channel[lines], sumA_analog[lines], sumB_analog[lines], sumC_analog[lines];

  float* row_content;

   for(int irow=0; irow<lines;++irow){
    analog_tuple->GetEntry(irow);
    row_content = analog_tuple.GetArgs();
    asic = row_content[0];
    channel[irow] = row_content[1];
    sumA_analog[irow] = row_content[2];
    sumB_analog[irow] = row_content[3];
    sumC_analog[irow] = row_content[4];

    //cout << asic <<"\t" << channel[irow] << "\t" << sumA_analog[irow] << "\t" << sumB_analog[irow] << "\t" << sumC_analog[irow] << endl;
  }


   /////////////////////DATOS DIGITAL OFFSET////////////////////////

   lines = offset_tuple.GetEntries();

   int channels = offset_tuple.GetEntries("comp==0 && sum==1");

   float sumA_dig0[channels], sumA_dig1[channels];
   int i=0, j=0, k=0,l=0,m=0, n=0;
   
   
   for (irow=0; irow < lines ; irow++){
      offset_tuple->GetEntry(irow);
      row_content = offset_tuple.GetArgs();
	if (row_content[3]==1 && row_content[2]==0){  
      	  sumA_dig0[i]=row_content[7];
	  i++;
	}
	
        if (row_content[3]==1 && row_content[2]==1){
	  sumA_dig1[j]=row_content[7];
	  j++;
	}

   
   }

   // for (i=0; i<channels; i++)
   // cout << sumA_dig0[i] << "  " << sumA_dig1[i] << endl;


   //////////////DATOS FIT OFFSET /////////////////////////

   lines = fitoff_tuple.GetEntries();

   float sumA_fit0[channels], sumA_fit1[channels], sumA_fit0_err[channels], sumA_fit1_err[channels], sumB_fit0[channels], sumB_fit1[channels], sumB_fit0_err[channels], sumB_fit1_err[channels],  sumC_fit0[channels], sumC_fit1[channels], sumC_fit0_err[channels], sumC_fit1_err[channels];

   float gainA0[channels], gainA0_err[channels], gainA1[channels], gainA1_err[channels], gainB0[channels], gainB0_err[channels], gainB1[channels], gainB1_err[channels],gainC0[channels], gainC0_err[channels], gainC1[channels], gainC1_err[channels] ;

   i=0;
   j=0;

   for(irow=0; irow < lines; irow++){
     fitoff_tuple->GetEntry(irow);
     row_content = fitoff_tuple.GetArgs();
     
     if (row_content[2]==0 && row_content[1]==0){
       sumA_fit0[i]=row_content[4];
       sumA_fit0_err[i]=row_content[6];
       gainA0[i]=row_content[3];
       gainA0_err[i]=row_content[5];
       i++;
     }
     if (row_content[2]==1 && row_content[1]==0){
       sumB_fit0[j]=row_content[4];
       sumB_fit0_err[j]=row_content[6];
       gainB0[j]=row_content[3];
       gainB0_err[j]=row_content[5];
       j++;
     }

     if (row_content[2]==2 && row_content[1]==0){
       sumC_fit0[k]=row_content[4];
       sumC_fit0_err[k]=row_content[6];

       gainC0[k]=row_content[3];
       gainC0_err[k]=row_content[5];
       k++;
     }
     
      if (row_content[2]==0 && row_content[1]==1){
       sumA_fit1[l]=row_content[4];
       sumA_fit1_err[l]=row_content[6];

       gainA1[l]=row_content[3];
       gainA1_err[l]=row_content[5];
       
       l++;
     }
      if (row_content[2]==1 && row_content[1]==1){
       sumB_fit1[m]=row_content[4];
       sumB_fit1_err[m]=row_content[6];
       
       gainB1[m]=row_content[3];
       gainB1_err[m]=row_content[5];
       
       m++;
     }

      if (row_content[2]==2 && row_content[1]==1){
       sumC_fit1[n]=row_content[4];
       sumC_fit1_err[n]=row_content[6];
       
       gainC1[n]=row_content[3];
       gainC1_err[n]=row_content[5];
       
       n++;
     }
      
       
   }
   // for (i=0; i<channels; i++){
     //cout << sumA_fit0[i] << "  " << sumA_fit0_err[i] <<  endl;
     // cout << sumA_fit1[i] << "  " << sumA_fit1_err[i] <<  endl;
   
     // cout << sumB_fit0[i] << "  " << sumB_fit0_err[i] <<  endl;
     // cout << sumB_fit1[i] << "  " << sumB_fit1_err[i] <<  endl;

     // cout << sumC_fit0[i] << "  " << sumC_fit0_err[i] <<  endl;
     // cout << sumC_fit1[i] << "  " << sumC_fit1_err[i] <<  endl;
   // }

   //////////////PLOT EN MULTIGRAPH/////////////////////////////

   TCanvas *c1 = new TCanvas("All Offsets", "All Offsets", 1000,800);
   c1->SetGridx();
   c1->SetGridy();

   c1.Divide(1,2);
   


   c1.cd(1);
   c1->SetGridx();
   c1->SetGridy();

   TMultiGraph *mg1= new TMultiGraph();
   

   TGraphErrors *gr_analogA = new TGraphErrors(channels, channel, sumA_analog,0,0);

   gr_analogA->SetMarkerColor(1);
   gr_analogA->SetMarkerStyle(20);
   mg1->Add(gr_analogA);


 TGraphErrors *gr_analogB = new TGraphErrors(channels, channel, sumB_analog,0,0);

   gr_analogB->SetMarkerColor(2);
   gr_analogB->SetMarkerStyle(21);
   mg1->Add(gr_analogB);

  

TGraphErrors *gr_analogC = new TGraphErrors(channels, channel, sumC_analog,0,0);

   gr_analogC->SetMarkerColor(4);
   gr_analogC->SetMarkerStyle(22);
   mg1->Add(gr_analogC);


TGraphErrors *gr_digA0 = new TGraphErrors(channels, channel, sumA_dig0,0,0);

   gr_digA0->SetMarkerColor(3);
   gr_digA0->SetMarkerStyle(23);
   mg1->Add(gr_digA0);

TGraphErrors *gr_fitA0 = new TGraphErrors(channels, channel, sumA_fit0,0,sumA_fit0_err);

   gr_fitA0->SetMarkerColor(1);
   gr_fitA0->SetMarkerStyle(24);
   mg1->Add(gr_fitA0);

TGraphErrors *gr_fitB0 = new TGraphErrors(channels, channel, sumB_fit0,0,sumB_fit0_err);

   gr_fitB0->SetMarkerColor(2);
   gr_fitB0->SetMarkerStyle(25);
   mg1->Add(gr_fitB0);

TGraphErrors *gr_fitC0 = new TGraphErrors(channels, channel, sumC_fit0,0,sumC_fit0_err);

   gr_fitC0->SetMarkerColor(4);
   gr_fitC0->SetMarkerStyle(26);
   mg1->Add(gr_fitC0);


    mg1->Draw("ap1");
    mg1->SetTitle("Output 0");
    mg1->GetXaxis()->SetTitle("Channel");
    mg1->GetYaxis()->SetTitle("Offset[mV]");

    TLegend leg1(.76,0.73,.94,.99);
    leg1.SetFillColor(0);
    leg1.AddEntry(gr_analogA,"Analog offset, Adder A","1p");
    leg1.AddEntry(gr_analogB,"Analog offset, Adder B","1p");
    leg1.AddEntry(gr_analogC,"Analog offset, Adder C","1p");
    leg1.AddEntry(gr_digA0,"Digital offset, Adder A","1p");
    leg1.AddEntry(gr_fitA0,"Fit offset, Adder A","1p");
    leg1.AddEntry(gr_fitB0,"Fit offset, Adder B","1p");
    leg1.AddEntry(gr_fitC0,"Fit offset, Adder C","1p");



    leg1.DrawClone();

    gPad->Update();
    gPad->Modified();


    c1.cd(2);

     TMultiGraph *mg2= new TMultiGraph();

  
   mg2->Add(gr_analogA);
   mg2->Add(gr_analogB);
   mg2->Add(gr_analogC);


TGraphErrors *gr_digA1 = new TGraphErrors(channels, channel, sumA_dig1,0,0);

   gr_digA1->SetMarkerColor(3);
   gr_digA1->SetMarkerStyle(23);
   mg2->Add(gr_digA1);

TGraphErrors *gr_fitA1 = new TGraphErrors(channels, channel, sumA_fit1,0,sumA_fit1_err);

   gr_fitA1->SetMarkerColor(1);
   gr_fitA1->SetMarkerStyle(24);
   mg2->Add(gr_fitA0);

TGraphErrors *gr_fitB1 = new TGraphErrors(channels, channel, sumB_fit1,0,sumB_fit1_err);

   gr_fitB1->SetMarkerColor(2);
   gr_fitB1->SetMarkerStyle(25);
   mg2->Add(gr_fitB1);

TGraphErrors *gr_fitC1 = new TGraphErrors(channels, channel, sumC_fit1,0,sumC_fit1_err);

   gr_fitC1->SetMarkerColor(4);
   gr_fitC1->SetMarkerStyle(26);
   mg2->Add(gr_fitC1);


    mg2->Draw("ap1");
    mg2->SetTitle("Output 1");
    mg2->GetXaxis()->SetTitle("Channel");
    mg2->GetYaxis()->SetTitle("Offset[mV]");

    TLegend leg2(.76,0.73,.94,.99);
    leg2.SetFillColor(0);
    leg2.AddEntry(gr_analogA,"Analog offset, Adder A","1p");
    leg2.AddEntry(gr_analogB,"Analog offset, Adder B","1p");
    leg2.AddEntry(gr_analogC,"Analog offset, Adder C","1p");
    leg2.AddEntry(gr_digA1,"Digital offset, Adder A","1p");
    leg2.AddEntry(gr_fitA1,"Fit offset, Adder A","1p");
    leg2.AddEntry(gr_fitB1,"Fit offset, Adder B","1p");
    leg2.AddEntry(gr_fitC1,"Fit offset, Adder C","1p");



    leg2.DrawClone();

    c1->SaveAs("alloffsets.pdf");

    gPad->Update();
    gPad->Modified();


    TCanvas *c2= new TCanvas("Gain","Gain", 1000,800);

    c2->SetGridx();
    c2->SetGridy();

   c2.Divide(1,2);
   


   c2.cd(1);
   c2->SetGridx();
   c2->SetGridy();

    TMultiGraph *mg3= new TMultiGraph();
   

    TGraphErrors *gr_gainA0 = new TGraphErrors(channels, channel, gainA0,0,gainA0_err);

   gr_gainA0->SetMarkerColor(1);
   gr_gainA0->SetMarkerStyle(20);
   mg3->Add(gr_gainA0);


   TGraphErrors *gr_gainB0 = new TGraphErrors(channels, channel, gainB0,0,gainB0_err);

   gr_gainB0->SetMarkerColor(2);
   gr_gainB0->SetMarkerStyle(21);
   mg3->Add(gr_gainB0);

 TGraphErrors *gr_gainC0 = new TGraphErrors(channels, channel, gainC0,0,gainC0_err);

   gr_gainC0->SetMarkerColor(4);
   gr_gainC0->SetMarkerStyle(22);
   mg3->Add(gr_gainC0);
    

    mg3->Draw("ap1");
    mg3->SetTitle("Output 0");
    mg3->GetXaxis()->SetTitle("Channel");
    mg3->GetYaxis()->SetTitle("Gain[mV]");

    TLegend leg3(.76,0.73,.94,.99);
    leg3.SetFillColor(0);
    leg3.AddEntry(gr_gainA0,"Fit Gain, Adder A","1p");
    leg3.AddEntry(gr_gainB0,"Fit Gain, Adder B","1p");
    leg3.AddEntry(gr_gainC0,"Fit Gain, Adder C","1p");



    leg3.DrawClone();

    gPad->Update();
    gPad->Modified();


    c2.cd(2);
    c2->SetGridx();
    c2->SetGridy();

    TMultiGraph *mg4= new TMultiGraph();
   

    TGraphErrors *gr_gainA1 = new TGraphErrors(channels, channel, gainA1,0,gainA1_err);

   gr_gainA1->SetMarkerColor(1);
   gr_gainA1->SetMarkerStyle(20);
   mg4->Add(gr_gainA1);


   TGraphErrors *gr_gainB1 = new TGraphErrors(channels, channel, gainB0,0,gainB0_err);

   gr_gainB1->SetMarkerColor(2);
   gr_gainB1->SetMarkerStyle(21);
   mg4->Add(gr_gainB1);

 TGraphErrors *gr_gainC1 = new TGraphErrors(channels, channel, gainC0,0,gainC0_err);

   gr_gainC1->SetMarkerColor(4);
   gr_gainC1->SetMarkerStyle(22);
   mg4->Add(gr_gainC1);
    

    mg4->Draw("ap1");
    mg4->SetTitle("Output 1");
    mg4->GetXaxis()->SetTitle("Channel");
    mg4->GetYaxis()->SetTitle("Gain[mV]");

    TLegend leg4(.76,0.73,.94,.99);
    leg4.SetFillColor(0);
    leg4.AddEntry(gr_gainA0,"Fit Gain, Adder A","1p");
    leg4.AddEntry(gr_gainB0,"Fit Gain, Adder B","1p");
    leg4.AddEntry(gr_gainC0,"Fit Gain, Adder C","1p");



    leg4.DrawClone();

    c2->SaveAs("gain.pdf");

    gPad->Update();
    gPad->Modified();


    




}
