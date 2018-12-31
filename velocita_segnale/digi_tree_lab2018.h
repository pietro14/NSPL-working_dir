//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 17 11:59:01 2013 by ROOT version 5.30/02
// from TTree digi_tree/digitizer tree
// found on file: run148_wave.root
//////////////////////////////////////////////////////////

#ifndef digi_tree_h
#define digi_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

TH1F * h_adc;
TH1F * h_adcTot;
TH1F * h_adcTot_low;
TH1F * h_adcInt;
TH1F * h_thr_time;

TString RootFile;

class digi_tree {
public :   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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

   digi_tree(TString run="0", TTree *tree=0);
   virtual ~digi_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef digi_tree_cxx
digi_tree::digi_tree(TString run,TTree *tree)
{
  RootFile+="run";
  RootFile+=run;
  RootFile+="_wave.root";
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
   if (tree == 0) {
     //test if rootfile with a tree already loaded
     tree = (TTree*)gROOT->FindObject("digi_tree");
     if (tree == 0) {
       cout<<" TTree not found, opening file "<<RootFile.Data()<<endl;
       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(RootFile.Data());
       if (!f || !f->IsOpen()) {
	 f = new TFile(RootFile.Data());
       }
       f->GetObject("digi_tree",tree);
     }
   }
   Init(tree);
}

digi_tree::~digi_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t digi_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t digi_tree::LoadTree(Long64_t entry)
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

void digi_tree::Init(TTree *tree)
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
   
  h_adc=new TH1F("adc","adc",350,0.,350.);
  h_adcTot= new TH1F("adcTot","adcTot", 4000,0.,40000.);
  h_adcTot_low= new TH1F("adcTot_low","adcTot_low", 400,0.,400.);
  h_adcInt= new TH1F("adcInt","adcInt", 1000,0.,100000000.);
  h_thr_time= new TH1F("h_thr_time","h_thr_time",520,0,520.); 
}

Bool_t digi_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void digi_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t digi_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef digi_tree_cxx
