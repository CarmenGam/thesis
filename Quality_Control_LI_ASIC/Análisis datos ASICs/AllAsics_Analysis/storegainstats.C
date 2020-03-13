void storegainstats(){

TFile fascis("gainstats.root","RECREATE");
    TNtuple
   
analog("Gain","Gain","disc:channel:sum:rms:mean");
    analog.ReadFile("gainall.txt");
    analog.Write();

}
