//Este Macro guarda los datos que salen del ASIC en formato root. 
void storedata(){
 

  TFile infile("input_signal.root","RECREATE");
    TNtuple input("Input","Input","time:channel1:channel2:channel3:channel4:channel5:channel6:channel7:threshold");
    input.ReadFile("data.txt");
    input.Write();
    

    TFile fadder("adder.root","RECREATE");
    TNtuple adder("Adder","Adder", "time:adderA:adderB:adderC");
    adder.ReadFile("adder.txt");
    adder.Write();

    TFile fcomp("comp.root","RECREATE");
    TNtuple comp("Comparator","Comparator", "time:Comp1:Comp2:Comp3");
    comp.ReadFile("comp.txt");
    comp.Write();


}
