//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May 14 16:36:14 2018 by ROOT version 6.12/06
// from TTree digi_tree/digitizer tree
// found on file: run1_wave.root
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class Analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ev_no;
   Int_t           ch_no;
   Int_t           nbins;
   vector<int>     *data_bin;
   vector<int>     *data_value;
   Int_t           ev_no_ch1;
   Int_t           ch_no_ch1;
   Int_t           nbins_ch1;
   vector<int>     *data_bin_ch1;
   vector<int>     *data_value_ch1;

   // List of branches
   TBranch        *b_ev_no;   //!
   TBranch        *b_ch_no;   //!
   TBranch        *b_nbins;   //!
   TBranch        *b_data_bin;   //!
   TBranch        *b_data_value;   //!
   TBranch        *b_ev_no_ch1;   //!
   TBranch        *b_ch_no_ch1;   //!
   TBranch        *b_nbins_ch1;   //!
   TBranch        *b_data_bin_ch1;   //!
   TBranch        *b_data_value_ch1;   //!

   Analysis(TTree *tree=0);
   virtual ~Analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("run1_wave.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("run1_wave.root");
      }
      f->GetObject("digi_tree",tree);

   }
   Init(tree);
}

Analysis::~Analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   data_bin = 0;
   data_value = 0;
   data_bin_ch1 = 0;
   data_value_ch1 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ev_no", &ev_no, &b_ev_no);
   fChain->SetBranchAddress("ch_no", &ch_no, &b_ch_no);
   fChain->SetBranchAddress("nbins", &nbins, &b_nbins);
   fChain->SetBranchAddress("data_bin", &data_bin, &b_data_bin);
   fChain->SetBranchAddress("data_value", &data_value, &b_data_value);
   fChain->SetBranchAddress("ev_no_ch1", &ev_no_ch1, &b_ev_no_ch1);
   fChain->SetBranchAddress("ch_no_ch1", &ch_no_ch1, &b_ch_no_ch1);
   fChain->SetBranchAddress("nbins_ch1", &nbins_ch1, &b_nbins_ch1);
   fChain->SetBranchAddress("data_bin_ch1", &data_bin_ch1, &b_data_bin_ch1);
   fChain->SetBranchAddress("data_value_ch1", &data_value_ch1, &b_data_value_ch1);
   Notify();
}

Bool_t Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis_cxx
