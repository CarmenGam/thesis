#include "TMath.h"
#include "TH1D.h"
#include <iostream>
using namespace std;

double sinc(double t1, double t2,double B)
{
  const double PI=TMath::Pi(); 
  if (t1==t2){
    return 1;
  }
      
  // return (sin((t1-t2)*2*PI*B)/((t1-t2)*PI));

  else 
    return sin((t1-t2)*2*PI*B)/(PI*(t1-t2));
  
}



double gaus(double x,double mu,double sigma){
  x-=mu;
  x/=sigma;
  return exp(-0.5*x*x)/sqrt(2*TMath::Pi())/sigma;
}


void convolution(TH1D &h0,double B){
  // ONE CONDITION: B*2<< 1/delta_t -> for the integral approximation
  // SECOND CONDITION: 


  TH1D result=h0;
  result.Reset();


  for(int i=1;i<=result.GetNbinsX();i++){
    double t0=result.GetXaxis()->GetBinCenter(i);

    double sum=0;
    double integral=0;
    for(int j=1;j<=h0.GetNbinsX();j++){
      double t1=h0.GetXaxis()->GetBinCenter(j);
      double integrando=sinc(t0,t1,B)*h0.GetXaxis()->GetBinWidth(j);
      sum+=h0.GetBinContent(j)*integrando;
      integral+=integrando;
    }
    result.SetBinContent(i,sum/integral);
    //    cout<<"INTEGRAL "<<integral<<" for "<<t0<<endl;
  }


  h0=result;
}


