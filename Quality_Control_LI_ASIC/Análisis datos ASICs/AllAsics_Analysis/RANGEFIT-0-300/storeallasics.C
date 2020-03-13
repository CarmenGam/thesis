void storeallasics(){

TFile fascis("allasicsdata.root","RECREATE");
    TNtuple
   
analog("Asics","Asics","asic:disc:channel:sum:fitoffset:analog:fiterr:diff:differr:gain:gainerr:digoffset:noise");
    analog.ReadFile("allasicsdata.txt");
    analog.Write();

}
