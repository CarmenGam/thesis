{
  gROOT->Reset();

 // Read back the ntuple
  TFile foffset("fit_offset.root");
  TNtuple* offset_tupleP=(TNtuple*)foffset.Get("OffsetFit");
  TNtuple &offset_tuple=*offset_tupleP; // Carlos is lazy, para no tener que escribir -

  TFile fanalog("analog_offset.root");
  TNtuple* analog_tupleP=(TNtuple*)fanalog.Get("Analog");
  TNtuple &analog_tuple=*analog_tupleP;
  
  double asic, fit, fiterr, analog;


  ofstream a_file("offset_diff.txt");

  for (int disc = 0; disc < 2; disc ++){

    for (int channel=0; channel < 7; channel ++){

      for (int sum = 0; sum < 3; sum++){
      
	

	offset_tuple.Draw(
			  "offset:offseterr",
			  Form("disc==%i && channel==%i &&  sum==%i",disc,channel,sum),
			  "goff");		
	analog_tuple.Draw(
			  Form("asic:sum%c",'A'+sum),
			  Form("channel==%i", channel+1),
			  "goff");
	asic = *analog_tuple.GetV1();
	analog = *analog_tuple.GetV2();
	fit = *offset_tuple.GetV1();
	fiterr = *offset_tuple.GetV2();

	a_file<< asic << "\t" << disc << "\t" << channel << "\t" << sum << "\t" << 
	  fit << "\t" << analog << "\t" << fiterr << "\t" << fit-analog << "\t" << 
	  (fit-analog)/fiterr << endl;
	

      }


    }

  }

}
