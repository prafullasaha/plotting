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

int DNN_performance( int year=2, bool DNN_opt = true){
//RunII
//
TFile *file_tth, *file_thq, *file_ttgg, *file_ttgjets, *file_DiPhotonJetsBox, *file_DiPhotonJetsBox2BJets, *file_gjets;
float MVA1_cut = 0.;
float MVA2_cut = 0.;
float lumi=0.;
if(year == 2){
cout<<"Running on Run2 samples"<<endl;
	file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
	file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_TTGG_0Jets_pythia8.root");
        file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_TTGJets_pythia8.root");
        file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
	file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

float MVA1_cut = 0.3;
float MVA2_cut = 0.08;
float lumi=137.1;

	}
//2016
else if(year == 2016){
cout<<"Running on 2016 samples"<<endl;

        file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_TTGG_0Jets_pythia8.root");
        file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_TTGJets_pythia8.root");
        file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
        file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2016/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

float MVA1_cut = 0.3;
float MVA2_cut = 0.08;
float lumi=35.9;

	}
//2017
else if(year==2017){
cout<<"Running on 2017 samples"<<endl;
        file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_TTGG_0Jets_pythia8.root");
        file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_TTGJets_pythia8.root");
        file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
        file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

float MVA1_cut = 0.3;
float MVA2_cut = 0.05;
float lumi=41.5;

}
//2018
else if(year==2018){
cout<<"Running on 2018 samples"<<endl;

        file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_TTGG_0Jets_pythia8.root");
        file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_TTGJets_pythia8.root");
        file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
        file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2018/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

float MVA1_cut = 0.3;
float MVA2_cut = 0.08;
float lumi=59.5;

}
else cout<<"No file exists-------------"<<endl;

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

        Float_t qweight, qdipho_mass, qMVA1, qMVA2;
        Float_t tweight, tdipho_mass, tMVA1, tMVA2;
	Float_t bweight, bdipho_mass, bMVA1, bMVA2;

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
s_sig->SetTitle("; #bf{DNN score}; #bf{Significance}");
tHq_eff->SetTitle("; #bf{DNN score}; #bf{Efficiency}");
ttH_eff->SetTitle("; #bf{DNN score}; #bf{Efficiency}");
bkg_eff->SetTitle("; #bf{DNN score}; #bf{Efficiency}");
mg->SetTitle("; #bf{DNN score}; #bf{Efficiency}");
//DNN optimization( tHq Vs ttH )---------------------------------------------------------------------
if(DNN_opt){

	for(double MVA1=1.0;MVA1>=0.;MVA1=MVA1-0.02){
	cout<<"Debug[2]"<<endl;
N++;
cout<<"N =  "<<N<<endl;
	float s=0;
	float b=0;
	float bkg=0;
	float tHq_yield=0;
	float ttH_yield=0;
	float bkg_yield=0;
	        for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
                tree_thq->GetEntry( ievent );
		if(qMVA2 > MVA2_cut) tHq_yield = tHq_yield + qweight;
			if(qMVA1 < MVA1 && qMVA2 > MVA2_cut/* && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
		         s= s+qweight;
			}
		}
                for(int ievent=0; ievent<nentries_tth; ievent++){ //Background event loop
                tree_tth->GetEntry( ievent );
		if(tMVA2 > MVA2_cut) ttH_yield = ttH_yield + tweight;
		        if(tMVA1 < MVA1 && tMVA2 > MVA2_cut/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	                b= b+tweight;
			}
		}
		for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkg->GetEntry( ievent );
                if(bMVA2 > MVA2_cut) bkg_yield = bkg_yield + bweight;
		         if(bMVA1 < MVA1 && bMVA2 > MVA2_cut/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	                bkg = bkg+bweight;
			}
		 }
double s_sig_ = Getsig(s,b);
double tHq_eff_ = s/tHq_yield;
double ttH_eff_ = b/ttH_yield;
double bkg_eff_ = bkg/bkg_yield;
cout<<"MVA1=  "<<MVA1<<"s_sig_   ="<<s_sig_<<"bkg  = "<<bkg<<endl;
s_sig->SetPoint(N-1, MVA1, s_sig_);
tHq_eff->SetPoint(N-1, MVA1, tHq_eff_*100);
ttH_eff->SetPoint(N-1, MVA1, ttH_eff_*100);
bkg_eff->SetPoint(N-1, MVA1, bkg_eff_*100);
}
}
//----------------------------------------------------------------------------------
//BDT optimization( tHq Vs NotHiggs background)-----------------------------------------------------
if(!DNN_opt)
{
        for(double MVA2=-0.3;MVA2 <=0.3;MVA2=MVA2+0.04){
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
                        if(/*qMVA1 < MVA1_cut &&*/ qMVA2 > MVA2/* && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
                        s= s+qweight;
                                 }
                }
                }
                for(int ievent=0; ievent<nentries_tth; ievent++){ //Background event loop
                tree_tth->GetEntry( ievent );
                if(tMVA2 > -999){
                ttH_yield = ttH_yield + tweight;
                if(/*tMVA1 < MVA1_cut &&*/ tMVA2 >= MVA2/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                        b= b+tweight;
                        }
                }
                }
                for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkg->GetEntry( ievent );
                if(bMVA2 > -999){
                bkg_yield = bkg_yield + bweight;
                if(/*bMVA1 < MVA1_cut &&*/ bMVA2 > MVA2 /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
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


        TLatex * tex = new TLatex(0.10, 0.97,TString("#bf{CMS}                                         ") +

                       Form("%.1f", lumi) + " fb^{-1} (13 TeV)");
        tex->SetNDC();
        tex->SetTextAlign(13);
        tex->SetTextFont(42);
        tex->SetTextSize(0.06);
        tex->SetLineWidth(2);



TLine *l = new TLine(MVA1_cut,0,MVA1_cut,100);
l->SetLineWidth(3);
l->SetLineColor(13);
l->SetLineStyle(7);

TLine *l_sig = new TLine(MVA1_cut,0.2,MVA1_cut,0.65);
l_sig->SetLineWidth(3);
l_sig->SetLineColor(13);
l_sig->SetLineStyle(7);

mg->Add(tHq_eff);
mg->Add(ttH_eff);
mg->Add(bkg_eff);

TCanvas *sig = new TCanvas("sig", "sig", 600, 600);
sig->cd();
s_sig->Draw("APL");
l_sig->Draw("SAME");
tex->Draw();
TCanvas *eff = new TCanvas("eff", "eff", 600, 600);
eff->cd();
mg->Draw("APL");
leg1->Draw();
l->Draw("SAME");
tex->Draw();
eff->SaveAs(Form("plots/DNN_eff_Run%i.root",year));
sig->SaveAs(Form("plots/DNN_sig_Run%i.root",year));

return 0;
}

int main(int argc, char** argv)
{
//TString methodList;
int year;
bool DNN_opt;
return DNN_performance( year );
}

