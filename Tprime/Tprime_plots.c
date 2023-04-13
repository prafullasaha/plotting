#include "TTree.h"
#include "TH1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLorentzVector.h"

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <TChain.h>
#include "TMath.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "THStack.h"

float Mtilde(float T_mass, float t_mass, float mh){
return (T_mass - t_mass + 175.5 - mh + 125); 
}

void Tprime_plots(TString Tprime_mass){
gStyle->SetOptStat(0);
gROOT->SetBatch(1);

TString file_name="/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/UL/v2/RunII/output_TprimeBToTH_Hgg_M-"+ Tprime_mass + "_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root";

TFile *file = new TFile(file_name, "READ");

TTree *tree = (TTree*)file->Get("tagsDumper/trees/TprimeM" + Tprime_mass + "_125_13TeV_THQLeptonicTag");

TH1F* h_mass =new TH1F("h_mass","h_mass",100,0,900);
TH1F* h_tmass =new TH1F("h_tmass","h_tmass",100,100,300);
TH1F* h_nu =new TH1F("h_nu","h_nu",100,300,1100);
TH1F* h_Xtt0 =new TH1F("h_Xtt0","h_Xtt0",100,0,30);
TH1F* h_SolvNuPt =new TH1F("h_SolvNuPt","h_SolvNuPt",100,0,300);
TH1F* h_solvedMET_pz =new TH1F("h_solvedMET_pz","h_solvedMET_pz",100,-300,300);
TH1F* h_genMET_pz = new TH1F("h_genMET_pz","h_genMET_pz",100,-300,300);
TH1F* h_promptGenMET_pz = new TH1F("h_promptGenMET_pz","h_promptGenMET_pz",100,-300,300);

TLegend *leg1 = new TLegend(0.6, 0.8, 0.9, 0.9, "");


//tree->Draw("top_mass >> h_tmass", "weight", "hist");
//tree->Draw("Xtt0 >> h_Xtt0", "weight", "hist");
tree->Draw("solvedMET_pz >> h_solvedMET_pz", "weight*(solvedMET_pz != 0)", "hist");
tree->Draw("genMET_pz >> h_genMET_pz", "weight*(genMET_pz != 0)", "hist");
tree->Draw("promptGenMET_pz >> h_promptGenMET_pz", "weight*(promptGenMET_pz != 0)", "hist");


Float_t qdipho_mass, qTprime_mass, qtop_mass, qweight, qMVA1, qMVA2;
tree->SetBranchAddress("dipho_mass", &qdipho_mass);
tree->SetBranchAddress("Tprime_mass", &qTprime_mass);
tree->SetBranchAddress("top_mass", &qtop_mass);
tree->SetBranchAddress("MVAscore_tHqVsttH_BDT", &qMVA1);//MVAresult_thq
tree->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &qMVA2);
tree->SetBranchAddress("weight", &qweight);
tree->SetBranchStatus("*", 1);
Int_t nentries=(Int_t)tree->GetEntries();

	for(int ievent=0; ievent < nentries; ievent++)
        {
        tree-> GetEntry( ievent );
	float Mtilde_ = Mtilde(qTprime_mass, qtop_mass, qdipho_mass);
//	cout<<"Mtilde      "<< Mtilde();<<endl;
	h_mass->Fill(Mtilde_, qweight);	
	}



h_mass->SetLineWidth(2);
h_tmass->SetLineWidth(2);
h_Xtt0->SetLineWidth(2);
h_genMET_pz->SetLineWidth(2);
h_solvedMET_pz->SetLineWidth(2);
h_promptGenMET_pz->SetLineWidth(2);

h_genMET_pz->SetLineColor(2);
h_solvedMET_pz->SetLineColor(4);
h_promptGenMET_pz->SetLineColor(6);

cout<<"h_genMET_pz Entries"<<h_genMET_pz->GetEntries()<<endl;
cout<<"h_solvedMET_pz Entries"<<h_solvedMET_pz->GetEntries()<<endl;
cout<<"h_promptGenMET_pz Entries"<<h_promptGenMET_pz->GetEntries()<<endl;

h_genMET_pz->Scale(1/h_genMET_pz->Integral());
h_solvedMET_pz->Scale(1/h_solvedMET_pz->Integral());
h_promptGenMET_pz->Scale(1/h_promptGenMET_pz->Integral());

leg1->AddEntry(h_genMET_pz, "Gen. matched(all)" ,"l");
leg1->AddEntry(h_solvedMET_pz, "Solved" ,"l");
leg1->AddEntry(h_promptGenMET_pz, "Gen. matched(prompt)" ,"l");

double std_mean = h_mass->GetMean();
double std_dev = h_mass->GetStdDev();


TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
c1->cd();
c1->SetTitle("");
c1->SetGrid();

TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(20);
    latex.DrawLatex( 0.6, 0.80, "std. hist " );
//    latex.DrawLatex( 0.6, 0.70, "fit. mode " );
//    latex.DrawLatex( 0.72, 0.80, Form("  : %.2f #pm %.2f", std_mean, std_dev) );
//    latex.DrawLatex( 0.72, 0.70, Form("  : %.2f #pm %.2f", mode, mode_sigma) );

//h_mass->Fit(double_gaus, "R");
//h_mass->Draw("hist");
//h_tmass->Draw("hist");
//h_Xtt0->Draw("hist");
h_solvedMET_pz->SetMaximum(4*h_solvedMET_pz->GetMaximum());
h_solvedMET_pz->SetTitle("");
h_solvedMET_pz->GetXaxis()->SetTitle("p_{z}^{#nu}");
h_solvedMET_pz->GetYaxis()->SetTitle("Normalized event");
h_solvedMET_pz->GetYaxis()->SetTitleOffset(1.4);
//h_solvedMET_pz->GetYaxis()->SetTitleSize(0.06);
//h_solvedMET_pz->GetYaxis()->SetLabelSize(0.04);

h_solvedMET_pz->Draw("hist");
h_genMET_pz->Draw("hist SAME");
h_promptGenMET_pz->Draw("hist SAME");
leg1->Draw("SAME");

//h_solvedMET_pz->Draw("hist SAME");
//c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Mtilde_Tprime"+ Tprime_mass +".png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/METpz_on_Tprime"+ Tprime_mass +".png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/METpz_on_Tprime"+ Tprime_mass +".pdf");
} 
