#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TSelector.h>
#include <TTreePlayer.h>

#include "TLorentzVector.h"
#include "TVector.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TGraph.h"

using namespace std;

void xs_plot(){

gStyle->SetOptStat(0);
gROOT->SetBatch(1);

Double_t xsbr[10] = {0.1764, 0.1489, 0.1213, 0.1050, 0.0886, 0.0459, 0.0251, 0.0145, 0.00867, 0.00536};
Double_t Had_eff[10] = {0.08, 0.09, 0.11, 0.11, 0.11, 0.12, 0.18, 0.20, 0.23, 0.27};
Double_t Lep_eff[10] = {0.088, 0.094, 0.10, 0.101, 0.106, 0.146, 0.161, 0.167, 0.174, 0.177};
Double_t T_mass[10] = {600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200};
//TGraph *xs_graph;

TLegend *leg1 = new TLegend(0.70, 0.75, 0.9, 0.87, "");
//leg1->SetNColumns(4);

TGraph* xs_graph 		= new TGraph(10, T_mass, xsbr);
TGraph* Had_eff_graph 	= new TGraph(10, T_mass, Had_eff);
TGraph* Lep_eff_graph 	= new TGraph(10, T_mass, Lep_eff);

xs_graph->SetLineWidth(2);
Had_eff_graph->SetLineWidth(2);
Lep_eff_graph->SetLineWidth(2);

//xs_graph->Fill(10, T_mass, xsbr);
TSpline3 *s = new TSpline3("grs", xs_graph);
s->SetLineColor(kRed);
s->SetLineWidth(2);

TSpline3 *Had_eff_s = new TSpline3("grs", Had_eff_graph);
Had_eff_s->SetLineColor(kRed);
Had_eff_s->SetLineWidth(2);

TSpline3 *Lep_eff_s = new TSpline3("grs", Lep_eff_graph);
Lep_eff_s->SetLineColor(kRed);
Lep_eff_s->SetLineWidth(2);

cout<<"Crossection at 750TeV    ="<<s->Eval(750)<<endl;
cout<<"Crossection at 850TeV	="<<s->Eval(850)<<endl;
cout<<"Crossection at 950TeV    ="<<s->Eval(950)<<endl;
cout<<"Crossection at 1050TeV   ="<<s->Eval(1050)<<endl;
cout<<"Crossection at 1150TeV   ="<<s->Eval(1150)<<endl;

leg1->AddEntry(xs_graph, "#sigma X Br.", "l");
leg1->AddEntry(s, "spline", "l");

//mg->GetXaxis()->SetTitle("Higgs-MVA");
//mg->GetYaxis()->SetTitle("Total Yield");
TCanvas *c0 = new TCanvas("c0", "c0", 600, 600);
c0->cd();
c0->SetGridy();
c0->SetGridx();
Had_eff_graph->SetMinimum(0);
Had_eff_graph->SetMaximum(0.3);
Had_eff_graph->Draw("APL");
Had_eff_graph->SetTitle("T' mass Vs Had. eff.");
Had_eff_graph->GetXaxis()->SetTitle("T' mass");
Had_eff_graph->GetYaxis()->SetTitle("Had. eff. ");
Had_eff_s->Draw("same");
//leg1->Draw("SAME");

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
c1->cd();
c1->SetGridy();
c1->SetGridx();
Lep_eff_graph->SetMinimum(0);
Lep_eff_graph->SetMaximum(0.3);
Lep_eff_graph->Draw("APL");
Lep_eff_graph->SetTitle("T' mass Vs Lep. eff.");
Lep_eff_graph->GetXaxis()->SetTitle("T' mass");
Lep_eff_graph->GetYaxis()->SetTitle("Lep. eff. ");
Lep_eff_s->Draw("same");

TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
c2->cd();
c2->SetGridy();
c2->SetGridx();
//c2->SetLogy();
xs_graph->Draw("APL");
xs_graph->SetTitle("T' mass Vs Xs x Br.");
xs_graph->GetXaxis()->SetTitle("T' mass");
xs_graph->GetYaxis()->SetTitle("#sigma X Br.");
s->Draw("same");
leg1->Draw("SAME");

c0->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Had_eff_spline.pdf");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Lep_eff_spline.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/xs_spline.pdf");

c0->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Had_eff_spline.png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Lep_eff_spline.png");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/xs_spline.png");
//c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/YieldHiggsBkg_frac_TmassGT375_HiggsBkgTng.png");
} 


