

{



TCanvas * draw_canvas=new TCanvas("draw_canvas","draw_canvas");
   //definizione di un frame per visualizzare il segnale


 double e_charge[3]={330, 311,223.4};
 double e_distance[3] = {2.89,2.89,2.89}; //mettere l'incertezza giusta
 double distance[3] = {65, 91.3, 116.9};
 double charge[3] = {2712, 1600, 1076};




 TGraphErrors* g  = new TGraphErrors(3 ,distance, charge, e_distance, e_charge);
 

 
    
 // TF1 *f = new TF1("retta","[0]*x+[1]", 0, 100);

 // g->Fit("retta");
    

    g->SetMarkerStyle(40); 
    g->SetMarkerSize(0.4);
        
    g->GetXaxis()->SetTitle("#Deltax [cm]");
    g->GetYaxis()->SetTitle("#Deltaq [??]");
    g->Draw("AP");
 
  


}

