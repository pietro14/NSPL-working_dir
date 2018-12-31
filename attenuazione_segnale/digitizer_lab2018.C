/*****
ROOT macro
example for CAEN digitizer analysis
single channel example
 *****/

#include "digitizer_lab2018.h"

void digitizer_lab2018()
{

  //choose the run number
  run="1";
  int totevents=143;
  off_ped_mean=0;
  off_ped_width=0;
  
  cout<<" inizializing..."<<endl;
  initialize();
  cout<<"         ...done"<<endl;
  //    
  cout<<" processing data..."<<endl;
  process_data(totevents);
  cout<<"            ...done"<<endl;
  cout<<" finalizing..."<<endl;
  finalize();
  cout<<"       ...done"<<endl;
}

void book_histos(){
  /*
  h_adc=new TH1F("adc","adc",350,0.,350.);
  h_adcTot= new TH1F("adcTot","adcTot", 4000,0.,40000.);
  h_adcTot_low= new TH1F("adcTot_low","adcTot_low", 400,0.,400.);
  h_adcInt= new TH1F("adcInt","adcInt", 1000,0.,100000000.);
  h_time=new TH1F("h_time","Time [4ns]",2000,-100,100);
  */
  h_signal= new TGraph();  
  h_signal->SetMarkerStyle(21);
  h_signal1= new TGraph();  
  h_signal1->SetMarkerStyle(21);
  fd=new TF1("fd","[0]/(1+exp(((-x+[1])/[2])))+[3]",0,100);

  digi_tree=new TTree("digi_tree","digitizer tree");  
  digi_tree->Branch("ev_no",&ev_no,"ev_no/I");
  digi_tree->Branch("ch_no",&ch_no,"ch_no/I");
  digi_tree->Branch("nbins",&nbins,"nbins/I");
  digi_tree->Branch("data_bin",&data_bin);
  digi_tree->Branch("data_value",&data_value);

  digi_tree->Branch("ev_no_ch1",&ev_no_ch1,"ev_no_ch1/I");
  digi_tree->Branch("ch_no_ch1",&ch_no_ch1,"ch_no_ch1/I");
  digi_tree->Branch("nbins_ch1",&nbins_ch1,"nbins_ch1/I");
  digi_tree->Branch("data_bin_ch1",&data_bin_ch1);
  digi_tree->Branch("data_value_ch1",&data_value_ch1);
  
}


void process_data(int totevents){
  //process data files from the CAEN digitizer.
  //files are written with an header and contains only one channel
  //a TTree is filled and written to a file
  //int max_events=3600;
  int max_events=totevents;
  event=-1;
  int myevent=0;
  while(myevent<max_events){
    cout<< "    ....processing event "<<myevent<<endl;
      nbins=0;
      data_bin.clear();
      data_value.clear();
      read_event_header_ch0();
      cout<<" after read event header ch0, event "<<ev_no<<endl;
      read_event_data_ch0();
      if(ev_no==myevent-1) break;
      
      nbins_ch1=0;
      data_bin_ch1.clear();
      data_value_ch1.clear();
      read_event_header_ch1();
      cout<<" after read event header ch1, event "<<ev_no_ch1<<endl;
      read_event_data_ch1();
      if(ev_no_ch1==myevent-1) break;

      event_analysis();
      
      myevent++;
  }

}

void open_files(){
  //open input file(s)
  //string dir = "../" ;
  string dir="";
  //string data_file1 = dir+"run"+run+"_wave_1.txt";
  //string data_file0 = dir+"run"+run+"_wave_0.txt";
  string data_file1 = dir+"wave_1.txt";
  string data_file0 = dir+"wave_0.txt";
  Data_File0.open(data_file0.c_str());
  Data_File1.open(data_file1.c_str());
  if(!Data_File0){cout << "Impossibile aprire file " << data_file0<<endl; return;} 
  if(!Data_File1){cout << "Impossibile aprire file " << data_file1<<endl; return;} 

  //open root file
  string root_file = "run"+run+"_wave.root";
  rootfile= new TFile(root_file.c_str(),"recreate");
  //rootfile= new TFile(root_file.c_str(),"read");
}

void event_analysis(){
  //h_adc->Fill((float)adc);
	digi_tree->Fill();
}
void initialize(){
  //opening files
  open_files();  
  //book histos and trees 
  book_histos();
}

void finalize(){
  digi_tree->Write();
}

bool read_event_header_ch0(){
      Data_File0.getline(name,30,*delim);
      cout<<" reading: "<<name<<" ch0"<<endl;
      if (strncmp(name,"Record Length",7)==0 ){
	Data_File0>>rlen;
	//start event
	headl=1;
	//cout<<"Record Length: "<<rlen<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"BoardID",7)==0 ){
	Data_File0>>bid;
	headl++;
	//cout<<"BID: "<<bid<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"Channel",7)==0 ){
	Data_File0>>ch_no;
	headl++;
	//cout<<"CHID: "<<chid<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"Event Number",12)==0 ){
	Data_File0>>ev_no;
	headl++;
	//cout<<"event: "<<event<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"Pattern",7)==0 ){
	Data_File0>>hex>>pattern>>dec;
	headl++;
	//cout<<"pattern: "<<hex<<pattern<<dec<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"Trigger Time Stamp",18)==0 ){
	Data_File0>>triggertime;
	headl++;
	//cout<<"triggertime: "<<triggertime<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      if (strncmp(name,"DC offset (DAC)",15)==0 ){
	Data_File0>>hex>>dac>>dec;
	headl++;
	//cout<<"dac: "<<hex<<dac<<dec<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File0.getline(name,30);
      }
      Data_File0.getline(name,30,*delim);
      //cout<<" reading: "<<name<<endl;
      if (strncmp(name,"Start Index Cell",16)==0 ){
	Data_File0>>idcell;
	headl++;
	//cout<<"id cell: "<<idcell<<" "<<headl<<endl;
	//read the end og the line to move on
	//Data_File0.getline(name,30);
      } 
      
      if(headl!=8){
	cout<<"corrupted header! last word read:  "<<name<<endl;
	cout<<"Record Length: "<<rlen<<" "<<headl<<endl;
	cout<<"BID: "<<bid<<" "<<headl<<endl;
	cout<<"CHID: "<<ch_no<<" "<<headl<<endl;
	cout<<"event: "<<ev_no<<" "<<headl<<endl;
	cout<<"pattern: "<<hex<<pattern<<dec<<" "<<headl<<endl;
	cout<<"triggertime: "<<triggertime<<" "<<headl<<endl;
	cout<<"dac: "<<hex<<dac<<dec<<" "<<headl<<endl;
	cout<<"id cell: "<<idcell<<" "<<headl<<endl;
	return false;;
      }
      return true;
}

bool read_event_header_ch1(){
      Data_File1.getline(name,30,*delim);
      cout<<" reading: "<<name<<" ch1"<<endl;
      if (strncmp(name,"Record Length",7)==0 ){
	Data_File1>>rlen;
	//start event
	headl=1;
	//cout<<"Record Length: "<<rlen<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"BoardID",7)==0 ){
	Data_File1>>bid;
	headl++;
	//cout<<"BID: "<<bid<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"Channel",7)==0 ){
	Data_File1>>ch_no_ch1;
	headl++;
	//cout<<"CHID: "<<chid<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"Event Number",12)==0 ){
	Data_File1>>ev_no_ch1;
	headl++;
	//cout<<"event: "<<event<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"Pattern",7)==0 ){
	Data_File1>>hex>>pattern>>dec;
	headl++;
	//cout<<"pattern: "<<hex<<pattern<<dec<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"Trigger Time Stamp",18)==0 ){
	Data_File1>>triggertime;
	headl++;
	//cout<<"triggertime: "<<triggertime<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      if (strncmp(name,"DC offset (DAC)",15)==0 ){
	Data_File1>>hex>>dac>>dec;
	headl++;
	//cout<<"dac: "<<hex<<dac<<dec<<" "<<headl<<endl;
	//read the end og the line to move on
	Data_File1.getline(name,30);
      }
      Data_File1.getline(name,30,*delim);
      //cout<<" reading: "<<name<<endl;
      if (strncmp(name,"Start Index Cell",16)==0 ){
	Data_File1>>idcell;
	headl++;
	//cout<<"id cell: "<<idcell<<" "<<headl<<endl;
	//read the end og the line to move on
	//Data_File1.getline(name,30);
      } 
      
      if(headl!=8){
	cout<<"corrupted header! last word read:  "<<name<<endl;
	cout<<"Record Length: "<<rlen<<" "<<headl<<endl;
	cout<<"BID: "<<bid<<" "<<headl<<endl;
	cout<<"CHID: "<<ch_no_ch1<<" "<<headl<<endl;
	cout<<"event: "<<ev_no_ch1<<" "<<headl<<endl;
	cout<<"pattern: "<<hex<<pattern<<dec<<" "<<headl<<endl;
	cout<<"triggertime: "<<triggertime<<" "<<headl<<endl;
	cout<<"dac: "<<hex<<dac<<dec<<" "<<headl<<endl;
	cout<<"id cell: "<<idcell<<" "<<headl<<endl;
	return false;
      }
      return true;
}

void read_event_data_ch0(){
      if(headl==8){
	for(int jj=0; jj<rlen; jj++){
	  //Data_File0>>name;
	  //bin=atoi(name);
	  Data_File0>>adc;
	  //cout<<" read event data: "<<jj<<" "<<bin<<" "<<adc<<endl;
	  nbins++;
	  bin=nbins;
	  if((adc-off_ped_mean)>off_ped_width){
	    data_bin.push_back(bin);
	    data_value.push_back((int)adc);
	  }
	}
      } else {
	cout<<"CORRUPTED EVENT!! event number= "<<event<<" header lenght= "<<headl<<" last word read: "<<name<<endl;
	return;
      }
	//read the end og the line to move on
	Data_File0.getline(name,30);
}
void read_event_data_ch1(){
      if(headl==8){
	for(int jj=0; jj<rlen; jj++){
	  //Data_File0>>name;
	  //bin=atoi(name);
	  Data_File1>>adc;
	  //cout<<" read event data: "<<jj<<" "<<bin<<" "<<adc<<endl;
	  nbins_ch1++;
	  bin=nbins_ch1;
	  if((adc-off_ped_mean)>off_ped_width){
	    data_bin_ch1.push_back(bin);
	    data_value_ch1.push_back((int)adc);
	  }
	}
      } else {
	cout<<"CORRUPTED EVENT!! event number= "<<event<<" header lenght= "<<headl<<" last word read: "<<name<<endl;
	return;
      }
	//read the end og the line to move on
	Data_File1.getline(name,30);
}
void skip_event_data_ch0(){
      if(headl==8){
	for(int jj=0; jj<rlen; jj++){
	  Data_File1.getline(name,30);
	  /*
	  Data_File0>>name;
	  bin=atoi(name);
	  Data_File0>>adc;
	  */
	  cout<<" skip event data: "<<name<<endl;
	  
	}
      } else {
	cout<<"CORRUPTED EVENT!! event number= "<<event<<" header lenght= "<<headl<<" last word read: "<<name<<endl;
	return;
      }
}
void skip_event_data_ch1(){
      if(headl==8){
	for(int jj=0; jj<rlen; jj++){
	  Data_File1.getline(name,30);
	  /*
	  Data_File1>>name;
	  bin=atoi(name);
	  Data_File1>>adc;
	  */
	  cout<<" skip event data: "<<name<<endl;
	  
	}
      } else {
	cout<<"CORRUPTED EVENT!! event number= "<<event<<" header lenght= "<<headl<<" last word read: "<<name<<endl;
	return;
      }
}
