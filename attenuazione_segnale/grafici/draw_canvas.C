void draw_canvas()
{
//=========Macro generated from canvas: draw_canvas/draw_canvas
//=========  (Wed May 23 19:08:53 2018) by ROOT version 6.12/06
   TCanvas *draw_canvas = new TCanvas("draw_canvas", "draw_canvas",10,52,700,500);
   gStyle->SetOptFit(1);
   draw_canvas->Range(44.525,42126.25,137.375,168910.8);
   draw_canvas->SetFillColor(0);
   draw_canvas->SetBorderMode(0);
   draw_canvas->SetBorderSize(2);
   draw_canvas->SetFrameBorderMode(0);
   draw_canvas->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1001[3] = {
     65,
     91.3,
     116.9};
   Double_t Graph0_fy1001[3] = {
   147500,
   89600,
   63400};
   Double_t Graph0_fex1001[3] = {
2.89,
2.89,
2.89};
   Double_t Graph0_fey1001[3] = {
      280,  
      185,  
      143}; 
   TGraphErrors *gre = new TGraphErrors(3,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(40);
   gre->SetMarkerSize(0.4);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","Graph",100,53.81,128.09);
   Graph_Graph1001->SetMinimum(54804.7);
   Graph_Graph1001->SetMaximum(156232.3);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetTitle("#Deltax [cm]");
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetTitle("#Deltaq [??]");
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   
   TF1 *PrevFitTMP1002 = new TF1("PrevFitTMP","expo",53.81,128.09, TF1::EAddToList::kNo);
   PrevFitTMP1002->SetFillColor(19);
   PrevFitTMP1002->SetFillStyle(0);
   PrevFitTMP1002->SetLineColor(2);
   PrevFitTMP1002->SetLineWidth(2);
   PrevFitTMP1002->SetChisquare(0.484471);
   PrevFitTMP1002->SetNDF(1);
   PrevFitTMP1002->GetXaxis()->SetLabelFont(42);
   PrevFitTMP1002->GetXaxis()->SetLabelSize(0.035);
   PrevFitTMP1002->GetXaxis()->SetTitleSize(0.035);
   PrevFitTMP1002->GetXaxis()->SetTitleFont(42);
   PrevFitTMP1002->GetYaxis()->SetLabelFont(42);
   PrevFitTMP1002->GetYaxis()->SetLabelSize(0.035);
   PrevFitTMP1002->GetYaxis()->SetTitleSize(0.035);
   PrevFitTMP1002->GetYaxis()->SetTitleOffset(0);
   PrevFitTMP1002->GetYaxis()->SetTitleFont(42);
   PrevFitTMP1002->SetParameter(0,12.95078);
   PrevFitTMP1002->SetParError(0,0.2039809);
   PrevFitTMP1002->SetParLimits(0,0,0);
   PrevFitTMP1002->SetParameter(1,-0.0164184);
   PrevFitTMP1002->SetParError(1,0.002173944);
   PrevFitTMP1002->SetParLimits(1,0,0);
   PrevFitTMP1002->SetParent(gre);
   gre->GetListOfFunctions()->Add(PrevFitTMP1002);
   
   TPaveStats *ptstats = new TPaveStats(0.62,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 0.4845 / 1");
   ptstats_LaTex = ptstats->AddText("Constant = 12.95 #pm 0.204 ");
   ptstats_LaTex = ptstats->AddText("Slope    = -0.01642 #pm 0.002174 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   gre->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.4398567,0.9338535,0.5601433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Graph");
   pt->Draw();
   draw_canvas->Modified();
   draw_canvas->cd();
   draw_canvas->SetSelected(draw_canvas);
}
