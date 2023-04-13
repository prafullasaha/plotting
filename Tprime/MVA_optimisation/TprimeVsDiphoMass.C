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

void TprimeVsDiphoMass(TString filename, TString procs){
gStyle->SetOptStat(0);
	TFile *file_data;
//        file_data = TFile::Open("/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/RunII/output_allData_RunII.root");
//	file_data = TFile::Open("/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/RunII/output_");
	file_data = TFile::Open(filename);
        TTree *tree_data  = (TTree*)file_data->Get("tagsDumper/trees/" + procs + "_13TeV_THQLeptonicTag");
	Float_t tweight, tdipho_mass, tTprime_mass, tMVA1, tMVA2, tsolvedMET_pz;
	tree_data->SetBranchAddress("MVAscore_tHqVsttH_BDT", &tMVA1);
	tree_data->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &tMVA2);
	tree_data->SetBranchAddress("Tprime_mass", &tTprime_mass);
	tree_data->SetBranchAddress("dipho_mass", &tdipho_mass);
	tree_data->SetBranchAddress("solvedMET_pz", &tsolvedMET_pz);
	tree_data->SetBranchAddress("weight", &tweight);
        tree_data->SetBranchStatus("*", 1);
	float MVA1 = 0.;
	float MVA2 = 0.04;
	Int_t nentries_data=(Int_t)tree_data->GetEntries();

TH2F *H_mass = new TH2F("H_mass","RawA vs RawB",100,90,180,100,0.,1200.);
TH2F *PzVsTmass = new TH2F("PzVsTmass","#nu_{p_{z}} vs T_{m}",50,-2000000,2000000,50,0.,200000.);
int N=0;
		for(int ievent=0; ievent<nentries_data; ievent++){ //Signal event loop
		tree_data->GetEntry( ievent );	
//	 	if(tMVA1>MVA1 && tMVA2>MVA2){
		H_mass->Fill(tdipho_mass, tTprime_mass, tweight);
		PzVsTmass->Fill(tsolvedMET_pz, tTprime_mass);
//			}
	 	}
cout<<"N=    "<<N<<endl;
TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);
c1->cd();
//H_mass->Draw("colz");
PzVsTmass->Draw("colz");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/PzVsTmass.pdf");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/PzVsTmass.png");
return 0;
}
