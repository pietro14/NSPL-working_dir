#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TH1D.h>


TF1 *fermi_dirac = new TF1("fermi_dirac", "[0]-[1]/(exp(-(x[0]-[2])*[3])+1)");

TH1D *myhisto = new TH1D("myhisto","" ,100 , 10, 50); 


void Analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analysis.C
//      root> Analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<2000/*nentries*/;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      
      fermi_dirac->SetParameters(4034,3003,79,2);
  TGraph * gr_ch0 = new TGraph();
  TGraph * gr_ch1 = new TGraph();

   for(int i=0; i<1024; i++){	
	// qui dentro tutto quello che si vuole

	// ad esempio, riempire un grafico col segnale del canale 0
	gr_ch0->SetPoint(i,(float)data_bin->at(i),(float)data_value->at(i));
	gr_ch1->SetPoint(i,(float)data_bin_ch1->at(i),(float)data_value_ch1->at(i));
   }

      double t_fit_ch0;
      double t_fit_ch1;
      
      gr_ch0->Fit("fermi_dirac","Q");

      t_fit_ch0 = fermi_dirac->GetParameter(2);
      
      gr_ch1->Fit("fermi_dirac","Q");
      
      t_fit_ch1 = fermi_dirac->GetParameter(2);


      double delta_t = fabs(t_fit_ch0 - t_fit_ch1);

      myhisto->Fill(delta_t);

      cout << fixed << "\r" <<"Progress= " <<100.*jentry/2000/*nentries*/  << " %"  << flush ; 
      
      
   }

   TCanvas * c1 = new TCanvas();

   myhisto->Draw();
   
}
