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

int MVA_Validation(int year=2, bool BDT_val =false, bool DNN_val = false){
const int file_size=16;
float lumi=0;
double min_score=0.;
double max_score=1;

if(DNN_val){
min_score=0.;
max_score=1;
};

if(BDT_val){
min_score=-0.3;
max_score=0.2;
};

double MVA1_min=0;
double MVA1_max=1;
double MVA2_min=-0.3;
double MVA2_max=0.15;
const int nbins=30;
double MVA1_cut=0.2;//For ttH bkg
double MVA2_cut=0.04;//For non-Higgs bkg
float bin_width = (max_score-min_score)/nbins;

std::vector<TString> file;
TString file_path;
cout<<"year"<<year<<endl;
string method;

if(year==2016){
file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/UL/2016/";
file.push_back("output_TTGG_0Jets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root");
file.push_back("output_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root");
file.push_back("output_WW_TuneCUETP8M1_13TeV-pythia8.root");
file.push_back("output_WZ_TuneCUETP8M1_13TeV-pythia8.root");
file.push_back("output_ZZ_TuneCUETP8M1_13TeV-pythia8.root");
file.push_back("output_TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("output_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root");
file.push_back("output_tZq_ll_4f_13TeV-amcatnlo-pythia8.root");
file.push_back("output_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root");
file.push_back("output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
file.push_back("output_DoubleEG_Run2016.root");
lumi=35.9;
}
if(year==2017){
file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/UL/2017/";
file.push_back("output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
file.push_back("output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root");
file.push_back("WW_TuneCP5_13TeV-pythia8.root");
file.push_back("WZ_TuneCP5_13TeV-pythia8.root");
file.push_back("ZZ_TuneCP5_13TeV-pythia8.root");
file.push_back("TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8.root");
file.push_back("output_tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8.root");
file.push_back("DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root");
file.push_back("output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
file.push_back("output_DoubleEG_Run2017.root");
lumi=41.5;
}

if(year==2018){
file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/UL/2018/";
file.push_back("output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
file.push_back("output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root");
file.push_back("WW_TuneCP5_13TeV-pythia8.root");
file.push_back("WZ_TuneCP5_13TeV-pythia8.root");
file.push_back("ZZ_TuneCP5_13TeV-pythia8.root");
file.push_back("TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8.root");
file.push_back("tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8.root");
file.push_back("DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root");
file.push_back("output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
file.push_back("output_EGamma_Run2018.root");
lumi=59.5;
}

if(year==2){
file_path = "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/UL/RunII/";
file.push_back("output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
file.push_back("output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root");
file.push_back("WW_TuneCP5_13TeV-pythia8.root");
file.push_back("WZ_TuneCP5_13TeV-pythia8.root");
file.push_back("ZZ_TuneCP5_13TeV-pythia8.root");
file.push_back("TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
file.push_back("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8.root");
file.push_back("output_tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8.root");
file.push_back("DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root");
file.push_back("output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root");
file.push_back("output_Data_Run2.root");
lumi=137;
}

string procs[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox", "DiPhotonJetsBox2BJets","gjets","WW","WZ","ZZ","ttwjets","ZG","ttZ","tZq","DYJets","thq_125","tth_125","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
string procs_[file_size] = {"tt#gamma#gamma", "tt#gamma + jets","#gamma#gamma + jets", "#gamma#gamma + 2 b jets","#gamma + jets","WW","WZ","ZZ","TTW","Z + #gamma","ttZ(Z#rightarrow e^{+}e^{-})","tZq(Z#rightarrow e^{+}e^{-})","Drell-Yan","tHq","ttH","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
THStack *hs = new THStack("hs",Form(";MVA_score;Events/(%.3f)",bin_width));
TLegend *leg1 = new TLegend(0.45, 0.67, 0.89, 0.89, "");
leg1->SetNColumns(2);
//TLegend *leg2 = new TLegend(0.6, 0.65, 0.85, 0.87, "");
int count=0;

TH1F* hist_Data=new TH1F("MVA_score_data",";MVA_score",nbins,min_score,max_score);
TH1F* hist_thq=new TH1F("MVA_score_thq",";MVA_score",nbins,min_score,max_score);
TH1F* hist_tth=new TH1F("MVA_score_tth",";MVA_score",nbins,min_score,max_score);
TH1F* totalMC=new TH1F("totalMC",";BDT_score",nbins,min_score,max_score);
TH1F* bkg_others=new TH1F("bkg_others",";BDT_score",nbins,min_score,max_score);
TGraphErrors *gr_Data = new TGraphErrors();
TGraphErrors *gr_Ratio = new TGraphErrors();
TH2F* h2_thq=new TH2F("MVA_thq","tHq;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_tth=new TH2F("MVA_tth","ttH;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_bkg=new TH2F("MVA_sig","Background;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH1F* hist[file_size];

gStyle->SetOptStat(0);
gStyle->SetCanvasPreferGL(true);
//gStyle->SetErrorX(0);
float totalMCYield=0;
float DataYield=0;
int MVA_no = 1;
float scaleWeight= 137.1/95.4;

if(DNN_val){
cout<<"Running DNN Validation----------------------------------------"<<endl;
method = "DNN";
for(int i=0; i<file_size; i++)
	{
	TFile *file_ = new TFile(file_path + file.at(i), "READ");
	TTree* tree_ = (TTree*)file_->Get(Form("tagsDumper/trees/%s_13TeV_THQLeptonicTag", procs[i].c_str()));
	Float_t qdipho_mass, qweight, qMVA1, qMVA2, qn_jets, qn_M_bjets;
	tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
	tree_->SetBranchAddress("MVAscore_tHqVsttH_DNN", &qMVA1);//MVAresult_thq
	tree_->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &qMVA2);
        tree_->SetBranchAddress("weight", &qweight);
	tree_->SetBranchAddress("n_jets", &qn_jets);
	tree_->SetBranchAddress("n_M_bjets", &qn_M_bjets);
        tree_->SetBranchStatus("*", 1);
	Int_t nentries=(Int_t)tree_->GetEntries();
	hist[i]=new TH1F("MVA_score_Bkg"," ;m_{#gamma#gamma}",nbins,min_score,max_score);
		for(int ievent=0; ievent < nentries; ievent++)
                {
                tree_-> GetEntry( ievent );
		if(qweight > 0 /*&& qMVA1 < MVA1_cut && qMVA2 > MVA2_cut && qn_jets >= 2 && qn_M_bjets >= 1*/){
		if(procs[i]=="Data") 
		{
		if(qdipho_mass<115 || qdipho_mass>135){
		hist_Data->Fill(qMVA1, qweight);
		}
		}
		else if(procs[i]=="thq_125")
		{
		hist_thq->Fill(qMVA1, qweight);
		h2_thq->Fill(qMVA1, qMVA2, qweight);
		}
		else if(procs[i]=="tth_125")
		{
		hist_tth->Fill(qMVA1, qweight);
		h2_tth->Fill(qMVA1, qMVA2, qweight);	
                }
		else if(procs[i]=="tZq")
		{ 
//		hist[i]->SetFillColor(2); 
//		hist[i]->SetLineColor(2);
		hist[i]->Fill(qMVA1, qweight);}
		else
		{
		hist[i]->Fill(qMVA1, qweight);
//		if(procs[i]=="ttZ"){ hist[i]->SetFillColor(3); hist[i]->SetLineColor(3);}
//		else if(procs[i]=="DYJets"){ hist[i]->SetFillColor(4); hist[i]->SetLineColor(4);}
//		else {hist[i]->SetFillColor(5); hist[i]->SetLineColor(5);}
		h2_bkg->Fill(qMVA1, qMVA2, qweight);
		}
                }
		}
	if(procs[i] != "thq_125" || procs[i] != "Data"){
	totalMCYield= totalMCYield + hist[i]->Integral();
	}
	leg1->SetFillColor(0);
	leg1->SetFillStyle(0);
	leg1->SetBorderSize(0);
	

//	leg2->SetFillColor(0);
//        leg2->SetFillStyle(0);
//        leg2->SetBorderSize(0);
	if(procs[i]=="Data"){leg1->AddEntry(hist_Data, procs_[i].c_str(),"ep"); }
//	else if(procs[i]=="thq_125"){leg2->AddEntry(hist_thq, "tHq x 200","f"); }
//	else if(procs[i]=="tth_125"){leg2->AddEntry(hist_tth, "ttH x 10","f"); }
/*	else 
	{
	leg1->AddEntry(hist[i], procs_[i].c_str(),"f");
	}*/
	}
}
//End of DNN val if loop

if(BDT_val){
cout<<"Running BDT Validation----------------------------------------"<<endl;
method = "BDT";
for(int i=0; i<file_size; i++)
        {
        TFile *file_ = new TFile(file_path + file.at(i), "READ");
        TTree* tree_ = (TTree*)file_->Get(Form("tagsDumper/trees/%s_13TeV_THQLeptonicTag", procs[i].c_str()));
        Float_t qdipho_mass, qweight, qMVA1, qMVA2, qn_jets, qn_M_bjets;
        tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
        tree_->SetBranchAddress("MVAscore_tHqVsttH_DNN", &qMVA1);//MVAresult_thq
        tree_->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &qMVA2);
        tree_->SetBranchAddress("weight", &qweight);
        tree_->SetBranchAddress("n_jets", &qn_jets);
        tree_->SetBranchAddress("n_M_bjets", &qn_M_bjets);
        tree_->SetBranchStatus("*", 1);
        Int_t nentries=(Int_t)tree_->GetEntries();
        hist[i]=new TH1F("MVA_score_Bkg"," ;m_{#gamma#gamma}",nbins,min_score,max_score);
                for(int ievent=0; ievent < nentries; ievent++)
                {
                tree_-> GetEntry( ievent );
                if(qweight > 0 /*&& qMVA1 < MVA1_cut && qMVA2 > MVA2_cut && qn_jets >= 2 && qn_M_bjets >= 1*/){
                if(procs[i]=="Data")
                {
                if(qdipho_mass<115 || qdipho_mass>135){
                hist_Data->Fill(qMVA2, qweight);
                }
                }
                else if(procs[i]=="thq_125")
                {
                hist_thq->Fill(qMVA2, qweight);
                h2_thq->Fill(qMVA1, qMVA2, qweight);
                }
                else if(procs[i]=="tth_125")
                {
                hist_tth->Fill(qMVA2, qweight);
                h2_tth->Fill(qMVA1, qMVA2, qweight);
                }
                else if(procs[i]=="tZq")
                {
//                hist[i]->SetFillColor(2);
//		hist[i]->SetLineColor(2);
                hist[i]->Fill(qMVA2, qweight);
                }
                else
                {
                hist[i]->Fill(qMVA2, qweight);
//                if(procs[i]=="ttZ") hist[i]->SetFillColor(3);
//                else if(procs[i]=="DYJets") hist[i]->SetFillColor(4);
//                else {hist[i]->SetFillColor(5);}
                h2_bkg->Fill(qMVA1, qMVA2, qweight);
                }
                }
                }
        if(procs[i] != "thq_125" || procs[i] != "Data"){
        totalMCYield= totalMCYield + hist[i]->Integral();
        }
        leg1->SetFillColor(0);
        leg1->SetFillStyle(0);
        leg1->SetBorderSize(0);


//        leg2->SetFillColor(0);
//        leg2->SetFillStyle(0);
//        leg2->SetBorderSize(0);
        if(procs[i]=="Data"){leg1->AddEntry(hist_Data, procs_[i].c_str(),"ep"); }
//        else if(procs[i]=="thq_125"){leg2->AddEntry(hist_thq, "tHq x 200","f"); }
//        else if(procs[i]=="tth_125"){leg2->AddEntry(hist_tth, "ttH x 10","f"); }
/*      else 
        {
        leg1->AddEntry(hist[i], procs_[i].c_str(),"f");
        }*/
        }

}
//end of BDT_opt loop
DataYield= hist_Data->Integral(0, nbins+1);
cout<<"totalMCYield   ="<<totalMCYield<<endl;
cout<<"DataYield   ="<<DataYield<<endl;
cout<<"ttH Yield   ="<<hist_tth->Integral()<<endl;
cout<<"tHq Yield   ="<<hist_thq->Integral()<<endl;
	for(int j=0; j<(file_size-3); j++){
	hist[j]->Scale(DataYield/totalMCYield);
//	hs->Add(hist[j]);
	totalMC->Add(hist[j]);
	//hist[j]->Draw("");
	}

	for(int i=0 ; i<file_size; i++)
	{
	if(procs[i]=="tZq"){hist[i]->SetFillColor(kPink+3); hist[i]->SetLineColor(kPink+3); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else if(procs[i]=="ttZ"){ hist[i]->SetFillColor(kAzure+7); hist[i]->SetLineColor(kAzure+7); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else if(procs[i]=="DYJets"){ hist[i]->SetFillColor(kCyan); hist[i]->SetLineColor(kCyan); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else {bkg_others->Add(hist[i]); bkg_others->SetFillColor(kGreen); bkg_others->SetLineColor(kGreen);}
	}
hs->Add(bkg_others);
leg1->AddEntry(bkg_others, "Others", "f");
hist_thq->Scale(200);
hist_tth->Scale(10);

	TLatex * tex1 = new TLatex(0.12, 0.99 ,TString("#bf{CMS}"));
        tex1->SetNDC();
        tex1->SetTextAlign(13);
        tex1->SetTextFont(42);
        tex1->SetTextSize(0.07);
        tex1->SetLineWidth(2);
//        tex->Draw();

        TLatex * tex2 = new TLatex(0.6, 0.99,TString(Form("%.0f fb^{-1} (13 TeV)",lumi)));
        tex2->SetNDC();
        tex2->SetTextAlign(13);
        tex2->SetTextFont(42);
        tex2->SetTextSize(0.06);
        tex2->SetLineWidth(2);


TCanvas *c1 = new TCanvas("c1", "c1", 600, 700);
//TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
//TCanvas *c3 = new TCanvas("c3", "c3", 600, 600);

TLine *l = new TLine(MVA1_cut,0,MVA1_cut,100);
l->SetLineWidth(3);
l->SetLineColor(13);
l->SetLineStyle(7);

TLine *l_ratio = new TLine(min_score,1,max_score,1);
l_ratio->SetLineWidth(3);
l_ratio->SetLineColor(kBlue);
l_ratio->SetLineStyle(7);

	hist_Data->SetMarkerStyle(20);
        hist_Data->SetMarkerSize(1);
        hist_Data->SetMarkerColor(kBlack);
	hist_Data->SetLineWidth(2);
        hist_Data->SetLineColor(kBlack);

	hist_thq->SetLineWidth(3);
        hist_thq->SetLineColor(kBlack);

	hist_tth->SetLineWidth(3);
        hist_tth->SetLineColor(kRed);
	
      	TH1F *hRatio = (TH1F*)hist_Data->Clone("hRatio");
      	hRatio->Reset();
      	hRatio->Add(hist_Data);
      	hRatio->Divide(totalMC);
      	hRatio->SetStats(0);
      	hRatio->SetMarkerStyle(20);
        hRatio->SetMarkerSize(1);
      	hRatio->SetTitle(""); // remove the ratio title
/*      	hRatio->GetYaxis()->SetRangeUser(0,2);
      	hRatio->GetYaxis()->SetTitleOffset(0.4);
      	hRatio->GetYaxis()->SetTitleSize(0.13);
      	hRatio->GetXaxis()->SetTitleSize(0.13);
      	hRatio->GetXaxis()->SetLabelSize(0.11);
	hRatio->GetYaxis()->SetLabelSize(0.09);
      	hRatio->GetYaxis()->SetTitle("Data/MC");
      	hRatio->GetXaxis()->SetTitle("BDT-bkg");
*/
	TH1F *hRatio_stat_Err = (TH1F*)totalMC->Clone("hRatio_stat_Err");
	hRatio_stat_Err->SetStats(0);
        hRatio_stat_Err->SetTitle(""); // remove the ratio title
        hRatio_stat_Err->GetYaxis()->SetRangeUser(-1,3.);
        hRatio_stat_Err->GetYaxis()->SetTitleOffset(0.4);

        hRatio_stat_Err->GetYaxis()->SetTitleSize(0.13);
        hRatio_stat_Err->GetXaxis()->SetTitleSize(0.12);

        hRatio_stat_Err->GetXaxis()->SetLabelSize(0.10);
        hRatio_stat_Err->GetYaxis()->SetLabelSize(0.10);
        hRatio_stat_Err->GetYaxis()->SetTitle("Data/MC");

//	hRatio_stat_Err->GetXaxis()->SetTitleOffset(0.7);
        hRatio_stat_Err->GetXaxis()->SetLabelOffset(0.035);
        hRatio_stat_Err->GetYaxis()->SetLabelOffset(0.01);	
//        hRatio_stat_Err->GetXaxis()->SetTitle("BDT-bkg");
	hRatio_stat_Err->GetYaxis()->SetNdivisions(5);

	for (int ibin=0; ibin<hRatio_stat_Err->GetNbinsX()+2; ibin++)
	{
	hRatio_stat_Err->SetBinContent(ibin, 1);
	double err = hRatio->GetBinContent(ibin)*sqrt(pow((totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)),2)+pow((hist_Data->GetBinError(ibin)/hist_Data->GetBinContent(ibin)),2));
	double err_MC = hRatio->GetBinContent(ibin)*sqrt(pow((totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)),2));
	hRatio_stat_Err->SetBinError(ibin, err_MC);
	if(ibin > 0 && ibin < hRatio_stat_Err->GetNbinsX()+1 ){
	gr_Data->SetPoint(ibin-1, hist_Data->GetBinCenter(ibin), hist_Data->GetBinContent(ibin));
	gr_Data->SetPointError(ibin-1, 0, hist_Data->GetBinError(ibin));
	gr_Ratio->SetPoint(ibin-1, hRatio->GetBinCenter(ibin), hRatio->GetBinContent(ibin));
	gr_Ratio->SetPointError(ibin-1, 0, hRatio->GetBinError(ibin));
	}
	}

	hRatio_stat_Err->SetLineColor(kRed);
//	hRatio_stat_Err->SetFillColor(kRed);
//	hRatio_stat_Err->SetFillStyle(3001);
TBox* box;
if(DNN_val){
	hRatio_stat_Err->GetYaxis()->SetRangeUser(-1,3);
	hRatio_stat_Err->GetXaxis()->SetTitle("top DNN");
	box =new TBox(MVA1_cut, 0, max_score, totalMC->GetMaximum());
}
else {hRatio_stat_Err->GetYaxis()->SetRangeUser(0,2);
      hRatio_stat_Err->GetXaxis()->SetTitle("BDT-bkg");
      box =new TBox(min_score, 0, MVA2_cut, totalMC->GetMaximum());
}
	hRatio_stat_Err->SetFillColorAlpha(kRed, 0.25);

	box->SetFillColorAlpha(kBlack, 0.15);
	totalMC->SetLineColor(0);
//	totalMC->SetFillColor(kRed);
//	totalMC->SetFillStyle(3001);
	totalMC->SetFillColorAlpha(kRed, 0.25);

	gr_Data->SetMarkerStyle(20);
        gr_Data->SetMarkerSize(1);
        gr_Data->SetMarkerColor(kBlack);
        gr_Data->SetLineWidth(2);
        gr_Data->SetLineColor(kBlack);

	gr_Ratio->SetMarkerStyle(20);
        gr_Ratio->SetMarkerSize(1);
        gr_Ratio->SetMarkerColor(kBlack);
        gr_Ratio->SetLineWidth(2);
        gr_Ratio->SetLineColor(kBlack);
	gr_Ratio->GetXaxis()->SetRangeUser(min_score, max_score);

leg1->AddEntry(totalMC, "Stat. Uncert." ,"f");
//leg2->AddEntry((TObject*)0, "", "");
//leg2->AddEntry((TObject*)0, "", "");

        leg1->SetFillColor(0);
        leg1->SetFillStyle(0);
        leg1->SetBorderSize(0);

//        leg2->SetFillColor(0);
//        leg2->SetFillStyle(0);
//        leg2->SetBorderSize(0);

TGraphAsymmErrors* ratioEr =new TGraphAsymmErrors(hist_Data, totalMC, "pois");

ratioEr->SetLineColor(kBlack);
ratioEr->SetFillColor(kBlack);
ratioEr->SetFillStyle(3001);

hs->Draw();
      hs->GetYaxis()->SetTitle(Form("Events/(%.3f)", bin_width));
        hs->GetYaxis()->SetTitleOffset(0.9);
        hs->GetYaxis()->SetTitleSize(0.06);
        hs->GetYaxis()->SetLabelSize(0.04);



c1->cd();

TPad *pad1 = new TPad("pad1","pad1",0,0.30,1.0,1.0);
pad1->SetTopMargin(0.075);
pad1->SetBottomMargin(0);
pad1->SetLeftMargin(0.120);
pad1->SetRightMargin(0.070);
pad1->SetLogy();
pad1->SetTickx();
pad1->SetTicky();
pad1->Draw();
pad1->cd();
        hs->Draw("hist");
/*	hs->GetYaxis()->SetTitle(Form("Events/(%.3f)", bin_width));
	hs->GetYaxis()->SetTitleOffset(1);
        hs->GetYaxis()->SetTitleSize(0.05);
        hs->GetYaxis()->SetLabelSize(0.05);
*/        totalMC->Draw("E2 SAME");
if(BDT_val){
        hs->SetMaximum(10*hist_Data->GetMaximum());
}
else hs->SetMaximum(2.5*hist_Data->GetMaximum());

        hist_Data->Draw("E1 x0 SAME");
//	gr_Data->Draw("P");
//        hist_thq->Draw("hist SAME");
//        hist_tth->Draw("hist SAME");
//        l->Draw("SAME");
        leg1->Draw("SAME");
//	leg2->Draw("SAME");
        tex1->Draw();
	tex2->Draw();
//	box->Draw();
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.30);
pad2->SetTopMargin(0.1);
pad2->SetLeftMargin(0.120);
pad2->SetRightMargin(0.070);
pad2->SetBottomMargin(0.35);
pad2->SetGridx();
pad2->SetGridy();
pad2->Draw();
pad2->cd();

//	gr_Ratio->Draw("AP");
//        ratioEr->Draw("E2");
//	gStyle->SetErrorX(1);
	hRatio_stat_Err->Draw("E2");
//	gStyle->SetErrorX(0);
	hRatio->Draw("SAME E1 x0");
//	gr_Ratio->Draw("P");
//	l_ratio->Draw();
/*c3->cd();
c3->Divide(2,2);
c3->cd(1);
h2_thq->Draw("colz");
c3->cd(2);
h2_tth->Draw("colz");
c3->cd(3);
h2_bkg->Draw("colz");
*/
c1->SaveAs(Form("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/%s_Validation_Run%i.root",method.c_str(),year));
c1->SaveAs(Form("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/%s_Validation_Run%i.png",method.c_str(),year));
c1->SaveAs(Form("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/%s_Validation_Run%i.pdf",method.c_str(),year));
return 0;


}

int main(int argc, char** argv)
{
int year;
bool DNN_val;
bool BDT_val;
return MVA_Validation( year, BDT_val, DNN_val );
}



