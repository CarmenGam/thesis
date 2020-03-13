
//Este Macro guarda los datos del fichero voltage.txt en un fichero tipo root para su futura interpretación. 

void storevoltage(){
 

  TFile ofile("voltage.root","RECREATE");
    TNtuple t("t","ejemplo","asic:channel:discriminator:mv:sumA:sumB:sumC");
    t.ReadFile("voltage.txt");
    t.Write();

}
 
