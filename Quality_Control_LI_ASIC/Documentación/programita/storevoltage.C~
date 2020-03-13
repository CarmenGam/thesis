


void storevoltage(){
 

  TFile ofile("voltage.root","RECREATE");
    TNtuple t("t","ejemplo","asic:channel:discriminator:mv:sumA:sumB:sumC");
    t.ReadFile("voltage.txt");
    t.Write();

}
 
