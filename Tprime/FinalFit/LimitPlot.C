#include <iostream>
 
using namespace std;
void LimitPlot(){
TCanvas* c41 = new TCanvas("c41","c41",200,10,600,400);
TMultiGraph *mg = new TMultiGraph();
double x[] = {600, 700, 800};
double y[] = {3.0781, 2.125, 2.0078};
double exl[] = {0, 0, 0};
double exh[] = {0, 0, 0};
double eyl[] = {1.063,0.7338,0.7018};
double eyh[] = {1.8405, 1.2706, 1.2005};
TGraphAsymmErrors* ge = new TGraphAsymmErrors(3, x, y,exl,exh,eyl,eyh);
ge->SetFillColor(kGreen);
// ge->Draw("a3");

double ex2l[] = {0, 0, 0};
double ex2h[] = {0, 0, 0};
double ey2l[] = {1.6563, 1.1455, 1.0823};
double ey2h[] = {4.5817, 3.163, 2.9889};

TGraphAsymmErrors* ge2 = new TGraphAsymmErrors(3, x, y, ex2l,ex2h,ey2l,ey2h);
ge2->SetFillColor(kYellow);
ge2->GetXaxis()->SetTitle("T' mass");
ge2->GetYaxis()->SetTitle("95\% CL limit on #sigma/#sigma_{SM}");
TGraph* g = new TGraph(3, x, y);
g->SetLineWidth(2);

c41->cd();
c41->SetGridx();
c41->SetGridy();
ge2->Draw("a3");
ge->Draw("Same3l");
g->Draw("SAME");
// ge->Draw("a3");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime.pdf");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime.png");
}
