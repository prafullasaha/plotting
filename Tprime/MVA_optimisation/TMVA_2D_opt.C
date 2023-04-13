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

double s_sig(float s, float b){
if (s==0  && b==0) return 0;
else
        return (s/sqrt(s+b));
}


int TMVA_2D_opt( int year=2 ){

TFile *file_Tprime_700, *file_tth, *file_thq, *file_VH, *file_ttgg, *file_ttgjets, *file_DiPhotonJetsBox, *file_DiPhotonJetsBox2BJets, *file_gjets, *file_TGJets, *file_TTJets, *file_DYJets, *file_WG, *file_ZG, *file_TTWJets;

float MVA1_cut = 0.;
float MVA2_cut = 0.;
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

else if(year == 2016){
cout<<"Running on 2016 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2016/";
        file_Tprime_700 = new TFile(file_path + "output_Tprime_700.root", "READ");
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
        file_VH = TFile::Open(file_path + "output_vh_125.root");


        MVA1_cut = 0.3;
        MVA2_cut = 0.04;
        lumi=35.9;
}

else if(year==2017){
cout<<"Running on 2017 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2017/";
        file_Tprime_700 = new TFile(file_path + "output_Tprime_700.root", "READ");
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
        file_VH = TFile::Open(file_path + "output_vh_125.root");

        MVA1_cut = 0.3;
        MVA2_cut = 0.04;
        lumi=41.5;

}

else if(year==2018){
cout<<"Running on 2018 samples"<<endl;
        file_path = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/2018/";
        file_Tprime_700 = new TFile(file_path + "output_Tprime_700.root", "READ");
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
        file_VH = TFile::Open(file_path + "output_vh_125.root");

        MVA1_cut = 0.3;
        MVA2_cut = 0.04;
        lumi=59.5;

}
else cout<<"No file exists-------------"<<endl;

        TTree* tree_tth = (TTree*)file_tth->Get("tth_125_13TeV_THQLeptonicTag");
        TTree* tree_thq = (TTree*)file_thq->Get("thq_125_13TeV_THQLeptonicTag");
        TTree* tree_vh = (TTree*)file_VH->Get("vh_125_13TeV_THQLeptonicTag");
        TTree *tree_ttgg = (TTree*)file_ttgg->Get("ttgg_13TeV_THQLeptonicTag");
        TTree *tree_ttgjets = (TTree*)file_ttgjets->Get("ttgjets_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox  = (TTree*)file_DiPhotonJetsBox->Get("DiPhotonJetsBox_13TeV_THQLeptonicTag");
        TTree *tree_DiPhotonJetsBox2BJets  = (TTree*)file_DiPhotonJetsBox2BJets->Get("DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag");
        TTree *tree_gjets  = (TTree*)file_gjets->Get("gjets_13TeV_THQLeptonicTag");
        TTree *tree_ttjets  = (TTree*)file_TTJets->Get("ttjets_13TeV_THQLeptonicTag");
        TTree *tree_tgjets  = (TTree*)file_TGJets->Get("tgjets_13TeV_THQLeptonicTag");
        TTree *tree_ttwjets  = (TTree*)file_TTWJets->Get("ttwjets_13TeV_THQLeptonicTag");
        TTree *tree_WG  = (TTree*)file_WG->Get("WG_13TeV_THQLeptonicTag");
        TTree *tree_ZG  = (TTree*)file_ZG->Get("ZG_13TeV_THQLeptonicTag");
        TTree *tree_DYJets  = (TTree*)file_DYJets->Get("DYJets_13TeV_THQLeptonicTag");
        TTree *tree_Tprime  = (TTree*)file_Tprime_700->Get("Tprime_700_13TeV_THQLeptonicTag");

        TFile *output = new TFile("output.root","RECREATE");
        TList *list1 = new TList;
        list1->Add(tree_ttgg);
        list1->Add(tree_ttgjets);
        list1->Add(tree_DiPhotonJetsBox);
        list1->Add(tree_DiPhotonJetsBox2BJets);
        list1->Add(tree_gjets);
        list1->Add(tree_ttjets);
        list1->Add(tree_tgjets);
        list1->Add(tree_ttwjets);
        list1->Add(tree_WG);
        list1->Add(tree_ZG);
        list1->Add(tree_DYJets);
        list1->Add(tree_tth);
        list1->Add(tree_thq);
        list1->Add(tree_vh);


        TTree *tree_bkg = TTree::MergeTrees(list1);
/*
        TList *list2 = new TList;
        list2->Add(tree_tth);
        list2->Add(tree_thq);
        list2->Add(tree_vh);
*/
        Float_t qweight, qdipho_mass, qMVA1, qMVA2;
	Float_t tweight, tdipho_mass, tMVA1, tMVA2;

	tree_bkg->SetBranchAddress("MVAscore_TprimeVsHiggs", &tMVA1);
	tree_bkg->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &tMVA2);
        tree_bkg->SetBranchAddress("weight", &tweight);
        tree_bkg->SetBranchAddress("dipho_mass", &tdipho_mass);
        tree_bkg->SetBranchStatus("*", 1);

        tree_Tprime->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA1);
	tree_Tprime->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA2);
        tree_Tprime->SetBranchAddress("weight", &qweight);
        tree_Tprime->SetBranchAddress("dipho_mass", &qdipho_mass);
        tree_Tprime->SetBranchStatus("*", 1);
        Int_t nentries_thq=(Int_t)tree_Tprime->GetEntries();
	Int_t nentries_bkg=(Int_t)tree_bkg->GetEntries();

TGraph2D *dt = new TGraph2D();
int N=0;
dt->SetTitle("2D Optimisation; TprimeVsHiggs MVA score; TprimeVsNonHiggs MVA score; Signal Significance");
for(float MVA1=-0.5;MVA1<0.51;MVA1=MVA1+0.005){ //loop for tHqVsttH MVA
	for(float MVA2=-0.5;MVA2<0.51;MVA2=MVA2+0.01){ //loop for tHqVsNonHiggs MVA
	N++;
//	cout<<"N=    "<<N<<endl;
	float s=0;
	float b=0;
		for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
		tree_Tprime->GetEntry( ievent );	
	 	if(qMVA1>MVA1 && qMVA2>MVA2){
	 		s= s+qweight;
			}
	 	}
		for(int ievent=0; ievent<nentries_bkg; ievent++){ //Background event loop
		tree_bkg->GetEntry( ievent );
	 	if(qMVA1>MVA1 && qMVA2>MVA2 ){
	 		b= b+tweight;
		}
	 	}
	double s_sig_=s_sig(s,b);
//cout<<"MVA1= "<<MVA1<<"   MVA2= "<<MVA2<<" s_sig_= "<<s_sig_<<endl;
dt->SetPoint(N,MVA1,MVA2,s_sig_);
		}
}
cout<<"N=    "<<N<<endl;
TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);
c1->cd();
dt->Draw("SURF3");
c1->SaveAs(Form("2D_opt_%i.root", year));
return 0;
}

int main(int argc, char** argv)
{
int year;
return TMVA_2D_opt( year );
}

