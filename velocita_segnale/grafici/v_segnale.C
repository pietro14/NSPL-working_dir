


{



TCanvas * draw_canvas=new TCanvas("draw_canvas","draw_canvas");
   //definizione di un frame per visualizzare il segnale


 double e_delta_time[]={0.011, 0.0106, 0.0128};   //mettere l'incertezza giusta
 double e_distance[]={2.89,2.89,2.89}; //mettere l'incertezza giusta
 
 double distance[] = {91.3, 65,116.9
 
};



 double delta_time[] = {50.15, 48.07, 52.08
 
};



 TGraphErrors* g  = new TGraphErrors(3 ,distance, delta_time, e_distance, e_delta_time);
 

 
    
    TF1 *f = new TF1("retta","[0]*x+[1]", 0, 100);
    f->SetParName(0,"v^{-1} [ns/cm]");
    f->SetParName(1,"#Deltat_{0} [ns]");
    
    g->Fit("retta");
    
    g->SetMarkerSize(0.4);
    
    g->GetXaxis()->SetTitle("d [cm]");
    g->GetYaxis()->SetTitle("#Deltat [ns]");
    g->Draw("AP");
 
  


}

