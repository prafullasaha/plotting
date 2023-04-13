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


void roc_plot(){

gStyle->SetOptStat(0);

TFile * file_output;
TString file_path="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/";

TFile * file_16;
file_16 = new TFile(file_path + "dataset_Run2_Tprime600_700VsHiggs_UL/TMVA_Run2_Tprime600_700VsHiggs.root", "READ");
TFile * file_17;
file_17 = new TFile(file_path + "dataset_Run2_Tprime800_1000VsHiggs_UL/TMVA_Run2_Tprime800_1000VsHiggs.root", "READ");
TFile * file_18;
file_18 = new TFile(file_path + "dataset_Run2_Tprime1100_1200VsHiggs_UL/TMVA_Run2_Tprime1100_1200VsHiggs.root", "READ");

file_output =new TFile("roc_xcheck.root", "RECREATE");

TH1F * h_roc_16 = (TH1F*) file_16->Get("dataset_Run2_Tprime600_700VsHiggs_UL/Method_BDTG/BDTG/MVA_BDTG_rejBvsS");
TH1F * h_roc_17 = (TH1F*) file_17->Get("dataset_Run2_Tprime800_1000VsHiggs_UL/Method_BDTG/BDTG/MVA_BDTG_rejBvsS");
TH1F * h_roc_18 = (TH1F*) file_18->Get("dataset_Run2_Tprime1100_1200VsHiggs_UL/Method_BDTG/BDTG/MVA_BDTG_rejBvsS");

h_roc_16->SetTitle("Background rejection vs Signal selection");
h_roc_17->GetYaxis()->SetTitle("Background rejection");
h_roc_18->GetXaxis()->SetTitle("Signal selection");

h_roc_16->SetLineWidth(2);
h_roc_16->SetLineColor(kRed);

h_roc_17->SetLineWidth(2);
h_roc_17->SetLineColor(kGreen);

h_roc_18->SetLineWidth(2);
h_roc_18->SetLineColor(kBlue);

TLegend *leg = new TLegend(0.2, 0.2, 0.6, 0.4, "");

leg->AddEntry(h_roc_16, "[600, 700]: AUC=0.923", "l");
leg->AddEntry(h_roc_17, "[800, 1000]: AUC=0.969", "l");
leg->AddEntry(h_roc_18, "[1100, 1200]: AUC=0.989", "l");

cout<<h_roc_16->GetEntries()<<endl;
TCanvas *c1= new TCanvas("c1", "c1",600,600);
c1->SetGridx();
c1->SetGridy();
c1->cd();
h_roc_16->Draw("l");
h_roc_17->Draw("l SAME");
h_roc_18->Draw("l SAME");
leg->Draw("SAME");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/roc_TprimeVsSMH.png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/roc_TprimeVsSMH.pdf");
}

