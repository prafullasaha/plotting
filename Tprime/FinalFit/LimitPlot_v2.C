#include <iostream>
 
using namespace std;
void LimitPlot_v2(){
TCanvas* c41 = new TCanvas("c41","c41",200,10,600,400);
TMultiGraph *mg = new TMultiGraph();
double x[] = {600, 700, 800};
double y[] = {1.5352, 1.1602, 1.3086};
double exl[] = {0, 0, 0};
double exh[] = {0, 0, 0};
double eyl[] = {(1.5352-0.9791),(1.1602-0.7399),(1.3086-0.8346)};
double eyh[] = {(2.5142-1.5352),(1.9001-1.1602), (2.1432-1.3086)};
TGraphAsymmErrors* ge = new TGraphAsymmErrors(3, x, y,exl,exh,eyl,eyh);
ge->SetFillColor(kGreen);
// ge->Draw("a3");

double ex2l[] = {0, 0, 0};
double ex2h[] = {0, 0, 0};
double ey2l[] = {(1.5352-0.6776), (1.1602-0.5121), (1.3086-0.5776)};
double ey2h[] = {(4.0119-1.5352), (3.0446-1.1602), (3.4198-1.3086)};

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
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v2.pdf");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v2.png");
}
/*
Expected  2.5%: r < 0.6776
Expected 16.0%: r < 0.9791
Expected 50.0%: r < 1.5352
Expected 84.0%: r < 2.5142
Expected 97.5%: r < 4.0119


*/
