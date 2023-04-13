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

void MVA_comp(){

gStyle->SetOptStat(0);
TString file_path;
std::vector<TString> file;
file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files/RunII/";
file.push_back("output_Tprime_600.root");
file.push_back("output_Tprime_625.root");
file.push_back("output_Tprime_650.root");
file.push_back("output_Tprime_675.root");
file.push_back("output_Tprime_700.root");
file.push_back("output_Tprime_800.root");
file.push_back("output_Tprime_900.root");
file.push_back("output_Tprime_1000.root");
file.push_back("output_Tprime_1100.root");
file.push_back("output_Tprime_1200.root");
const int file_size = 10;
TH1F* hist_Higgs[file_size];
TH1F* hist_NonHiggs[file_size];
TH1F* hist =new TH1F("MVA_score_HiggsBkg"," ;m_{#gamma#gamma}", 100, -0.4, 0.4);

//TLegend *leg1 = new TLegend(0.2, 0.6, 0.6, 0.87, "");
TLegend *leg1 = new TLegend(0.85, 0.3, 0.95, 0.87, "");
//leg1->SetNColumns(2);

string procs[file_size] = {"Tprime_600","Tprime_625", "Tprime_650", "Tprime_675", "Tprime_700", "Tprime_800", "Tprime_900", "Tprime_1000", "Tprime_1100", "Tprime_1200"};

for(int i=0; i<file.size(); i++)
        {
	TFile *file_ = new TFile(file_path + file.at(i), "READ");
        TTree* tree_ = (TTree*)file_->Get(Form("%s_13TeV_THQLeptonicTag", procs[i].c_str()));
cout<<"process=     "<<procs[i].c_str()<<endl;
	Float_t qdipho_mass, qTprime_mass, qweight, qMVA_HiggsBkg, qMVA_NonHiggsBkg;
        tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
        tree_->SetBranchAddress("Tprime_mass", &qTprime_mass);
        tree_->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA_HiggsBkg);
        tree_->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA_NonHiggsBkg);
        tree_->SetBranchAddress("weight", &qweight);
        tree_->SetBranchStatus("*", 1);
        Int_t nentries=(Int_t)tree_->GetEntries();
        hist_Higgs[i] =new TH1F("MVA_score_HiggsBkg"," ;MVA_score_HiggsBkg", 100, -0.4, 0.4);   
        hist_NonHiggs[i] =new TH1F("MVA_score_NonHiggsBkg"," ;MVA_score_NonHiggsBkg", 100, -0.4, 0.4);

                for(int ievent=0; ievent < 15000; ievent++)
                {
                tree_-> GetEntry( ievent );
		hist_Higgs[i]->Fill(qMVA_HiggsBkg);
		hist_NonHiggs[i]->Fill(qMVA_NonHiggsBkg);
		}
	hist_Higgs[i]->SetLineWidth(2);
        hist_NonHiggs[i]->SetLineWidth(2);
	if(i == 0){
	hist_Higgs[i]->SetLineColor(46);
	hist_NonHiggs[i]->SetLineColor(46);
        hist_Higgs[i]->SetLineStyle(46);
        hist_NonHiggs[i]->SetLineStyle(46);
	}
	else{
        hist_Higgs[i]->SetLineColor(i);
        hist_NonHiggs[i]->SetLineColor(i);
        hist_Higgs[i]->SetLineStyle(i);
        hist_NonHiggs[i]->SetLineStyle(i);
	}
	}

TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);
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

TCanvas *c2 = new TCanvas("c2", "c2", 700, 600);
c2->cd();
hist_Higgs[0]->Draw("hist");
hist_Higgs[0]->SetMaximum(2*(hist_Higgs[0]->GetMaximum()));
for(int j=1; j<file.size(); j++)
{
hist_Higgs[j]->Draw("SAME hist");
//leg1->AddEntry(hist_NonHiggs[j], procs[j].c_str(),"f");
}
leg1->Draw("SAME");


//c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_NonHiggsBkg.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_All_HiggsBkg.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_All_HiggsBkg.png");
} 


