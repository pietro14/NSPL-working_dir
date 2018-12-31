#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace TMath;

string run;
int off_ped_mean;
int off_ped_width;
char name[30];
char chComm[]   = "#";
char *delim = ":";
int rlen,bid,chid,event,pattern,dac,bin,headl,nwords,idcell;
float adc;
unsigned long int triggertime;

ifstream Data_File0; 
ifstream Data_File1;
TFile *rootfile;


/*
TH1F * h_time;
TH1F * h_adc;
TH1F * h_adcTot;
TH1F * h_adcTot_low;
TH1F * h_adcInt;
TH1F * h_nbin1;
TH1F * h_charge1;
TH1F * h_nbin2;
TH1F * h_charge2;
TH1F * h_intervallo;
*/
TF1* fd;
TGraph * h_signal;
TGraph * h_signal1;

TTree * digi_tree;
int nbins;
int ev_no;
int ch_no;
vector<int> data_bin;
vector<int> data_value;
int nbins_ch1;
int ev_no_ch1;
int ch_no_ch1;
vector<int> data_bin_ch1;
vector<int> data_value_ch1;

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

void initialize();
void finalize();
void process_data(int totevents);
bool read_event_header_ch0();
bool read_event_header_ch1();
void read_event_data_ch0();
void read_event_data_ch1();
void skip_event_data_ch0();
void skip_event_data_ch1();
void event_analysis();
void book_histos();
