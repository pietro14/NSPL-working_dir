

{



TCanvas * draw_canvas=new TCanvas("draw_canvas","draw_canvas");
   //definizione di un frame per visualizzare il segnale


 double e_charge[3]={2.8e2, 1.85e2, 1.43e2};
 double e_distance[3]={5,5,5}; //mettere l'incertezza giusta
 double distance[3] = {65, 91.3, 116.9};
 double charge[3] = {1.475e5, 8.96e4, 6.34e4};




 TGraphErrors* g  = new TGraphErrors(3 ,distance, charge, e_distance, e_charge);
 

 
    
 // TF1 *f = new TF1("retta","[0]*x+[1]", 0, 100);

 // g->Fit("retta");
    

    g->SetMarkerStyle(40); 
    g->SetMarkerSize(0.4);
        
    g->GetXaxis()->SetTitle("#Deltax [cm]");
    g->GetYaxis()->SetTitle("#Deltaq [??]");
    g->Draw("AP");
 
  


}

