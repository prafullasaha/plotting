//Run one optimisation once either DNN_opt=true or BDT_opt=true. Not both together.

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

int MVA_optimisation_ForMVA_v3( int year=2, bool DNN_opt = false, bool BDT_opt = false){
//RunII
//
TFile *file_tth, *file_thq, *file_ttgg, *file_ttgjets, *file_DiPhotonJetsBox, *file_DiPhotonJetsBox2BJets, *file_gjets, *file_TTJets, *file_TGJets, *file_ZG, *file_WG, *file_TTWJets, *file_DYJets, *file_VH;
float MVA1_cut = 0.;
float MVA2_cut = 0.;
double min_score=0;
double max_score=0;
if(DNN_opt){
//nbins=40;
min_score=0.;
max_score=1;
//bin_width = (max_score-min_score)/nbins;
};

if(BDT_opt){
//nbins=30;
min_score=-0.2;
max_score=0.15;
//bin_width = (max_score-min_score)/nbins;
};


float lumi=0.;
string method;
TString file_path;
if(year == 2){
cout<<"Running on Run2 samples"<<endl;
	file_tth = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
	file_ttgg = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_TTGG_0Jets_pythia8.root");
        file_ttgjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_TTGJets_pythia8.root");
        file_DiPhotonJetsBox = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root");
	file_gjets = TFile::Open("/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/RunII/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root");

	MVA1_cut = 0.3;
	MVA2_cut = 0.08;
	lumi=137.1;

	}
//2016
else if(year == 2016){
cout<<"Running on 2016 samples"<<endl;
	file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/For_v3/2016/";
        file_tth = new TFile(file_path + "output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
        file_ttgjets = TFile::Open(file_path + "output_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
        file_gjets = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root");
   	file_TTJets = TFile::Open(file_path + "output_TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root");
   	file_TGJets = TFile::Open(file_path + "output_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
   	file_ZG = TFile::Open(file_path + "ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
   	file_WG = TFile::Open(file_path + "output_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
   	file_TTWJets = TFile::Open(file_path + "output_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
   	file_DYJets = TFile::Open(file_path + "output_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
   	file_VH = TFile::Open(file_path + "output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");

	MVA1_cut = 0.3;
	MVA2_cut = 0.05;
	lumi=35.9;

	}
//2017
else if(year==2017){
cout<<"Running on 2017 samples"<<endl;
	file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/For_v3/2017/";
        file_tth = new TFile(file_path + "output_ttHJetToGG_M125_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root", "READ");
        file_thq = new TFile(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
        file_ttgjets = TFile::Open(file_path + "output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
        file_gjets = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root");
   	file_TTJets = TFile::Open(file_path + "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_TGJets = TFile::Open(file_path + "output_TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
   	file_ZG = TFile::Open(file_path + "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_WG = TFile::Open(file_path + "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_TTWJets = TFile::Open(file_path + "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
   	file_DYJets = TFile::Open(file_path + "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_VH = TFile::Open(file_path + "output_VHToGG_M125_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
	MVA1_cut = 0.3;
	MVA2_cut = 0.01;
	lumi=41.5;

}
//2018
else if(year==2018){
cout<<"Running on 2018 samples"<<endl;
	file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/For_v3/2018/";
        file_tth = new TFile(file_path + "output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
        file_thq = new TFile(file_path + "output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
        file_ttgjets = TFile::Open(file_path + "output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
        file_gjets = TFile::Open(file_path + "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root");
   	file_TTJets = TFile::Open(file_path + "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_TGJets = TFile::Open(file_path + "output_TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
   	file_ZG = TFile::Open(file_path + "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_WG = TFile::Open(file_path + "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_TTWJets = TFile::Open(file_path + "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
   	file_DYJets = TFile::Open(file_path + "DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
   	file_VH = TFile::Open(file_path + "output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
	MVA1_cut = 0.3;
	MVA2_cut = 0.0;
	lumi=59.5;

}
else cout<<"No file exists-------------"<<endl;

	TTree* tree_tth = (TTree*)file_tth->Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag");
        TTree* tree_thq = (TTree*)file_thq->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
        TTree *tree_ttgg = (TTree*)file_ttgg->Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag");
        TTree *tree_ttgjets = (TTree*)file_ttgjets->Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox  = (TTree*)file_DiPhotonJetsBox->Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox2BJets  = (TTree*)file_DiPhotonJetsBox2BJets->Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag");
	TTree *tree_gjets  = (TTree*)file_gjets->Get("tagsDumper/trees/gjets_13TeV_THQLeptonicTag");
   	TTree *tree_TGJets = (TTree*)file_TGJets->Get("tagsDumper/trees/tgjets_13TeV_THQLeptonicTag");
   	TTree *tree_TTJets = (TTree*)file_TTJets->Get("tagsDumper/trees/ttjets_13TeV_THQLeptonicTag");
   	TTree *tree_ZG = (TTree*)file_ZG->Get("tagsDumper/trees/ZG_13TeV_THQLeptonicTag");
   	TTree *tree_WG = (TTree*)file_WG->Get("tagsDumper/trees/WG_13TeV_THQLeptonicTag");
   	TTree *tree_TTWJets = (TTree*)file_TTWJets->Get("tagsDumper/trees/ttwjets_13TeV_THQLeptonicTag");
   	TTree *tree_DYJets = (TTree*)file_DYJets->Get("tagsDumper/trees/DYJets_13TeV_THQLeptonicTag");
   	TTree *tree_VH = (TTree*)file_VH->Get("tagsDumper/trees/vh_125_13TeV_THQLeptonicTag");

	TFile *output = new TFile("output.root","RECREATE");
        TList *list = new TList;
//        list->Add(tree_tth);
        list->Add(tree_ttgg);
        list->Add(tree_ttgjets);
        list->Add(tree_DiPhotonJetsBox);
        list->Add(tree_DiPhotonJetsBox2BJets);
	list->Add(tree_gjets);
        list->Add(tree_TGJets);
        list->Add(tree_TTJets);
        list->Add(tree_ZG);
        list->Add(tree_WG);
        list->Add(tree_TTWJets);
        list->Add(tree_DYJets);

	TTree *tree_bkg = TTree::MergeTrees(list);

        Float_t qweight, qdipho_mass, qMVA1, qMVA2;
        Float_t tweight, tdipho_mass, tMVA1, tMVA2;
	Float_t bweight, bdipho_mass, bMVA1, bMVA2;
        Float_t vweight, vdipho_mass, vMVA1, vMVA2;

        tree_tth->SetBranchAddress("MVAscore_tHqVsttH_DNN", &tMVA1);
        tree_tth->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &tMVA2);
        tree_tth->SetBranchAddress("weight", &tweight);
        tree_tth->SetBranchAddress("dipho_mass", &tdipho_mass);
        tree_tth->SetBranchStatus("*", 1);

        tree_VH->SetBranchAddress("MVAscore_tHqVsttH_DNN", &vMVA1);
        tree_VH->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &vMVA2);
        tree_VH->SetBranchAddress("weight", &vweight);
        tree_VH->SetBranchAddress("dipho_mass", &vdipho_mass);
        tree_VH->SetBranchStatus("*", 1);

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
        Int_t nentries_VH=(Int_t)tree_VH->GetEntries();
        Int_t nentries_tth=(Int_t)tree_tth->GetEntries();
	Int_t nentries_bkg=(Int_t)tree_bkg->GetEntries();

TGraph *s_sig_wrtTTH = new TGraph();
TGraph *s_sig_wrtBkg = new TGraph();
TGraph *tHq_eff = new TGraph();
TGraph *ttH_eff = new TGraph();
TGraph *bkg_eff = new TGraph();
TMultiGraph *mg = new TMultiGraph();

int N=0;

//DNN optimization( tHq Vs ttH )---------------------------------------------------------------------
if(DNN_opt){
cout<<"Running DNN optimisation----------------------------------------"<<endl;
method = "DNN";
	for(double MVA1=1.0;MVA1>=0.;MVA1=MVA1-0.01){
N++;
//cout<<"N =  "<<N<<endl;
	float s=0;
	float b=0;
	float bkg=0;
	float VH=0;
	float tHq_yield=0;
	float ttH_yield=0;
	float bkg_yield=0;
	float VH_yield=0;
//---------------------------------------------------------------------------------------------------
	        for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
                tree_thq->GetEntry( ievent );
		if(qweight<0.001){
		if(qMVA2 > MVA2_cut) tHq_yield = tHq_yield + (qweight);
			if(qMVA1 < MVA1 && qMVA2 > MVA2_cut /*&& (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
		         s= s+(qweight);
			}
		}
		}
//---------------------------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_tth; ievent++){ //Background event loop
                tree_tth->GetEntry( ievent );
		if(tweight < 3){
		if(tMVA2 > MVA2_cut) ttH_yield = ttH_yield + tweight;
		        if(tMVA1 < MVA1 && tMVA2 > MVA2_cut /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	                b= b+tweight;
			}
		}
		}
//---------------------------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_VH; ievent++){ //Background event loop
                tree_VH->GetEntry( ievent ); 
                if(vMVA2 > MVA2_cut) VH_yield = VH_yield + vweight;
                        if(vMVA1 < MVA1 && vMVA2 > MVA2_cut /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                        VH= VH+vweight;
                        }
                }
//--------------------------------------------------------------------------------------------------
		for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkg->GetEntry( ievent );
//		if(bweight>0){
                if(bMVA2 > MVA2_cut) bkg_yield = bkg_yield + bweight;
		         if(bMVA1 < MVA1 && bMVA2 > MVA2_cut /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	                bkg = bkg+bweight;
			}
//		}
		}
//--------------------------------------------------------------------------------------------------
double s_sig_wrtTTH_ = Getsig(s,b);
double s_sig_wrtBkg_ = Getsig(s,bkg);
double tHq_eff_ = s/tHq_yield;
double ttH_eff_ = b/ttH_yield;
double bkg_eff_ = bkg/bkg_yield;

//cout<<"tHq_yield  "<<tHq_yield<<"   s= "<<s<<endl;
//cout<<"ttH_yield  "<<ttH_yield<<"   b= "<<b<<endl;

cout<<"DNN score=  "<<MVA1<<"   tHq_yield=  "<<s<<"   ttH_yield=  "<<b<<"   VH_yield=  "<<VH<<"   bkg_yield=  "<<bkg<<endl;
//cout<<"MVA1=  "<<MVA1<<"s_sig_wrtBkg   ="<<s_sig_wrtBkg_<<"bkg  = "<<bkg<<endl;
s_sig_wrtTTH->SetPoint(N-1, MVA1, s_sig_wrtTTH_);
s_sig_wrtBkg->SetPoint(N-1, MVA1, s_sig_wrtBkg_);
tHq_eff->SetPoint(N-1, MVA1, tHq_eff_*100);
ttH_eff->SetPoint(N-1, MVA1, ttH_eff_*100);
bkg_eff->SetPoint(N-1, MVA1, bkg_eff_*100);
}
}
//----------------------------------------------------------------------------------
//BDT optimization( tHq Vs NotHiggs background)-----------------------------------------------------
if(BDT_opt)
{
cout<<"Running BDT optimisation----------------------------------------"<<endl;
method = "BDT";
        for(double MVA2=min_score;MVA2 <=max_score;MVA2=MVA2+0.01){
N++;
        Float_t s=0;
        Float_t b=0;
	float VH =0;
        float bkg=0;
        float tHq_yield=0;
        Float_t ttH_yield=0;
        Float_t VH_yield=0;
        float bkg_yield=0;
//tHq loop----------------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
                tree_thq->GetEntry( ievent );
                if(qMVA2 > -999 && qweight < 0.004 ){
                /*if( qMVA1 < MVA1_cut )*/ tHq_yield = tHq_yield + (qweight);
                        if(/*qMVA1 < MVA1_cut &&*/ qMVA2 > MVA2/* && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
                        s= s+(qweight);
                                 }
                }
                }
//ttH loop----------------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_tth; ievent++){ //Background event loop
                tree_tth->GetEntry( ievent );
                if(tMVA2 > -999 && tweight < 3 ){
                /*if( tMVA1 < MVA1_cut )*/ ttH_yield = ttH_yield + tweight;
                if(/*tMVA1 < MVA1_cut &&*/ tMVA2 >= MVA2/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                        b= b+tweight;
                        }
                }
                }
//VH loop--------------------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_VH; ievent++){ //Background event loop
                tree_VH->GetEntry( ievent );
                if(vMVA2 > -999 ){
                /*if( tMVA1 < MVA1_cut )*/ VH_yield = VH_yield + vweight;
                if(/*tMVA1 < MVA1_cut &&*/ vMVA2 >= MVA2/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                        VH = VH + vweight;
                        }
                }
                }

//Background loop----------------------------------------------------------------------------------
                for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkg->GetEntry( ievent );
                if(bMVA2 > -999){
                /*if( bMVA1 < MVA1_cut )*/ bkg_yield = bkg_yield + bweight;
                if(/*bMVA1 < MVA1_cut &&*/ bMVA2 > MVA2 /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                         bkg = bkg+bweight;
                        }
                }
                }
//--------------------------------------------------------------------------------------------------
        double s_sig_wrtBkg_ = Getsig(s,bkg);
	double s_sig_wrtTTH_ = Getsig(s,b);
        double tHq_eff_ = s/tHq_yield;
        double ttH_eff_ = b/ttH_yield;
        double bkg_eff_ = bkg/bkg_yield;

cout<<"BDT score=  "<<MVA2<<"   tHq_yield=  "<<s<<"   ttH_yield=  "<<b<<"   VH_yield=  "<<VH<<"   bkg_yield=  "<<bkg<<endl;

        s_sig_wrtBkg->SetPoint(N-1, MVA2, s_sig_wrtBkg_);
	s_sig_wrtTTH->SetPoint(N-1, MVA2, s_sig_wrtTTH_);
        tHq_eff->SetPoint(N-1, MVA2, tHq_eff_*100);
        ttH_eff->SetPoint(N-1, MVA2, ttH_eff_*100);
        bkg_eff->SetPoint(N-1, MVA2, bkg_eff_*100);
        }
}

s_sig_wrtTTH->SetTitle(Form("; %s score; Significance", method.c_str()));
s_sig_wrtBkg->SetTitle(Form("; #bf{%s score}; Significance", method.c_str()));
tHq_eff->SetTitle(Form("; %s score; Efficiency", method.c_str()));
ttH_eff->SetTitle(Form("; %s score; Efficiency", method.c_str()));
bkg_eff->SetTitle(Form("; %s score; Efficiency", method.c_str()));
mg->SetTitle(Form("; %s score; Efficiency", method.c_str()));



gStyle->SetPadGridX(kTRUE);
gStyle->SetPadGridY(kTRUE);

s_sig_wrtTTH->SetMarkerStyle(20);
s_sig_wrtTTH->SetMarkerColor(2);
s_sig_wrtTTH->SetLineColor(2);
s_sig_wrtTTH->SetLineWidth(2);

s_sig_wrtBkg->SetMarkerStyle(20);
s_sig_wrtBkg->SetMarkerColor(2);
s_sig_wrtBkg->SetLineColor(2);
s_sig_wrtBkg->SetLineWidth(2);

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

        TLatex * tex1 = new TLatex(0.12, 0.99,TString("#bf{CMS}"));
        tex1->SetNDC();
        tex1->SetTextAlign(13);
        tex1->SetTextFont(42);
        tex1->SetTextSize(0.07);
        tex1->SetLineWidth(2);

        TLatex * tex2 = new TLatex(0.52, 0.99,TString(Form("%.1f fb^{-1} (13 TeV)",lumi)));
        tex2->SetNDC();
        tex2->SetTextAlign(13);
        tex2->SetTextFont(42);
        tex2->SetTextSize(0.06);
        tex2->SetLineWidth(2);


TLine *l = new TLine(MVA1_cut,0,MVA1_cut,100);
l->SetLineWidth(3);
l->SetLineColor(13);
l->SetLineStyle(7);

TLine *l_sig = new TLine(MVA1_cut,0.2,MVA1_cut,0.65);
l_sig->SetLineWidth(3);
l_sig->SetLineColor(13);
l_sig->SetLineStyle(7);

TBox* box;
TBox* box1;
TBox* box2;


if(DNN_opt){
        box =new TBox(MVA1_cut, 0, max_score, 100);
	box1 =new TBox(MVA1_cut, 0, max_score, 0.014);
	box2 =new TBox(MVA1_cut, 0, max_score, 0.008);
}
else { 	
	box =new TBox(min_score, 0, MVA2_cut, 100);
	box1 =new TBox(min_score, 0, MVA2_cut, 0.014);
	box2 =new TBox(min_score, 0, MVA2_cut, 0.008);
}
        box->SetFillColorAlpha(kBlack, 0.15);
	box1->SetFillColorAlpha(kBlack, 0.15);
	box2->SetFillColorAlpha(kBlack, 0.15);

//mg->GetXaxis()->SetRangeUser(min_score, max_score);
s_sig_wrtTTH->GetYaxis()->SetTitleOffset(1.5);
s_sig_wrtBkg->GetYaxis()->SetTitleOffset(1.5);


mg->Add(tHq_eff);
mg->Add(ttH_eff);
mg->Add(bkg_eff);

TCanvas *sig_wrtTTH = new TCanvas("sig_wrtTTH", "sig_wrtTTH", 600, 600);
sig_wrtTTH->cd();
TPad *pad1 = new TPad("pad1","pad1",0,0,1.0,1.0);
pad1->SetTopMargin(0.075);
pad1->SetBottomMargin(0.075);
pad1->SetLeftMargin(0.120);
pad1->SetRightMargin(0.075);
pad1->SetTickx();
pad1->SetTicky();
pad1->Draw();
pad1->cd();

s_sig_wrtTTH->Draw("APL");
box1->Draw();
//l_sig->Draw("SAME");
tex1->Draw();
tex2->Draw();

TCanvas *sig_wrtBkg = new TCanvas("sig_wrtBkg", "sig_wrtBkg", 600, 600);
sig_wrtBkg->cd();
TPad *pad1_ = new TPad("pad1","pad1",0.,0.,1.0,1.0);
pad1_->SetTopMargin(0.075);
pad1_->SetBottomMargin(0.075);
pad1_->SetLeftMargin(0.120);
pad1_->SetRightMargin(0.070);
pad1_->SetTickx();
pad1_->SetTicky();
pad1_->Draw();
pad1_->cd();
s_sig_wrtBkg->Draw("APL");
tex1->Draw();
tex2->Draw();
box2->Draw();

TCanvas *eff = new TCanvas("eff", "eff", 600, 600);
eff->cd();
TPad *pad1__ = new TPad("pad1__","pad1__",0.,0.,1.0,1.0);
pad1__->SetTopMargin(0.075);
pad1__->SetBottomMargin(0.075);
pad1__->SetLeftMargin(0.120);
pad1__->SetRightMargin(0.070);
pad1__->SetTickx();
pad1__->SetTicky();
pad1__->Draw();
pad1__->cd();

mg->Draw("APL");
mg->GetXaxis()->SetRangeUser(min_score, max_score);
leg1->Draw();
box->Draw();
//l->Draw("SAME");
tex1->Draw();
tex2->Draw();

eff->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_eff_Run%i.root",method.c_str(), year));
sig_wrtTTH->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtTTH_Run%i.root",method.c_str(), year));
sig_wrtBkg->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtBkg_Run%i.root",method.c_str(), year));

eff->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_eff_Run%i.pdf",method.c_str(), year));
sig_wrtTTH->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtTTH_Run%i.pdf",method.c_str(), year));
sig_wrtBkg->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtBkg_Run%i.pdf",method.c_str(), year));

eff->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_eff_Run%i.png",method.c_str(), year));
sig_wrtTTH->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtTTH_Run%i.png",method.c_str(), year));
sig_wrtBkg->SaveAs(Form("/eos/user/p/prsaha/www/tmp/MVA_opt_v3/%s_sig_wrtBkg_Run%i.png",method.c_str(), year));

return 0;
}

int main(int argc, char** argv)
{
//TString methodList;
int year;
bool DNN_opt;
bool BDT_opt;
return MVA_optimisation_ForMVA_v3( year, DNN_opt, BDT_opt );
}

