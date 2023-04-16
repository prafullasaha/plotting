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

void tHqCtCv_comp(){

//gROOT->SetBatch();
gStyle->SetOptStat(0);

const int num = 3;
string ctcv[num] = {"SM", "ctm1cv1", "ctm15cv15"};

TFile *file_SM = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_SM.root", "READ");
TFile *file_ctm1cv1 = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_TuneCP5_13TeV-madgraph-pythia8_ctm1cv1.root", "READ");
TFile *file_ctm15cv15 = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_TuneCP5_13TeV-madgraph-pythia8_ctm15cv15.root", "READ");

//for(int i=0; i<num; i++)
//{
//Form("TFile *file_%s",ctcv[i].c_str()) = new TFile(Form("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_%s.root",ctcv[i].c_str()), "READ");

TTree* tree_SM = (TTree*)file_SM->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
TTree* tree_ctm1cv1 = (TTree*)file_ctm1cv1->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
TTree* tree_ctm15cv15 = (TTree*)file_ctm15cv15->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
//}
TH1F* h_SM =new TH1F("h_SM","h_SM",100,100,140);
TH1F* h_ctm1cv1 =new TH1F("h_ctm1cv1","ctm1cv1",100,100,140);
TH1F* h_ctm15cv15 =new TH1F("h_ctm15cv15","h_ctm15cv15",100,100,140);

TH1F* h_SM_w =new TH1F("h_SM_w","h_SM",100,-0.00001,1);
TH1F* h_ctm1cv1_w =new TH1F("h_ctm1cv1_w","ctm1cv1",100,-0.00001,1);
TH1F* h_ctm15cv15_w =new TH1F("h_ctm15cv15_w","h_ctm15cv15",100,-0.00001,1);

tree_SM->Draw("dipho_mass >>  h_SM","(weight<0.004)*weight*11.84","hist");
tree_ctm1cv1->Draw("dipho_mass >>  h_ctm1cv1","(weight<0.004)*weight*11.84","hist");
tree_ctm15cv15->Draw("dipho_mass >>  h_ctm15cv15","(weight<0.004)*weight*11.84","hist");

tree_SM->Draw("weight >>  h_SM_w","weight>0","hist");
tree_ctm1cv1->Draw("weight >>  h_ctm1cv1_w","weight>0","hist");
tree_ctm15cv15->Draw("weight >>  h_ctm15cv15_w","weight>0","hist");

//TFile *file_ctm1cv1 = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_ctm1cv1.root", "READ");
//TFile *file_ctm15cv15 = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/flashggOutput_ntuple/Output_tHqCtCv/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_ctm15cv15.root", "READ");

h_SM->SetLineColor(kBlue);
h_ctm1cv1->SetLineColor(kRed);
h_ctm15cv15->SetLineColor(kBlack);

h_SM->SetLineWidth(2);
h_ctm1cv1->SetLineWidth(2);
h_ctm15cv15->SetLineWidth(2);

h_SM_w->SetLineColor(4);
h_ctm1cv1_w->SetLineColor(5);
h_ctm15cv15_w->SetLineColor(6);

h_ctm15cv15->SetTitle("DiPhoton mass");
h_ctm15cv15->GetYaxis()->SetTitle("Events");
h_ctm15cv15->GetXaxis()->SetTitle("Diphoton mass");


TLegend *leg = new TLegend(0.2, 0.2, 0.4, 0.4, "");
leg->AddEntry(h_SM, "ct=1, cv=-1", "l");
leg->AddEntry(h_ctm1cv1, "ct=-1, cv=1", "l");
leg->AddEntry(h_ctm15cv15, "ct=-1.5, cv=1.5", "l");

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
c1->cd();
//c1->SetLogy();
h_ctm15cv15->Draw("hist");
h_ctm1cv1->Draw("hist SAME");
h_SM->Draw("hist SAME");
leg->Draw("SAME");
/*
TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
c2->cd();
h_SM_w->Draw("hist");
h_ctm15cv15_w->Draw("hist SAME");
h_ctm1cv1_w->Draw("hist SAME");
//h_SM_w->Draw("hist SAME");
*/
c1->SaveAs("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/ctcv_weight.png");
c1->SaveAs("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/ctcv_weight.pdf");
}
