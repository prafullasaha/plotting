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
#include <fstream>
double Getsig(float s, float b){
if (s==0  && b==0) return 0;
else if (s+b < 0) return 0;
else
        return (s/sqrt(s+b));
}

int MVA_optimisation( int year=2, bool BDT_Higgs = false, bool BDT_NonHiggs = false){
//RunII
//
TFile *file_Tprime_600, *file_tth, *file_thq, *file_vh, *file_ggh, *file_vbf, *file_ttgg, *file_ttgjets, *file_DiPhotonJetsBox, *file_DiPhotonJetsBox2BJets, *file_gjets, *file_TGJets, *file_TTJets, *file_DYJets, *file_WG, *file_ZG, *file_TTWJets, *file_Data;

float MVA1_cut = 0.;
float MVA2_cut = 0.;
float lumi=0.;
string method;
TString file_path;
if(year == 2){
cout<<"Running on Run2 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/UL/output_files_Tprime600_700VsHiggs_BDTG_UL/Run2/";
//	file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files_Tprime600_700VsHiggs_BDTG/Run2/";
//	file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files/Run2/";
  	file_Tprime_600 = new TFile(file_path + "output_Tprime_600.root", "READ");
    file_tth 		= new TFile(file_path + "output_tth_125.root", "READ");
    file_thq 		= new TFile(file_path + "output_thq_125.root", "READ");
	file_ggh 		= new TFile(file_path + "output_ggh_125.root", "READ");
	file_vbf 		= new TFile(file_path + "output_vbf_125.root", "READ");
	file_vh 		= TFile::Open(file_path + "output_vh_125.root");
    file_ttgg 		= TFile::Open(file_path + "output_ttgg.root");
    file_ttgjets 	= TFile::Open(file_path + "output_ttgjets.root");
    file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox.root");
//    file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets.root");
    file_gjets 		= TFile::Open(file_path + "output_gjets.root");
    file_TTJets 	= TFile::Open(file_path + "output_ttjets.root");
    file_TGJets 	= TFile::Open(file_path + "output_tgjets.root");
    file_ZG 		= TFile::Open(file_path + "output_ZG.root");
    file_WG 		= TFile::Open(file_path + "output_WG.root");
    file_TTWJets 	= TFile::Open(file_path + "output_ttwjets.root");
    file_DYJets 	= TFile::Open(file_path + "output_DYJets.root");
	file_Data 		= new TFile(file_path + "output_Data.root", "READ");
	MVA1_cut = 0.3;
	MVA2_cut = 0.08;
	lumi=138;

	}
//2016
else if(year == 2016){
cout<<"Running on 2016 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2016/";
	file_Tprime_600 = new TFile(file_path + "output_Tprime_600.root", "READ");
        file_tth = new TFile(file_path + "output_tth_125.root", "READ");
        file_thq = new TFile(file_path + "output_thq_125.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_ttgg.root");
        file_ttgjets = TFile::Open(file_path + "output_ttgjets.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets.root");
        file_gjets = TFile::Open(file_path + "output_gjets.root");
        file_TTJets = TFile::Open(file_path + "output_ttjets.root");
        file_TGJets = TFile::Open(file_path + "output_tgjets.root");
        file_ZG = TFile::Open(file_path + "output_ZG.root");
        file_WG = TFile::Open(file_path + "output_WG.root");
        file_TTWJets = TFile::Open(file_path + "output_ttwjets.root");
        file_DYJets = TFile::Open(file_path + "output_DYJets.root");
        file_vh = TFile::Open(file_path + "output_vh_125.root");


	MVA1_cut = 0.3;
	MVA2_cut = 0.04;
	lumi=35.9;

	}
//2017
else if(year==2017){
cout<<"Running on 2017 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2017/";
        file_Tprime_600 = new TFile(file_path + "output_Tprime_600.root", "READ");
        file_tth = new TFile(file_path + "output_tth_125.root", "READ");
        file_thq = new TFile(file_path + "output_thq_125.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_ttgg.root");
        file_ttgjets = TFile::Open(file_path + "output_ttgjets.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets.root");
        file_gjets = TFile::Open(file_path + "output_gjets.root");
        file_TTJets = TFile::Open(file_path + "output_ttjets.root");
        file_TGJets = TFile::Open(file_path + "output_tgjets.root");
        file_ZG = TFile::Open(file_path + "output_ZG.root");
        file_WG = TFile::Open(file_path + "output_WG.root");
        file_TTWJets = TFile::Open(file_path + "output_ttwjets.root");
        file_DYJets = TFile::Open(file_path + "output_DYJets.root");
        file_vh = TFile::Open(file_path + "output_vh_125.root");

	MVA1_cut = 0.3;
	MVA2_cut = 0.04;
	lumi=41.5;

}
//2018
else if(year==2018){
cout<<"Running on 2018 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2018/";
        file_Tprime_600 = new TFile(file_path + "output_Tprime_600.root", "READ");
        file_tth = new TFile(file_path + "output_tth_125.root", "READ");
        file_thq = new TFile(file_path + "output_thq_125.root", "READ");
        file_ttgg = TFile::Open(file_path + "output_ttgg.root");
        file_ttgjets = TFile::Open(file_path + "output_ttgjets.root");
        file_DiPhotonJetsBox = TFile::Open(file_path + "output_DiPhotonJetsBox.root");
        file_DiPhotonJetsBox2BJets = TFile::Open(file_path + "output_DiPhotonJetsBox2BJets.root");
        file_gjets = TFile::Open(file_path + "output_gjets.root");
        file_TTJets = TFile::Open(file_path + "output_ttjets.root");
        file_TGJets = TFile::Open(file_path + "output_tgjets.root");
        file_ZG = TFile::Open(file_path + "output_ZG.root");
        file_WG = TFile::Open(file_path + "output_WG.root");
        file_TTWJets = TFile::Open(file_path + "output_ttwjets.root");
        file_DYJets = TFile::Open(file_path + "output_DYJets.root");
        file_vh = TFile::Open(file_path + "output_vh_125.root");

	MVA1_cut = 0.3;
	MVA2_cut = 0.04;
	lumi=59.5;

}
else cout<<"No file exists-------------"<<endl;

	TTree* tree_tth = (TTree*)file_tth->Get("tth_125_13TeV_THQLeptonicTag");
   	TTree* tree_thq = (TTree*)file_thq->Get("thq_125_13TeV_THQLeptonicTag");
	TTree* tree_vh = (TTree*)file_vh->Get("vh_125_13TeV_THQLeptonicTag");
	TTree* tree_ggh = (TTree*)file_ggh->Get("ggh_125_13TeV_THQLeptonicTag");
	TTree* tree_vbf = (TTree*)file_vbf->Get("vbf_125_13TeV_THQLeptonicTag");
   	TTree *tree_ttgg = (TTree*)file_ttgg->Get("ttgg_13TeV_THQLeptonicTag");
   	TTree *tree_ttgjets = (TTree*)file_ttgjets->Get("ttgjets_13TeV_THQLeptonicTag");
   	TTree *tree_DiPhotonJetsBox  = (TTree*)file_DiPhotonJetsBox->Get("DiPhotonJetsBox_13TeV_THQLeptonicTag");
//        TTree *tree_DiPhotonJetsBox2BJets  = (TTree*)file_DiPhotonJetsBox2BJets->Get("DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag");
	TTree *tree_gjets  = (TTree*)file_gjets->Get("gjets_13TeV_THQLeptonicTag");
	TTree *tree_ttjets  = (TTree*)file_TTJets->Get("ttjets_13TeV_THQLeptonicTag");
   	TTree *tree_tgjets  = (TTree*)file_TGJets->Get("tgjets_13TeV_THQLeptonicTag");
   	TTree *tree_ttwjets  = (TTree*)file_TTWJets->Get("ttwjets_13TeV_THQLeptonicTag");
   	TTree *tree_WG  = (TTree*)file_WG->Get("WG_13TeV_THQLeptonicTag");
  	TTree *tree_ZG  = (TTree*)file_ZG->Get("ZG_13TeV_THQLeptonicTag");
   	TTree *tree_DYJets  = (TTree*)file_DYJets->Get("DYJets_13TeV_THQLeptonicTag");
  	TTree *tree_Tprime_600  = (TTree*)file_Tprime_600->Get("Tprime_600_13TeV_THQLeptonicTag");
	TTree *tree_data  = (TTree*)file_Data->Get("Data_13TeV_THQLeptonicTag");

	TFile *output = new TFile("output.root","RECREATE");
   	TList *list1 = new TList;
//        list->Add(tree_tth);
  	list1->Add(tree_ttgg);
   	list1->Add(tree_ttgjets);
  	list1->Add(tree_DiPhotonJetsBox);
//        list1->Add(tree_DiPhotonJetsBox2BJets);
	list1->Add(tree_gjets);
	list1->Add(tree_ttjets);
//	list1->Add(tree_tgjets);
  	list1->Add(tree_ttwjets);
   	list1->Add(tree_WG);
   	list1->Add(tree_ZG);
  	list1->Add(tree_DYJets);


	TTree *tree_bkgNonHiggs = TTree::MergeTrees(list1);

    TList *list2 = new TList;
	list2->Add(tree_tth);
	list2->Add(tree_thq);
	list2->Add(tree_vh);
	list2->Add(tree_ggh);
	list2->Add(tree_vbf);

	TTree *tree_bkgHiggs = TTree::MergeTrees(list2);

  	Float_t qdipho_mass, qMVA1, qMVA2;
 	Float_t tdipho_mass, tMVA1, tMVA2;
	Float_t bdipho_mass, bMVA1, bMVA2;
	Float_t ddipho_mass, dMVA1, dMVA2, dlepton_leadPt;
	Float_t qweight, tweight, bweight, dweight;

	tree_bkgHiggs->SetBranchAddress("MVAscore_TprimeVsHiggs", &tMVA1);
	tree_bkgHiggs->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &tMVA2);
	tree_bkgHiggs->SetBranchAddress("weight", &tweight);
   	tree_bkgHiggs->SetBranchAddress("dipho_mass", &tdipho_mass);
   	tree_bkgHiggs->SetBranchStatus("*", 1);

  	tree_Tprime_600->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA1);
   	tree_Tprime_600->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA2);
   	tree_Tprime_600->SetBranchAddress("weight", &qweight);
   	tree_Tprime_600->SetBranchAddress("dipho_mass", &qdipho_mass);
   	tree_Tprime_600->SetBranchStatus("*", 1);

	tree_bkgNonHiggs->SetBranchAddress("MVAscore_TprimeVsHiggs", &bMVA1);
	tree_bkgNonHiggs->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &bMVA2);
	tree_bkgNonHiggs->SetBranchAddress("weight", &bweight);
    tree_bkgNonHiggs->SetBranchAddress("dipho_mass", &bdipho_mass);
    tree_bkgNonHiggs->SetBranchStatus("*", 1);

	tree_data->SetBranchAddress("MVAscore_TprimeVsHiggs", &dMVA1);
	tree_data->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &dMVA2);
 	tree_data->SetBranchAddress("weight", &dweight);
  	tree_data->SetBranchAddress("dipho_mass", &ddipho_mass);
	tree_data->SetBranchAddress("lepton_leadPt", &dlepton_leadPt);	
	tree_data->SetBranchStatus("*", 1);        

  	Int_t nentries_Tprime=(Int_t)tree_Tprime_600->GetEntries();
  	Int_t nentries_bkgHiggs=(Int_t)tree_bkgHiggs->GetEntries();
	Int_t nentries_bkg=(Int_t)tree_bkgNonHiggs->GetEntries();
	Int_t nentries_data=(Int_t)tree_data->GetEntries();

	TGraph *s_sig_wrtHiggsBkg = new TGraph();
	TGraph *s_sig_wrtNonHiggsBkg = new TGraph();
	TGraph *tHq_eff = new TGraph();
	TGraph *ttH_eff = new TGraph();
	TGraph *bkg_eff = new TGraph();
	TMultiGraph *mg = new TMultiGraph();

int N=0;
ofstream myfile;
//myfile.open ("example.txt");

//BDT-Higgs optimization( Tprime Vs ttH, tHq, VH )---------------------------------------------------------------------
if(BDT_Higgs){
cout<<"Running BDT-Higgs optimisation----------------------------------------"<<endl;
method = "BDT_Tprime600_700VsHiggs";
myfile.open (Form("%s_ScoreVsYield.txt",method.c_str()));
	for(double MVA1=0;MVA1<=1.;MVA1=MVA1+0.01){
N++;
	float s=0;
	float b=0;
	float bkg=0;
	float data=0;
	float Tprime_yield=0;
	float ttH_yield=0;
	float bkg_yield=0;
	float data_yield=0;
	 	for(int ievent=0; ievent<nentries_Tprime; ievent++){ //Signal event loop
          	tree_Tprime_600->GetEntry( ievent );
		/*if(qMVA2 > MVA2_cut)*/ Tprime_yield = Tprime_yield + (qweight);
			if(qMVA1 > MVA1 /*&& qMVA2 > MVA2_cut && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
		    	s= s+(qweight);
			}
		}
		for(int ievent=0; ievent<nentries_bkgHiggs; ievent++){ //Background event loop
           	tree_bkgHiggs->GetEntry( ievent );
			/*if(tMVA2 > MVA2_cut)*/ ttH_yield = ttH_yield + tweight;
		 	if(tMVA1 > MVA1 /*&& tMVA2 > MVA2_cut && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
	        	b= b+tweight;
			}
		}
		for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
          	tree_bkgNonHiggs->GetEntry( ievent );
/*              if(bMVA2 > MVA2_cut && (bdipho_mass < 115 || bdipho_mass > 135))*/ bkg_yield = bkg_yield + bweight;
		  	if(bMVA1 > MVA1 /*&& bMVA2 > MVA2_cut && (bdipho_mass < 115 || bdipho_mass > 135)*/){
	         	bkg = bkg+bweight;
			}
		}
		for(int ievent=0; ievent<nentries_data; ievent++){ //Data event loop
          	tree_data->GetEntry( ievent );
/*           	if(bMVA2 > MVA2_cut (ddipho_mass < 115 || ddipho_mass > 135) && dlepton_leadPt>10 )*/ data_yield = data_yield + dweight;
           	if(dMVA1 > MVA1 /*&& bMVA2 > MVA2_cut*/ && (ddipho_mass < 115 || ddipho_mass > 135)/* && dlepton_leadPt>10*/ ){
         		data = data+dweight;
//			cout<<"MVA_score= "<<dMVA1<<"ddipho_mass= "<<ddipho_mass<<endl;
         	}
		}
double s_sig_wrtHiggsBkg_ = Getsig(s,b);
double s_sig_wrtNonHiggsBkg_ = Getsig(s,bkg);
double tHq_eff_ = s/Tprime_yield;
double ttH_eff_ = b/ttH_yield;
double bkg_eff_ = bkg/bkg_yield;

//cout<<"Tprime_yield  "<<Tprime_yield<<"   s= "<<s<<endl;
//cout<<"ttH_yield  "<<ttH_yield<<"   b= "<<b<<endl;

cout<<"BDT score=  "<<MVA1<<"   Tprime_yield=  "<<s<<"   ttH_yield=  "<<b<<"   NRB=  "<<bkg<<"   s_sig_wrtHiggsBkg=   "<<s_sig_wrtHiggsBkg_<<"   Data SB=   "<<data<<endl;
if (myfile.is_open()) myfile << "BDT score=  "<<MVA1<<"   Tprime_yield=  "<<s<<"   ttH_yield=  "<<b<<"   NRB=  "<<bkg<<"   s_sig_wrtHiggsBkg=   "<<s_sig_wrtHiggsBkg_<<"   Data SB=   "<<data<<endl;
//cout<<"MVA1=  "<<MVA1<<"s_sig_wrtNonHiggsBkg   ="<<s_sig_wrtNonHiggsBkg_<<"bkg  = "<<bkg<<endl;
s_sig_wrtHiggsBkg->SetPoint(N-1, MVA1, s_sig_wrtHiggsBkg_);
s_sig_wrtNonHiggsBkg->SetPoint(N-1, MVA1, s_sig_wrtNonHiggsBkg_);
tHq_eff->SetPoint(N-1, MVA1, tHq_eff_*100);
ttH_eff->SetPoint(N-1, MVA1, ttH_eff_*100);
bkg_eff->SetPoint(N-1, MVA1, bkg_eff_*100);
}
}
//----------------------------------------------------------------------------------
//BDT optimization( tHq Vs NotHiggs background)-----------------------------------------------------
if(BDT_NonHiggs)
{
cout<<"Running BDT-NonHiggs optimisation----------------------------------------"<<endl;
method = "BDT_NonHiggs";
        for(double MVA2=-0.4;MVA2 <=0.4;MVA2=MVA2+0.02){
N++;
//cout<<"N =  "<<N<<endl;
        Float_t s=0;
        Float_t b=0;
        float bkg=0;
        float Tprime_yield=0;
        Float_t ttH_yield=0;
        float bkg_yield=0;
                for(int ievent=0; ievent<nentries_Tprime; ievent++){ //Signal event loop
                tree_Tprime_600->GetEntry( ievent );
                if(qMVA2 > -999 ){
                /*if( qMVA1 < MVA1_cut )*/ Tprime_yield = Tprime_yield + (qweight);
                        if(/*qMVA1 < MVA1_cut &&*/ qMVA2 > MVA2/* && (qdipho_mass > 122 && qdipho_mass < 128)*/ ){
                        s= s+(qweight);
                                 }
                }
                }
                for(int ievent=0; ievent<nentries_bkgHiggs; ievent++){ //Background event loop
                tree_bkgHiggs->GetEntry( ievent );
                if(tMVA2 > -999 ){
                /*if( tMVA1 < MVA1_cut )*/ ttH_yield = ttH_yield + tweight;
                if(/*tMVA1 < MVA1_cut &&*/ tMVA2 >= MVA2/* && (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                        b= b+tweight;
                        }
                }
                }
                for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
                tree_bkgNonHiggs->GetEntry( ievent );
                if(bMVA2 > -999){
                /*if( bMVA1 < MVA1_cut )*/ bkg_yield = bkg_yield + bweight;
                if(/*bMVA1 < MVA1_cut &&*/ bMVA2 > MVA2 /*&& (tdipho_mass > 122 && tdipho_mass < 128)*/ ){
                         bkg = bkg+bweight;
                        }
                }
                }
        double s_sig_wrtNonHiggsBkg_ = Getsig(s,bkg);
	double s_sig_wrtHiggsBkg_ = Getsig(s,b);
        double tHq_eff_ = s/Tprime_yield;
        double ttH_eff_ = b/ttH_yield;
        double bkg_eff_ = bkg/bkg_yield;
//        cout<<"Tprime_yield  "<<Tprime_yield<<"   s= "<<s<<endl;
//        cout<<"ttH_yield  "<<ttH_yield<<"   b= "<<b<<endl;
//        cout<<"MVA2=  "<<MVA2<<"s_sig_wrtNonHiggsBkg_   ="<<s_sig_wrtNonHiggsBkg_<<"   tHq eff= "<<tHq_eff_<<"   ttH eff"<<ttH_eff_<<endl;
cout<<"BDT score=  "<<MVA2<<"   Tprime_yield=  "<<s<<"   ttH_yield=  "<<b<<endl;

        s_sig_wrtNonHiggsBkg->SetPoint(N-1, MVA2, s_sig_wrtNonHiggsBkg_);
	s_sig_wrtHiggsBkg->SetPoint(N-1, MVA2, s_sig_wrtHiggsBkg_);
        tHq_eff->SetPoint(N-1, MVA2, tHq_eff_*100);
        ttH_eff->SetPoint(N-1, MVA2, ttH_eff_*100);
        bkg_eff->SetPoint(N-1, MVA2, bkg_eff_*100);
        }


}

s_sig_wrtHiggsBkg->SetTitle(Form("; #bf{%s score}; #bf{Significance}", method.c_str()));
s_sig_wrtNonHiggsBkg->SetTitle(Form("; #bf{%s score}; #bf{Significance}", method.c_str()));
tHq_eff->SetTitle(Form("; #bf{%s score}; #bf{Efficiency}", method.c_str()));
ttH_eff->SetTitle(Form("; #bf{%s score}; #bf{Efficiency}", method.c_str()));
bkg_eff->SetTitle(Form("; #bf{%s score}; #bf{Efficiency}", method.c_str()));
mg->SetTitle(Form("; #bf{%s score}; #bf{Efficiency}", method.c_str()));



gStyle->SetPadGridX(kTRUE);
gStyle->SetPadGridY(kTRUE);

s_sig_wrtHiggsBkg->SetMarkerStyle(20);
s_sig_wrtHiggsBkg->SetMarkerColor(2);
s_sig_wrtHiggsBkg->SetLineColor(2);
s_sig_wrtHiggsBkg->SetLineWidth(2);

s_sig_wrtNonHiggsBkg->SetMarkerStyle(20);
s_sig_wrtNonHiggsBkg->SetMarkerColor(2);
s_sig_wrtNonHiggsBkg->SetLineColor(2);
s_sig_wrtNonHiggsBkg->SetLineWidth(2);

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
    leg1->AddEntry(tHq_eff,"T' 600","pl");
    leg1->AddEntry(ttH_eff,"SMH","pl");
    leg1->AddEntry(bkg_eff,"NRB","pl");
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);

        TLatex * tex1 = new TLatex(0.12, 0.99,TString("#bf{CMS}"));
        tex1->SetNDC();
        tex1->SetTextAlign(13);
        tex1->SetTextFont(42);
        tex1->SetTextSize(0.07);
        tex1->SetLineWidth(2);

        TLatex * tex2 = new TLatex(0.53, 0.99,TString(Form("%.0f fb^{-1} (13 TeV)",lumi)));
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

//mg->GetYaxis()->SetTitleOffset(0.4);
s_sig_wrtHiggsBkg->GetYaxis()->SetTitleOffset(1.5);
s_sig_wrtNonHiggsBkg->GetYaxis()->SetTitleOffset(1.5);


mg->Add(tHq_eff);
mg->Add(ttH_eff);
mg->Add(bkg_eff);

TCanvas *sig_wrtHiggsBkg = new TCanvas("sig_wrtHiggsBkg", "sig_wrtHiggsBkg", 600, 600);
sig_wrtHiggsBkg->cd();
TPad *pad1 = new TPad("pad1","pad1",0,0,1.0,1.0);
pad1->SetTopMargin(0.075);
pad1->SetBottomMargin(0.075);
pad1->SetLeftMargin(0.120);
pad1->SetRightMargin(0.075);
pad1->SetTickx();
pad1->SetTicky();
pad1->Draw();
pad1->cd();
s_sig_wrtHiggsBkg->Draw("APL");
//l_sig->Draw("SAME");
tex1->Draw();
tex2->Draw();
TCanvas *sig_wrtNonHiggsBkg = new TCanvas("sig_wrtNonHiggsBkg", "sig_wrtNonHiggsBkg", 600, 600);
sig_wrtNonHiggsBkg->cd();
TPad *pad1_ = new TPad("pad1","pad1",0.,0.,1.0,1.0);
pad1_->SetTopMargin(0.075);
pad1_->SetBottomMargin(0.075);
pad1_->SetLeftMargin(0.120);
pad1_->SetRightMargin(0.070);
pad1_->SetTickx();
pad1_->SetTicky();
pad1_->Draw();
pad1_->cd();
s_sig_wrtNonHiggsBkg->Draw("APL");
tex1->Draw();
tex2->Draw();
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
leg1->Draw();
//l->Draw("SAME");
tex1->Draw();
tex2->Draw();

TString outdir="/eos/user/p/prsaha/www/Tprime_analysis/UL/opt/";
//eff->SaveAs(outdir + Form("%s_eff_Run%i.root",method.c_str(), year));
//sig_wrtTTH->SaveAs(outdir + Form("%s_sig_wrtHiggsBkg_Run%i.root",method.c_str(), year));
//sig_wrtBkg->SaveAs(outdir + Form("%s_sig_wrtNonHiggsBkg_Run%i.root",method.c_str(), year));

eff->SaveAs(outdir + Form("%s_eff_Run%i_BDTG.pdf",method.c_str(), year));
sig_wrtHiggsBkg->SaveAs(outdir + Form("%s_sig_wrtHiggsBkg_Run%i_BDTG.pdf",method.c_str(), year));
sig_wrtNonHiggsBkg->SaveAs(outdir + Form("%s_sig_wrtNonHiggsBkg_Run%i_BDTG.pdf",method.c_str(), year));

eff->SaveAs(outdir + Form("%s_eff_Run%i_BDTG.png",method.c_str(), year));
sig_wrtHiggsBkg->SaveAs(outdir + Form("%s_sig_wrtHiggsBkg_Run%i_BDTG.png",method.c_str(), year));
sig_wrtNonHiggsBkg->SaveAs(outdir + Form("%s_sig_wrtNonHiggsBkg_Run%i_BDTG.png",method.c_str(), year));
return 0;
}

int main(int argc, char** argv)
{
//TString methodList;
int year;
bool BDT_Higgs;
bool BDT_NonHiggs;
return MVA_optimisation( year, BDT_Higgs, BDT_NonHiggs );
}

