#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TSelector.h>
#include <TTreePlayer.h>

#include "TLorentzVector.h"
#include "TVector.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"

using namespace std;

void DiphoMass_pt_over_mggCutComp(){

gStyle->SetOptStat(0);
gROOT->SetBatch(1);
TString file_path;
std::vector<TString> file;
/*file_path = "/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/RunII/";
file.push_back("output_TprimeBToTH_Hgg_M-600_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-625_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-650_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-675_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-900_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-1100_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
file.push_back("output_TprimeBToTH_Hgg_M-1200_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root");
*/
file_path = "/afs/cern.ch/work/p/prsaha/public/Tprime_analysis/flashgg_legacy_runII_v5/CMSSW_10_6_8/src/flashgg/Systematics/test/";//output_files_Tprime600_700VsHiggs_BDTG/Run2";
file.push_back("output_numEvent30000.root");
file.push_back("output_numEvent30000_WOpt_over_mgg.root");

const int file_size = 2;
TH1F* hist[file_size];
TH1F* hist_NonHiggs[file_size];
TH1F* hist_ =new TH1F("MVA_score_HiggsBkg"," ;m_{#gamma#gamma}", 200, 300, 1500);

//TLegend *leg1 = new TLegend(0.2, 0.6, 0.6, 0.87, "");
//TLegend *leg1 = new TLegend(0.85, 0.3, 0.95, 0.87, "");
TLegend *leg1 = new TLegend(0.4, 0.7, 0.9, 0.87, "");
leg1->SetNColumns(3);

//string procs[file_size] = {"Tprime_600","Tprime_625", "Tprime_650", "Tprime_675", "Tprime_700", "Tprime_800", "Tprime_900", "Tprime_1000", "Tprime_1100", "Tprime_1200"};

//string m_range[3] = {"600_700","800_1000","1100_1200"};
int i=0;

for(i=0; i<file.size(); i++)
	{
	TFile *file_;
	file_ = new TFile(file_path + file.at(i), "READ");
//		hist[i] =new TH1F("hist"," ;Tprime_mass", 400, 460, 800);
	
    TTree* tree_ = (TTree*)file_->Get("tagsDumper/trees/TprimeM600_125_13TeV_THQLeptonicTag");
	Float_t qdipho_mass, qTprime_mass, qweight, qMVA_HiggsBkg, qMVA_NonHiggsBkg;
    tree_->SetBranchAddress("CMS_hgg_mass", &qdipho_mass);
//    tree_->SetBranchAddress("weight", &qweight);
    tree_->SetBranchStatus("*", 1);
    Int_t nentries=(Int_t)tree_->GetEntries();
    hist[i] =new TH1F("hist"," ;m_{#gamma#gamma}", 200, 100, 180);   
//    hist_NonHiggs[i] =new TH1F("MVA_score_NonHiggsBkg"," ;MVA_score_NonHiggsBkg", 100, -0.4, 0.4);
	for(int ievent=0; ievent < nentries/*15000*/; ievent++)
	{
    bool cut=false;
	tree_-> GetEntry( ievent );
//cout<<"Cut ="<< cut <<endl;
	hist[i]->Fill(qdipho_mass);
//		hist_NonHiggs[i]->Fill(qMVA_NonHiggsBkg);
	}

	hist[i]->SetLineWidth(2);
//    hist_NonHiggs[i]->SetLineWidth(2);
	if(i == 0){
		hist[i]->SetLineColor(46);
//		hist_NonHiggs[i]->SetLineColor(46);
    	hist[i]->SetLineStyle(46);
//    	hist_NonHiggs[i]->SetLineStyle(46);
		hist[i]->Scale(1/hist[i]->Integral());
	}
	else{
    	hist[i]->SetLineColor(i);
//        hist_NonHiggs[i]->SetLineColor(i);
        hist[i]->SetLineStyle(i);
//        hist_NonHiggs[i]->SetLineStyle(i);
		hist[i]->Scale(1/hist[i]->Integral());
	}
	}
/*
TCanvas *c1 = new TCanvas("c1", "c1", 900, 600);
c1->cd();
//hist->Draw();
hist_NonHiggs[0]->Draw("hist");
leg1->AddEntry(hist_NonHiggs[0], procs[0].c_str(),"f");
hist_NonHiggs[0]->SetMaximum(2*(hist_NonHiggs[0]->GetMaximum()));
for(int j=1; j<file.size(); j++)
{
hist_NonHiggs[j]->Draw("SAME hist");
leg1->AddEntry(hist_NonHiggs[j], procs[j].c_str(),"f");
}
leg1->Draw("SAME");
*/
float lumi=137;
TLatex * tex1 = new TLatex(0.1, 0.94,TString("#bf{CMS} #it{work in progress}"));
     tex1->SetNDC();
     tex1->SetTextAlign(13);
     tex1->SetTextFont(42);
     tex1->SetTextSize(0.04);
     tex1->SetLineWidth(2);

     TLatex * tex2 = new TLatex(0.7, 0.94,TString(Form("%.0f fb^{-1} (13 TeV)",lumi)));
     tex2->SetNDC();
     tex2->SetTextAlign(13);
     tex2->SetTextFont(42);
     tex2->SetTextSize(0.03);
     tex2->SetLineWidth(2);

TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
c2->cd();
c2->SetGridx();
c2->SetGridy();
//hist[0]->GetXaxis()->SetNdivisions(20);
//TF1 *g1 = new TF1("g1","gaus", hist[0]->GetMean(), hist[0]->GetStdDev());
//TF1 *g2 = new TF1("g2","([5])*([0]/sqrt(2*TMath::Pi())*[2])*exp(-pow((x-[1]),2)/2*[2]*[2])+(1-[5])*([3]/sqrt(2*TMath::Pi())*[4])*exp(-pow((x-[1]),2)/2*[4]*[4])",hist[0]->GetMean(),hist[0]->GetStdDev());
//hist[0]->Fit("g2", "M");
hist[0]->Draw("hist");
//hist[0]->Draw("PE"); hist[0]->Draw("HIST L SAME");
hist[0]->SetMaximum(1.2*(hist[0]->GetMaximum()));
//hist[0]->SetMinimum(0.005);
//hist[0]->GetYaxis()->SetRangeUser(0.001,0.05);
hist[0]->GetYaxis()->SetTitle(Form("Normalised Events/(%0.3fGeV)",hist[0]->GetBinWidth(1)));
hist[0]->GetYaxis()->SetTitleOffset(1.4444);
//hist[0]->GetYaxis()->SetTitleSize(0.06);
//hist[0]->GetYaxis()->SetLabelSize(0.04);

leg1->AddEntry(hist[0], "W/O pt_over_mgg cut","f");
for(int j=1; j<file.size(); j++)
{
//TF1 *g1 = new TF1("g1","gaus", hist[j]->GetMean(), hist[j]->GetStdDev());
//TF1 *g2 = new TF1("g2", "([5])*([0]/sqrt(2*TMath::Pi())*[2])*exp(-pow((x-[1]),2)/2*[2]*[2])+(1-[5])*([3]/sqrt(2*TMath::Pi())*[4])*exp(-pow((x-[1]),2)/2*[4]*[4])", hist[0]->GetMean(), hist[0]->GetStdDev());
//hist[j]->Fit("g2", "M");
hist[j]->Draw("SAME hist");
//hist[j]->Draw("PE"); hist[j]->Draw("HIST L SAME");
leg1->AddEntry(hist[j], "With pt_over_mgg cut","f");
}
leg1->Draw("SAME");
tex1->Draw("SAME");
tex2->Draw("SAME");
//c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_NonHiggsBkg.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/DiphoMass_pt_over_mggCutComp.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/DiphoMass_pt_over_mggCutComp.png");
} 


