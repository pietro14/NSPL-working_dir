#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include "accettanza.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TF1.h"
#include "TMath.h"

using namespace std;

int accettanza()
{
  //initialize the random generator
  srand(time(0));
  
  TFile* outfile = new TFile("accettanza.root","RECREATE");


  // TF1* f1 = new TF1("myfun","[0]*cos(x)*cos(x)*cos(x)*sin(x)",0,5);

  TH1D* h_theta_1 = new TH1D("h_theta_1","theta_1",160,0,1.6);
  TH1D* h_phi_1 = new TH1D("h_phi_1","phi_1",630,0,6.3);
  TH1D* h_theta_2 = new TH1D("h_theta_2","theta_2",160,0,1.6);
  TH1D* h_phi_2 = new TH1D("h_phi_2","phi_2",630,0,6.3);

  TH1D* h_x_2 = new TH1D("h_x_2","x_2",2500,0,25);
  TH1D* h_y_2 = new TH1D("h_y_2","y_2",1250,0,125);
  TH1D* h_x_1 = new TH1D("h_x_1","x_1",2500,0,25);
  TH1D* h_y_1 = new TH1D("h_y_1","y_1",1250,0,125);


  double d = 14;  // 12; //distanza tra i due scintillatori (cm)
  

  int counter = 0;
  for(int i=0; i<1e6; i++){
        

    double theta_ang=theta();
    double phi_ang=phi();
    double x=ascissa();
    double y=ordinata();
    
    double  x_down = x - d * tan(theta_ang)*cos(phi_ang)  ;
    double  y_down = y - d * tan(theta_ang)*sin(phi_ang)  ;
 
    if( x_down > 0  && y_down > 0  && x_down < 20.  && y_down < 122. ){
      
      h_theta_2->Fill(theta_ang);    
      h_phi_2->Fill(phi_ang);
      h_x_2->Fill(x);
      h_y_2->Fill(y);
      

      counter ++;

    
    };
    
    h_theta_1->Fill(theta_ang);
    h_phi_1->Fill(phi_ang);
    h_x_1->Fill(x);
    h_y_1->Fill(y);

  };

  // h_theta_1->Fit("myfun","","",0,M_PI/2.);


  //comando per disegnare istogramma normalizzato: histo->DrawNormalized("same")

  outfile->Write();

  cout << endl << "accettanza = "  << (double)counter / 1e6 << endl ; 

}

double myrand(){
  //generate a pseudo random number in the interval [-1;1]
  double r,sign;
  r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  sign=1.; 
  if(r<0.5) sign=-1.;
  r = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  r=r*sign;
  //  cout<<"  myrand: "<<r<<endl;
  return r;
}
double myrandpos(){
  //generate a pseudo random number in the interval [0;1]
  double r;
  r =  (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  //cout<<"  myrandpos: "<<r<<endl;
  return r;
}









double theta(){
   double x;
   double f;
 
  do {
    x = (M_PI/2.) * (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
    f = (3.*sqrt(3)/4) * (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  }while(f > (4)*cos(x)*cos(x)*cos(x)*sin(x));

  return x;
}




double phi(){
  double r;
  r = 2*M_PI * (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
  //cout<<"  myrandpos: "<<r<<endl;
  return r;
}



double ascissa(){
  double r;
  double r_max = 20; //cm
 
  r = r_max * (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
 

  return r;
}


double ordinata(){
  double r;
  double r_max = 122; //cm
 
  r = r_max * (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );
 

  return r;
}
