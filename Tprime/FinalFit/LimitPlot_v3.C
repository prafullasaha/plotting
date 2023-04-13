#include <iostream>
 
using namespace std;
void LimitPlot_v3(){
TCanvas* c41 = new TCanvas("c41","c41",200,10,600,400);
TMultiGraph *mg = new TMultiGraph();
double x[] = {600, 650, 700};
double y[] = {2.6094, 3.3438, 4.4531};
double exl[] = {0, 0, 0};
double exh[] = {0, 0, 0};
double eyl[] = {(2.6094-1.7812),(3.3438-2.2825),(4.4531-3.0221)};
double eyh[] = {(3.9095-2.6094),(5.0231-3.3438), (6.6719-4.4531)};
TGraphAsymmErrors* ge = new TGraphAsymmErrors(3, x, y,exl,exh,eyl,eyh);
ge->SetFillColor(kGreen);
// ge->Draw("a3");

double ex2l[] = {0, 0, 0};
double ex2h[] = {0, 0, 0};
double ey2l[] = {(2.6094-1.2843), (3.3438-1.6458), (4.4531-2.1918)};
double ey2h[] = {(5.6548-2.6094), (7.2538-3.3438), (9.6504-4.4531)};

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
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v3.pdf");
c41->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/LimitTprime_v3.png");
}
/*
Expected  2.5%: r < 0.6776
Expected 16.0%: r < 0.9791
Expected 50.0%: r < 1.5352
Expected 84.0%: r < 2.5142
Expected 97.5%: r < 4.0119


*/
