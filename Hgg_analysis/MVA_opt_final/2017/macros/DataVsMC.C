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

void DataVsMC(){
const int file_size=8;
TString file[file_size] = {"../output_TTGG_0Jets_pythia8.root", "../output_TTGJets_pythia8.root", "../output_DiPhotonJetsBox_MGG-80toInf_Sherpa.root", "../output_DiPhotonJetsBox2BJets_MGG-80toInf_Sherpa.root","../output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_Pythia8.root","../output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root","../output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root","../allData_17.root"};
string procs[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox", "DiPhotonJetsBox2BJets","gjets","thq_125","tth_125","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
string procs_[file_size] = {"tt#gamma#gamma", "tt#gamma jets","#gamma #gammaJets", "#gamma #gamma Jets2BJets","#gamma Jets","tHq","ttH","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};
THStack *hs = new THStack("hs",";MVA_score;Events");
TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9, "");
const int nbins=70;
int count=0;
double lumi=41.5;
double min_score=-0.3;
double max_score=0.4;
double MVA1_min=0.;
double MVA1_max=1.;
double MVA2_min=-0.3;
double MVA2_max=0.4;
TH1F* hist_Data=new TH1F("MVA_score_data",";MVA_score",nbins,min_score,max_score);
TH1F* hist_thq=new TH1F("MVA_score_thq",";MVA_score",nbins,min_score,max_score);
TH1F* hist_tth=new TH1F("MVA_score_tth",";MVA_score",nbins,min_score,max_score);
TH2F* h2_thq=new TH2F("MVA_thq","tHq;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_tth=new TH2F("MVA_tth","ttH;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_bkg=new TH2F("MVA_sig","Background;MVAscore_tHqVsttH;MVAscore_tHqVsBkg",nbins,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH1F* hist[file_size];
gStyle->SetOptStat(0);
gStyle->SetCanvasPreferGL(true);
float totalMCYield=0;
float DataYield=0;
double MVA1_cut=0.3;//For ttH bkg
double MVA2_cut=0.05;//For non-Higgs bkg
int MVA_no = 1;
for(int i=0; i<file_size; i++)
	{
	TFile *file_ = new TFile(file[i], "READ");
	TTree* tree_ = (TTree*)file_->Get(Form("tagsDumper/trees/%s_13TeV_THQLeptonicTag", procs[i].c_str()));
	Float_t qdipho_mass, qweight, qMVA1, qMVA2;
	tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
	tree_->SetBranchAddress("MVAscore_tHqVsttH_DNN", &qMVA1);//MVAresult_thq
	tree_->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &qMVA2);
        tree_->SetBranchAddress("weight", &qweight);
        tree_->SetBranchStatus("*", 1);
	Int_t nentries=(Int_t)tree_->GetEntries();
	hist[i]=new TH1F("MVA_score_Bkg"," ;m_{#gamma#gamma}",nbins,min_score,max_score);
		for(int ievent=0; ievent < nentries; ievent++)
                {
                tree_-> GetEntry( ievent );
		if(/*qweight > 0 &&*/ qMVA1 < MVA1_cut /*&& qMVA2 > MVA2_cut*/){
		if(procs[i]=="Data") 
		{
		if(qdipho_mass<115 || qdipho_mass>135){
		hist_Data->Fill(qMVA2, qweight);
		hist_Data->SetMarkerStyle(20);
		hist_Data->SetMarkerSize(1.5);
	        hist_Data->SetMarkerColor(kBlack);
		}
		}
		else if(procs[i]=="thq_125")
		{
		hist_thq->Fill(qMVA2, qweight);
		hist_thq->SetLineWidth(3);
		hist_thq->SetLineColor(kBlack);
		h2_thq->Fill(qMVA1, qMVA2, qweight);
		}
		else if(procs[i]=="tth_125")
                {
		hist_tth->Fill(qMVA2, qweight);
                hist_tth->SetLineWidth(3);
                hist_tth->SetLineColor(kRed);
		h2_tth->Fill(qMVA1, qMVA2, qweight);	
                }
		else
		{
		hist[i]->Fill(qMVA2, qweight);
		hist[i]->SetFillColor(9-i);
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
	if(procs[i]=="Data"){leg1->AddEntry(hist_Data, procs_[i].c_str(),"p"); }
	else if(procs[i]=="thq_125"){leg1->AddEntry(hist_thq, "tHq(m_{H}=125)x200","l"); }
	else if(procs[i]=="tth_125"){leg1->AddEntry(hist_tth, "ttH(m_{H}=125)x10","l"); }
	else 
	{
	leg1->AddEntry(hist[i], procs_[i].c_str(),"f");
	}
	}
DataYield= hist_Data->Integral();
cout<<"totalMCYield   ="<<totalMCYield<<endl;
cout<<"DataYield   ="<<DataYield<<endl;
cout<<"ttH Yield   ="<<hist_tth->Integral()<<endl;
cout<<"tHq Yield   ="<<hist_thq->Integral()<<endl;
for(int j=0; j<5; j++){
hist[j]->Scale(DataYield/totalMCYield);
hs->Add(hist[j]);
//hist[j]->Draw("");
}

hist_thq->Scale(200);
hist_tth->Scale(10);

        TLatex * tex = new TLatex(0.10, 0.97,TString("#bf{CMS} Preliminary    ") +
                                  Form("%.1f", lumi) + " fb^{-1} (13 TeV)");

        tex->SetNDC();
        tex->SetTextAlign(13);
        tex->SetTextFont(42);
        tex->SetTextSize(0.045);
        tex->SetLineWidth(2);
//        tex->Draw();
TBox* box =new TBox(min_score, 0, MVA2_cut, 1.3*hist_Data->GetMaximum());
box->SetFillColorAlpha(9, 0.3);

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
//TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
TCanvas *c3 = new TCanvas("c3", "c3", 600, 600);

TLine *l = new TLine(MVA2_cut,0,MVA2_cut,1.3*hist_Data->GetMaximum());
l->SetLineWidth(3);
l->SetLineColor(13);
l->SetLineStyle(7);

c1->cd();
hs->Draw("hist");
hs->SetMaximum(1.3*hist_Data->GetMaximum());
hist_Data->Draw("E1 SAME");
hist_thq->Draw("hist SAME");
hist_tth->Draw("hist SAME");
box->Draw();
l->Draw("SAME");
leg1->Draw("SAME");
tex->Draw();
c1->SaveAs("plots/BDTscore_NonHiggs_17.root");
c3->cd();
c3->Divide(2,2);
c3->cd(1);
h2_thq->Draw("colz");
c3->cd(2);
h2_tth->Draw("colz");
c3->cd(3);
h2_bkg->Draw("colz");
}
