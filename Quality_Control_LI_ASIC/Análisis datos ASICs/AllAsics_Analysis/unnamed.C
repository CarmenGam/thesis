{
//=========Macro generated from canvas: c1/c1
//=========  (Mon May 23 16:22:56 2016) by ROOT version5.34/32
   TCanvas *c1 = new TCanvas("c1", "c1",12,51,700,500);
   c1->Range(-0.8250001,0.8125,7.425,0.8675);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH2F *htemp__1 = new TH2F("htemp__1","mean:channel {disc==0 && sum==1}",40,0,6.6,40,0.818,0.862);
   htemp__1->SetDirectory(0);
   htemp__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   htemp__1->SetLineColor(ci);
   htemp__1->SetMarkerColor(2);
   htemp__1->SetMarkerStyle(21);
   htemp__1->GetXaxis()->SetTitle("channel");
   htemp__1->GetXaxis()->SetRange(1,40);
   htemp__1->GetXaxis()->SetLabelFont(42);
   htemp__1->GetXaxis()->SetLabelSize(0.035);
   htemp__1->GetXaxis()->SetTitleSize(0.035);
   htemp__1->GetXaxis()->SetTitleFont(42);
   htemp__1->GetYaxis()->SetTitle("mean");
   htemp__1->GetYaxis()->SetRange(1,40);
   htemp__1->GetYaxis()->SetLabelFont(42);
   htemp__1->GetYaxis()->SetLabelSize(0.035);
   htemp__1->GetYaxis()->SetTitleSize(0.035);
   htemp__1->GetYaxis()->SetTitleFont(42);
   htemp__1->GetZaxis()->SetLabelFont(42);
   htemp__1->GetZaxis()->SetLabelSize(0.035);
   htemp__1->GetZaxis()->SetTitleSize(0.035);
   htemp__1->GetZaxis()->SetTitleFont(42);
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.1934384,0.9367722,0.8065616,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("mean:channel {disc==0 && sum==1}");
   pt->Draw();
   
   TGraph *graph = new TGraph(7);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#000099");
   graph->SetLineColor(ci);
   graph->SetMarkerColor(2);
   graph->SetMarkerStyle(21);
   graph->SetPoint(0,0,0.8502290249);
   graph->SetPoint(1,1,0.8201029897);
   graph->SetPoint(2,2,0.8586450219);
   graph->SetPoint(3,3,0.8535410166);
   graph->SetPoint(4,4,0.8525500298);
   graph->SetPoint(5,5,0.8477839828);
   graph->SetPoint(6,6,0.8531079888);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0,6.6);
   Graph_Graph1->SetMinimum(0.8162488);
   Graph_Graph1->SetMaximum(0.8624992);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   graph->Draw("p");
   
   TLegend *leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   graph = new TGraph(7);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#000099");
   graph->SetLineColor(ci);
   graph->SetMarkerColor(4);
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,0,0.8454419971);
   graph->SetPoint(1,1,0.8182439804);
   graph->SetPoint(2,2,0.8562030196);
   graph->SetPoint(3,3,0.8465539813);
   graph->SetPoint(4,4,0.8498479724);
   graph->SetPoint(5,5,0.8479409814);
   graph->SetPoint(6,6,0.8518429995);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,0,6.6);
   Graph_Graph2->SetMinimum(0.8144481);
   Graph_Graph2->SetMaximum(0.8599989);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   graph->Draw("p ");
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   graph = new TGraph(7);
   graph->SetName("Graph2");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#000099");
   graph->SetLineColor(ci);
   graph->SetMarkerColor(4);
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,0,0.8454419971);
   graph->SetPoint(1,1,0.8182439804);
   graph->SetPoint(2,2,0.8562030196);
   graph->SetPoint(3,3,0.8465539813);
   graph->SetPoint(4,4,0.8498479724);
   graph->SetPoint(5,5,0.8479409814);
   graph->SetPoint(6,6,0.8518429995);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,0,6.6);
   Graph_Graph3->SetMinimum(0.8144481);
   Graph_Graph3->SetMaximum(0.8599989);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3->SetLineColor(ci);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph3);
   
   graph->Draw("p ");
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   graph = new TGraph(7);
   graph->SetName("Graph3");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#000099");
   graph->SetLineColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,0,0.8523240089);
   graph->SetPoint(1,1,0.8254730105);
   graph->SetPoint(2,2,0.8611230254);
   graph->SetPoint(3,3,0.8551009893);
   graph->SetPoint(4,4,0.8564400077);
   graph->SetPoint(5,5,0.8521490097);
   graph->SetPoint(6,6,0.8577610254);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,0,6.6);
   Graph_Graph4->SetMinimum(0.821908);
   Graph_Graph4->SetMaximum(0.864688);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph4->SetLineColor(ci);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph4);
   
   graph->Draw("p ");
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.7048711,0.100211,0.8997135,0.2921941,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","Adder A","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
