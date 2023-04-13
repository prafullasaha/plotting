#include <iostream>
 
using namespace std;
void LimitPlot_FinalfitLite(){
TCanvas* c41 = new TCanvas("c41","c41",200,10,600,400);
TMultiGraph *mg = new TMultiGraph();
double x[] = {600, 700, 800};
double y[] = {5.5312, 4.1875, 4.7188};
double exl[] = {0, 0, 0};
double exh[] = {0, 0, 0};
double eyl[] = {(5.5312-3.5796),(4.1875-2.7100),(4.7188-3.0335)};
double eyh[] = {(8.8384-5.5312),(6.6912-4.1875), (7.5401-4.7188)};
TGraphAsymmErrors* ge = new TGraphAsymmErrors(3, x, y,exl,exh,eyl,eyh);
ge->SetFillColor(kGreen);
// ge->Draw("a3");

double ex2l[] = {0, 0, 0};
double ex2h[] = {0, 0, 0};
double ey2l[] = {(5.5312-2.4847), (4.1875-1.8811), (4.7188-2.1198)};
double ey2h[] = {(13.6397-5.5312), (10.3261-4.1875), (11.6361-4.7188)};

TGraphAsymmErrors* ge2 = new TGraphAsymmErrors(3, x, y, ex2l,ex2h,ey2l,ey2h);
ge2->SetFillColor(kYellow);
ge2->GetXaxis()->SetTitle("T' mass");
ge2->GetYaxis()->SetTitle("95\% CL limit on #mu");
ge2->SetTitle("");
TGraph* g = new TGraph(3, x, y);
g->SetLineWidth(2);

c41->cd();
c41->SetGridx();
c41->SetGridy();
ge2->Draw("a3");
ge->Draw("Same3l");
g->Draw("SAME");
// ge->Draw("a3");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v2_FinalfitLite.pdf");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v2_FinalfitLite.png");
}
/*
Expected  2.5%: r < 0.6776
Expected 16.0%: r < 0.9791
Expected 50.0%: r < 1.5352
Expected 84.0%: r < 2.5142
Expected 97.5%: r < 4.0119


*/
