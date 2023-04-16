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


void TMVA_2D_opt(){
        TFile *file_tth = new TFile("../output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", "READ");
	TFile *file_thq = new TFile("../output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8.root", "READ");
	TFile *file_ttgg = TFile::Open("../output_TTGG_0Jets.root");
    	TFile *file_ttgjets = TFile::Open("../output_TTGJets.root");
    	TFile *file_DiPhotonJetsBox = TFile::Open("../output_DiPhotonJetsBox.root");
    	TFile *file_DiPhotonJetsBox2BJets = TFile::Open("../output_DiPhotonJetsBox2BJets.root");
        TTree* tree_tth = (TTree*)file_tth->Get("tagsDumper/trees/tth_125_13TeV_THQLeptonicTag");
	TTree* tree_thq = (TTree*)file_thq->Get("tagsDumper/trees/thq_125_13TeV_THQLeptonicTag");
	TTree *tree_ttgg = (TTree*)file_ttgg->Get("tagsDumper/trees/ttgg_13TeV_THQLeptonicTag");
   	TTree *tree_ttgjets = (TTree*)file_ttgjets->Get("tagsDumper/trees/ttgjets_13TeV_THQLeptonicTag");
   	TTree *tree_DiPhotonJetsBox  = (TTree*)file_DiPhotonJetsBox->Get("tagsDumper/trees/DiPhotonJetsBox_13TeV_THQLeptonicTag");
   	TTree *tree_DiPhotonJetsBox2BJets  = (TTree*)file_DiPhotonJetsBox2BJets->Get("tagsDumper/trees/DiPhotonJetsBox2BJets_13TeV_THQLeptonicTag");
	TFile *output = new TFile("output.root","RECREATE");
	TList *list = new TList;
	list->Add(tree_tth);
   	list->Add(tree_ttgg);
   	list->Add(tree_ttgjets);
   	list->Add(tree_DiPhotonJetsBox);
   	list->Add(tree_DiPhotonJetsBox2BJets);
	
	TTree *tree_bkg = TTree::MergeTrees(list);

        Float_t qweight, qdipho_mass, qMVA1, qMVA2;
	Float_t tweight, tdipho_mass, tMVA1, tMVA2;

	tree_bkg->SetBranchAddress("MVAresult_thq", &tMVA1);
	tree_bkg->SetBranchAddress("MVA_thqVsNonPeakingBkg", &tMVA2);
        tree_bkg->SetBranchAddress("weight", &tweight);
        tree_bkg->SetBranchAddress("dipho_mass", &tdipho_mass);
        tree_bkg->SetBranchStatus("*", 1);

        tree_thq->SetBranchAddress("MVAresult_thq", &qMVA1);
	tree_thq->SetBranchAddress("MVA_thqVsNonPeakingBkg", &qMVA2);
        tree_thq->SetBranchAddress("weight", &qweight);
        tree_thq->SetBranchAddress("dipho_mass", &qdipho_mass);
        tree_thq->SetBranchStatus("*", 1);
        Int_t nentries_thq=(Int_t)tree_thq->GetEntries();
	Int_t nentries_bkg=(Int_t)tree_bkg->GetEntries();

TGraph2D *dt = new TGraph2D();
int N=0;
dt->SetTitle("2D Optimisation; tHqVsttH MVA score; tHqVsNonHiggs MVA score; Signal Significance");
for(float MVA1=-0.5;MVA1<0.51;MVA1=MVA1+0.1){ //loop for tHqVsttH MVA
	for(float MVA2=-0.5;MVA2<0.51;MVA2=MVA2+0.1){ //loop for tHqVsNonHiggs MVA
	N++;
	cout<<"N=    "<<N<<endl;
	float s=0;
	float b=0;
		for(int ievent=0; ievent<nentries_thq; ievent++){ //Signal event loop
		tree_thq->GetEntry( ievent );	
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
cout<<"MVA1= "<<MVA1<<"   MVA2= "<<MVA2<<" s_sig_= "<<s_sig_<<endl;
dt->SetPoint(N,MVA1,MVA2,s_sig_);
        }
}
dt->Draw("SURF3");
}
