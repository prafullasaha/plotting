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

void top_MVA(){
const int file_size=16;
float lumi=59.7;
double min_score=0.;
double max_score=1;
double MVA1_min=0;
double MVA1_max=1;
double MVA2_min=-0.2;
double MVA2_max=0.2;
const int nbins=20;
double MVA1_cut=0.3;//For ttH bkg
double MVA2_cut=0.08;//For non-Higgs bkg
float bin_width = (max_score-min_score)/nbins;

TString file[file_size] = {"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_TTGG_0Jets_pythia8.root", 
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_TTGJets_pythia8.root", 
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root", 
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/WW_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/WZ_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/ZZ_TuneCP5_13TeV-pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/TTWJetsToLNu_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/ZGTo2LG_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/TTZToLLNuNu_M-10_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/tZq_ll_4f_ckm_NLO_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/DYJetsToLL_M-50_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root",
"/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_validation_inputs/2018/output_Data_18.root"};
string procs[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox", "DiPhotonJetsBox2BJets","gjets","WW","WZ","ZZ","ttwjets","ZG","ttZ","tZq","DYJets","thq_125","tth_125","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
string procs_[file_size] = {"tt#gamma#gamma", "tt#gamma + jets","#gamma#gamma + jets", "#gamma#gamma + 2 b jets","#gamma + jets","WW","WZ","ZZ","TTW","Z + #gamma","ttZ","tZq","Drell-Yan","tHq","ttH","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
THStack *hs = new THStack("hs",";MVA_score;Events/(0.015)");
TLegend *leg1 = new TLegend(0.2, 0.6, 0.5, 0.9, "");
TLegend *leg2 = new TLegend(0.6, 0.6, 0.9, 0.9, "");
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

for(int i=0; i<file_size; i++)
	{
	TFile *file_ = new TFile(file[i], "READ");
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
		if(qweight > 0 /*&& qMVA1 < MVA1_cut && qMVA2 > MVA2_cut*/ && qn_jets >= 2 && qn_M_bjets >= 1){
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
		else
		{
		hist[i]->Fill(qMVA1, qweight);
		if(procs[i]=="tZq") hist[i]->SetFillColor(2);
		else if(procs[i]=="ttZ") hist[i]->SetFillColor(3);
		else if(procs[i]=="DYJets") hist[i]->SetFillColor(4);
		else {hist[i]->SetFillColor(5);}
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
	

	leg2->SetFillColor(0);
        leg2->SetFillStyle(0);
        leg2->SetBorderSize(0);
	if(procs[i]=="Data"){leg2->AddEntry(hist_Data, procs_[i].c_str(),"lep"); }
	else if(procs[i]=="thq_125"){leg2->AddEntry(hist_thq, "tHq x 200","l"); }
	else if(procs[i]=="tth_125"){leg2->AddEntry(hist_tth, "ttH x 10","l"); }
/*	else 
	{
	leg1->AddEntry(hist[i], procs_[i].c_str(),"f");
	}*/
	}
DataYield= hist_Data->Integral();
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
	if(procs[i]=="tZq"){hist[i]->SetFillColor(2); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else if(procs[i]=="ttZ"){ hist[i]->SetFillColor(3); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else if(procs[i]=="DYJets"){ hist[i]->SetFillColor(4); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
        else {bkg_others->Add(hist[i]); bkg_others->SetFillColor(5);}
	}
hs->Add(bkg_others);
leg1->AddEntry(bkg_others, "Others", "f");
hist_thq->Scale(200);
hist_tth->Scale(10);

	TLatex * tex = new TLatex(0.10, 0.97,TString("#bf{CMS}                                         ") +

                       Form("%.1f", lumi) + " fb^{-1} (13 TeV)");
        tex->SetNDC();
        tex->SetTextAlign(13);
        tex->SetTextFont(42);
        tex->SetTextSize(0.06);
        tex->SetLineWidth(2);
//        tex->Draw();


TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
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

TBox* box =new TBox(MVA1_cut, 0, max_score, hist_Data->GetMaximum());
box->SetFillColorAlpha(9, 0.3);
//box->Draw();
//box->SetLineColorAlpha(9, 0.571);
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
//      	hRatio->GetYaxis()->SetRangeUser(0,2);
      	hRatio->GetYaxis()->SetTitleOffset(0.4);
      	hRatio->GetYaxis()->SetTitleSize(0.1);
      	hRatio->GetXaxis()->SetTitleSize(0.1);
      	hRatio->GetXaxis()->SetLabelSize(0.11);
	hRatio->GetYaxis()->SetLabelSize(0.09);
      	hRatio->GetYaxis()->SetTitle("#frac{Data}{MC}");
      	hRatio->GetXaxis()->SetTitle("BDT-bkg");
	TH1F *hRatio_stat_Err = (TH1F*)totalMC->Clone("hRatio_stat_Err");
	hRatio_stat_Err->SetStats(0);
        hRatio_stat_Err->SetTitle(""); // remove the ratio title
        hRatio_stat_Err->GetYaxis()->SetRangeUser(0.,2.);
        hRatio_stat_Err->GetYaxis()->SetTitleOffset(0.4);
        hRatio_stat_Err->GetYaxis()->SetTitleSize(0.1);
        hRatio_stat_Err->GetXaxis()->SetTitleSize(0.11);
        hRatio_stat_Err->GetXaxis()->SetLabelSize(0.11);
        hRatio_stat_Err->GetYaxis()->SetLabelSize(0.09);
        hRatio_stat_Err->GetYaxis()->SetTitle("#frac{Data}{MC}");
	hRatio_stat_Err->GetXaxis()->SetTitleOffset(0.8);
        hRatio_stat_Err->GetXaxis()->SetTitle("BDT-bkg");
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
	hRatio_stat_Err->SetFillColor(kRed);
	hRatio_stat_Err->SetFillStyle(3001);
	hRatio_stat_Err->GetYaxis()->SetRangeUser(0,2);

	totalMC->SetLineColor(kRed);
	totalMC->SetFillColor(kRed);
	totalMC->SetFillStyle(3001);

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

leg2->AddEntry(totalMC, "Stat. Uncert." ,"f");

        leg1->SetFillColor(0);
        leg1->SetFillStyle(0);
        leg1->SetBorderSize(0);

        leg2->SetFillColor(0);
        leg2->SetFillStyle(0);
        leg2->SetBorderSize(0);

TGraphAsymmErrors* ratioEr =new TGraphAsymmErrors(hist_Data, totalMC, "pois");

ratioEr->SetLineColor(kBlack);
ratioEr->SetFillColor(kBlack);
ratioEr->SetFillStyle(3001);

c1->cd();

TPad *pad1 = new TPad("pad1","pad1",0,0.3,1.0,1.0);
pad1->SetBottomMargin(0);
pad1->SetLogy();
pad1->Draw();
pad1->cd();
        hs->Draw("hist");
	hs->GetYaxis()->SetTitle(Form("Events/(%.3f)", bin_width));
	hs->GetYaxis()->SetTitleOffset(1);
        hs->GetYaxis()->SetTitleSize(0.05);
        hs->GetYaxis()->SetLabelSize(0.05);
//        totalMC->Draw("E2 SAME");
        hs->SetMaximum(15*hist_Data->GetMaximum());
        hist_Data->Draw("E1 x0 SAME");
//	gr_Data->Draw("P");
        hist_thq->Draw("hist SAME");
        hist_tth->Draw("hist SAME");
//        l->Draw("SAME");
        leg1->Draw("SAME");
	leg2->Draw("SAME");
        tex->Draw();
	box->Draw();
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
pad2->SetTopMargin(0.1);
pad2->SetBottomMargin(0.2);
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
	l_ratio->Draw();
/*c3->cd();
c3->Divide(2,2);
c3->cd(1);
h2_thq->Draw("colz");
c3->cd(2);
h2_tth->Draw("colz");
c3->cd(3);
h2_bkg->Draw("colz");
*/
c1->SaveAs("plots/top_DNN_validation.root");
c1->SaveAs("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/top_DNN_validation_16.png");
c1->SaveAs("/eos/user/p/prsaha/www/Hgg_analysis/Variable_plots/top_DNN_validation_16.pdf");
}
