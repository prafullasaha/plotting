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
#include "TGraph.h"

double Getsig(float s, float b){
if (s==0  && b==0) return 0;
else if (s+b < 0) return 0;
else
        return (s/sqrt(s+b));
}

void BDT_performance_NonHiggs(){
	TFile *file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        TFile *file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
	TFile *file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_TTGG_0Jets_pythia8.root");
        TFile *file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_TTGJets_pythia8.root");
        TFile *file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        TFile *file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
	TFile *file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

	TTree* tree_tth = (TTree*)file_tth->Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag");
        TTree* tree_thq = (TTree*)file_thq->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
        TTree *tree_ttgg = (TTree*)file_ttgg->Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag");
        TTree *tree_ttgjets = (TTree*)file_ttgjets->Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox  = (TTree*)file_DiPhotonJetsBox->Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox2BJets  = (TTree*)file_DiPhotonJetsBox2BJets->Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag");
	TTree *tree_gjets  = (TTree*)file_gjets->Get("tagsDumper/trees/gjets_13TeV_THQLeptonicTag");

	TFile *output = new TFile("output.root","RECREATE");
        TList *list = new TList;
//        list->Add(tree_tth);
        list->Add(tree_ttgg);
        list->Add(tree_ttgjets);
        list->Add(tree_DiPhotonJetsBox);
        list->Add(tree_DiPhotonJetsBox2BJets);
	list->Add(tree_gjets);

	TTree *tree_bkg = TTree::MergeTrees(list);

        Float_t qweight=0, qdipho_mass, qMVA1, qMVA2;
        Float_t tweight=0, tdipho_mass, tMVA1, tMVA2;
	Float_t bweight=0, bdipho_mass, bMVA1, bMVA2;

        tree_tth->SetBranchAddress("MVAscore_tHqVsttH_DNN", &tMVA1);
        tree_tth->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &tMVA2);
        tree_tth->SetBranchAddress("weight", &tweight);
        tree_tth->SetBranchAddress("dipho_mass", &tdipho_mass);
        tree_tth->SetBranchStatus("*", 1);

        tree_thq->SetBranchAddress("MVAscore_tHqVsttH_DNN", &qMVA1);
        tree_thq->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &qMVA2);
        tree_thq->SetBranchAddress("weight", &qweight);
        tree_thq->SetBranchAddress("dipho_mass", &qdipho_mass);
        tree_thq->SetBranchStatus("*", 1);

	tree_bkg->SetBranchAddress("MVAscore_tHqVsttH_DNN", &bMVA1);
	tree_bkg->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &bMVA2);
	tree_bkg->SetBranchAddress("weight", &bweight);
        tree_bkg->SetBranchAddress("dipho_mass", &bdipho_mass);
        tree_bkg->SetBranchStatus("*", 1);

        Int_t nentries_thq=(Int_t)tree_thq->GetEntries();
        Int_t nentries_tth=(Int_t)tree_tth->GetEntries();
	Int_t nentries_bkg=(Int_t)tree_bkg->GetEntries();

TGraph *s_sig = new TGraph();
TGraph *tHq_eff = new TGraph();
TGraph *ttH_eff = new TGraph();
TGraph *bkg_eff = new TGraph();
TMultiGraph *mg = new TMultiGraph();

int N=0;
s_sig->SetTitle("; #bf{BDT score}; #bf{Significance}");
tHq_eff->SetTitle("; #bf{BDT score}; #bf{Efficiency}");
ttH_eff->SetTitle("; #bf{BDT score}; #bf{Efficiency}");
bkg_eff->SetTitle("; #bf{BDT score}; #bf{Efficiency}");
mg->SetTitle("; #bf{BDT score}; #bf{Efficiency}");
//float MVA1_cut=0.3;//real
float MVA1_cut=1.5;//to avoid the cut in if condition
float MVA2_cut=0.08;
float lumi = 59.7;
	for(double MVA2=-0.3;MVA2 <=0.3;MVA2=MVA2+0.01){
	cout<<"Debug[2]"<<endl;
N++;
cout<<"N =  "<<N<<endl;
	Float_t s=0;
	Float_t b=0;
	float bkg=0;
	float tHq_yield=0;
	Float_t ttH_yield=0;
	float bkg_yield=0;
	        for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
                tree_thq->GetEntry( ievent );
		if(qMVA2 > -999){
		tHq_yield = tHq_yield + qweight;
		      	if(qMVA1 < MVA1_cut && qMVA2 > MVA2/* && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
	              	s= s+qweight;
			         }
		}
        	}
                for(int ievent=0; ievent<nentries_tth; ievent++){ //Background event loop
                tree_tth->GetEntry( ievent );
		if(tMVA2 > -999){
		ttH_yield = ttH_yield + tweight;
         	if(tMVA1 < MVA1_cut && tMVA2 >= MVA2/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                	b= b+tweight;
			}
		}
		}
		for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkg->GetEntry( ievent );
		if(bMVA2 > -999){
                bkg_yield = bkg_yield + bweight;
			if(bMVA1 < MVA1_cut && bMVA2 > MVA2 /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	                 bkg = bkg+bweight;
			}
		}
		}
	double s_sig_ = Getsig(s,bkg);
	double tHq_eff_ = s/tHq_yield;
	double ttH_eff_ = b/ttH_yield;
	double bkg_eff_ = bkg/bkg_yield;
	cout<<"tHq_yield  "<<tHq_yield<<"   s= "<<s<<endl;
	cout<<"ttH_yield  "<<ttH_yield<<"   b= "<<b<<endl;
	cout<<"MVA2=  "<<MVA2<<"s_sig_   ="<<s_sig_<<"   tHq eff= "<<tHq_eff_<<"   ttH eff"<<ttH_eff_<<endl;
	s_sig->SetPoint(N-1, MVA2, s_sig_);
	tHq_eff->SetPoint(N-1, MVA2, tHq_eff_*100);
	ttH_eff->SetPoint(N-1, MVA2, ttH_eff_*100);
	bkg_eff->SetPoint(N-1, MVA2, bkg_eff_*100);
	}

gStyle->SetPadGridX(kTRUE);
gStyle->SetPadGridY(kTRUE);

s_sig->SetMarkerStyle(20);
s_sig->SetMarkerColor(2);
s_sig->SetLineColor(2);
s_sig->SetLineWidth(2);

tHq_eff->SetMarkerStyle(20);
tHq_eff->SetMarkerColor(4);
tHq_eff->SetLineColor(4);
tHq_eff->SetLineWidth(2);
ttH_eff->SetMarkerStyle(20);
ttH_eff->SetMarkerColor(2);
ttH_eff->SetLineColor(2);
ttH_eff->SetLineWidth(2);
bkg_eff->SetMarkerStyle(20);
bkg_eff->SetMarkerColor(3);
bkg_eff->SetLineColor(3);
bkg_eff->SetLineWidth(2);

TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9, "");
    leg1->SetFillColor(0);
    leg1->AddEntry(tHq_eff,"tHq","pl");
    leg1->AddEntry(ttH_eff,"ttH","pl");
    leg1->AddEntry(bkg_eff,"NonHiggs","pl");
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);

TLatex * tex = new TLatex(-0.3, 0,TString("#bf{CMS} Preliminary    ") +
                                  Form("%.1f", lumi) + " fb^{-1} (13 TeV)");

TLine *eff_l = new TLine(MVA2_cut,0,MVA2_cut,100);
eff_l->SetLineWidth(3);
eff_l->SetLineColor(13);
eff_l->SetLineStyle(7);

TLine *sig_l = new TLine(MVA2_cut,0,MVA2_cut,0.065);
sig_l->SetLineWidth(3);
sig_l->SetLineColor(13);
sig_l->SetLineStyle(7);

mg->Add(tHq_eff);
mg->Add(ttH_eff);
mg->Add(bkg_eff);

TCanvas *sig = new TCanvas("sig", "sig", 600, 600);
sig->cd();
s_sig->Draw("APL");
sig_l->Draw();
tex->Draw();

TCanvas *eff = new TCanvas("eff", "eff", 600, 600);
eff->cd();
mg->Draw("APL");
leg1->Draw();
eff_l->Draw();
tex->Draw();
eff->SaveAs("plots/BDT_eff_NonHiggs_18.root");
sig->SaveAs("plots/BDT_sig_NonHiggs_18.root");
}
