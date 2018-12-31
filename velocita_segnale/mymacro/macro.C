
{
#define NUMBER_OF_SIGNALS 2890
#define FILE "wave_1.txt"
  //#define FILE "wave_0.txt"
  
  
   
  TF1 *fermi_dirac = new TF1("fermi_dirac", "[0]-[1]/(exp(-(x[0]-[2])*[3])+1)");
  fermi_dirac->SetParameters(4034,3003,79,2);
  
  //quali errori assegnare alle tensioni e ai tempi (e se assegnarli)??

  int n = NUMBER_OF_SIGNALS;
  string useless_string;
  TH1D * histo = new TH1D("histo","istogramma dei tempi corrispondenti a (V_max+V_min)/2", 120, 50 ,1000);
  TGraph * g = new TGraph[n];
  Double_t V[1024], t[1024];
  t[0]= 0;
  
  ifstream myReadFile;
  myReadFile.open(FILE);
  for(int j=0; j<n; j++) {
    for(int k=0; k<24; k++){  //24 è il numero di stringhe iniziali "inutili" per ogni segnale
      myReadFile >> useless_string;
    };
    for(int i=0; i<1024; i++) {
      myReadFile >> V[i];
      t[i] =+ i*0.2;
    };   
    g[j] = TGraph(1024, t, V);
    g[j].Fit("fermi_dirac","Q");
    histo->Fill( fermi_dirac->GetParameter(2) );
    cout <<fixed<< "\r" <<"Progress= " <<100.*j/n  << " %"  << flush ; 
  }
  myReadFile.close();
  
  
  TCanvas * c1 = new TCanvas();
  // c1->Divide(1,2);
  //c1->cd(1);
  //g[0].Draw("PA*");     //disegna e fitta il primo segnale
  //g[0].Fit("fermi_dirac");
  //c1->cd(2);
  histo->Draw();
     
  
};
