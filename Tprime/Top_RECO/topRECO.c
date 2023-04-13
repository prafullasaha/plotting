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
#include "SemiLepTopQuark.h"

void topRECO(TString filename, TString procs){

gStyle->SetOptStat(0);
TFile *file_data;

        file_data = TFile::Open(filename);
        TTree *tree_data  = (TTree*)file_data->Get("tagsDumper/trees/" + procs + "_13TeV_THQLeptonicTag");
        Float_t tweight, tdipho_mass, tTprime_mass, tMVA1, tMVA2, tsolvedMET_pz;
	Float_t qele1_pt, qele1_eta, qele1_phi, qele1_e;
	Float_t qele2_pt, qele2_eta, qele2_phi, qele2_e;
	Float_t qmuon1_pt, qmuon1_eta, qmuon1_phi, qmuon1_e;
	Float_t qmuon2_pt, qmuon2_eta, qmuon2_phi, qmuon2_e;
	Float_t qbjet1_pt, qbjet1_eta, qbjet1_phi, qbjet1_e;	
	Float_t qfwdjet1_pt, qfwdjet1_eta, qfwdjet1_phi, qfwdjet1_e;
	Float_t qrecoMET_pt, qrecoMET_eta, qrecoMET_phi, qrecoMET_e;
	Float_t qlepton_leadPt;

        tree_data->SetBranchAddress("MVAscore_tHqVsttH_BDT", &tMVA1);
        tree_data->SetBranchAddress("MVAscore_thqVsNonHiggsBkg", &tMVA2);

	tree_data->SetBranchAddress("ele1_pt", 	&qele1_pt);
	tree_data->SetBranchAddress("ele1_eta", &qele1_eta);
	tree_data->SetBranchAddress("ele1_phi", &qele1_phi);
	tree_data->SetBranchAddress("ele1_e", 	&qele1_e);

        tree_data->SetBranchAddress("ele2_pt",  &qele2_pt);
        tree_data->SetBranchAddress("ele2_eta", &qele2_eta);
        tree_data->SetBranchAddress("ele2_phi", &qele2_phi);
        tree_data->SetBranchAddress("ele2_e",   &qele2_e);

        tree_data->SetBranchAddress("muon1_pt",  &qmuon1_pt);
        tree_data->SetBranchAddress("muon1_eta", &qmuon1_eta);
        tree_data->SetBranchAddress("muon1_phi", &qmuon1_phi);
        tree_data->SetBranchAddress("muon1_e",   &qmuon1_e);

        tree_data->SetBranchAddress("muon2_pt",  &qmuon2_pt);
        tree_data->SetBranchAddress("muon2_eta", &qmuon2_eta);
        tree_data->SetBranchAddress("muon2_phi", &qmuon2_phi);
        tree_data->SetBranchAddress("muon2_e",   &qmuon2_e);

        tree_data->SetBranchAddress("bjet1_pt",  &qbjet1_pt);
        tree_data->SetBranchAddress("bjet1_eta", &qbjet1_eta);
        tree_data->SetBranchAddress("bjet1_phi", &qbjet1_phi);
        tree_data->SetBranchAddress("bjet1_e",   &qbjet1_e);

        tree_data->SetBranchAddress("fwdjet1_pt",  &qfwdjet1_pt);
        tree_data->SetBranchAddress("fwdjet1_eta", &qfwdjet1_eta);
        tree_data->SetBranchAddress("fwdjet1_phi", &qfwdjet1_phi);
        tree_data->SetBranchAddress("fwdjet1_e",   &qfwdjet1_e);

        tree_data->SetBranchAddress("recoMET_pt",  &qrecoMET_pt);
        tree_data->SetBranchAddress("recoMET_eta", &qrecoMET_eta);
        tree_data->SetBranchAddress("recoMET_phi", &qrecoMET_phi);
        tree_data->SetBranchAddress("recoMET_e",   &qrecoMET_e);

	tree_data->SetBranchAddress("lepton_leadPt", &qlepton_leadPt);

        tree_data->SetBranchAddress("Tprime_mass", &tTprime_mass);
        tree_data->SetBranchAddress("dipho_mass", &tdipho_mass);
        tree_data->SetBranchAddress("solvedMET_pz", &tsolvedMET_pz);
        tree_data->SetBranchAddress("weight", &tweight);
        tree_data->SetBranchStatus("*", 1);

	TLorentzVector metL, bL,fwdJL, lL, metW_check; 

	TH1F* h_solvedMET_pz =new TH1F("h_solvedMET_pz","h_solvedMET_pz",100,-400,400);
	TH1F* h_genMET_pz = new TH1F("h_genMET_pz","h_genMET_pz",100,-400,400);
	TH1F* h_promptGenMET_pz = new TH1F("h_promptGenMET_pz","h_promptGenMET_pz",100,-400,400);
	TH1F* h_mW =new TH1F("h_mW","h_mW",100,60,1000);
	TH1F* h_mW_xCheck =new TH1F("h_mW_xCheck","h_mW_xCheck",100,60,1000);
//	tree_data->Draw("genMET_pz >> h_genMET_pz", "weight*(genMET_pz != 0)", "hist");
//	tree_data->Draw("promptGenMET_pz >> h_promptGenMET_pz", "weight*(promptGenMET_pz != 0)", "hist");

        tree_data->Draw("genMET_pz >> h_genMET_pz", "(genMET_pz != 0)", "hist");
        tree_data->Draw("promptGenMET_pz >> h_promptGenMET_pz","(promptGenMET_pz != 0)", "hist");

        Int_t nentries_data=(Int_t)tree_data->GetEntries();
	int soln_2=0;
	
                for(int ievent=0; ievent<nentries_data; ievent++){ //Signal event loop
                tree_data->GetEntry( ievent );
		metL.SetPtEtaPhiE( qrecoMET_pt, qrecoMET_eta, qrecoMET_phi, qrecoMET_e );
		bL.SetPtEtaPhiE( qbjet1_pt, qbjet1_eta, qbjet1_phi, qbjet1_e );
		fwdJL.SetPtEtaPhiE( qfwdjet1_pt, qfwdjet1_eta, qfwdjet1_phi, qfwdjet1_e );
		if( abs(qlepton_leadPt- qele1_pt) < 0.0001) lL.SetPtEtaPhiE( qele1_pt, qele1_eta, qele1_phi, qele1_e );
		else if ( abs(qlepton_leadPt- qele2_pt) < 0.0001) lL.SetPtEtaPhiE( qele2_pt, qele2_eta, qele2_phi, qele2_e );
		else if ( abs(qlepton_leadPt- qmuon1_pt) < 0.0001) lL.SetPtEtaPhiE( qmuon1_pt, qmuon1_eta, qmuon1_phi, qmuon1_e );
		else if ( abs(qlepton_leadPt- qmuon2_pt) < 0.0001) lL.SetPtEtaPhiE( qmuon2_pt, qmuon2_eta, qmuon2_phi, qmuon2_e );
		else cout<<"There is no lep match with leading lep. pt"<<endl;

//		if(ievent == 72){	
		SemiLepTopQuark singletop(bL, metL, lL, fwdJL,fwdJL);
		double m_w = singletop.W().M();
//		h_mW->Fill(m_w);
//		h_mW_xCheck->Fill(singletop.getW_mass());
//		if(ievent == 72){
		metW_check = singletop.getMET();
		h_solvedMET_pz->Fill(metW_check.Pz());		
		if( singletop.getSoln_Tag()== 2){
		soln_2 ++;
		h_mW->Fill(m_w);
		h_mW_xCheck->Fill(singletop.getW_mass());
//		cout<<"event count  "<<ievent<<endl;
		cout<<"Neutrino Pz= "<<metW_check.Pz()<<endl;
		cout<<"w mass=    "<<m_w<<endl;
		}
//		}
//		cout<<"w mass=    "<<singletop.getW_mass()<<endl;	
                }
cout<<"Total number of 2nd solution	"<<soln_2<<endl;
h_genMET_pz->SetLineWidth(2);
h_solvedMET_pz->SetLineWidth(2);
h_promptGenMET_pz->SetLineWidth(2);

h_genMET_pz->SetLineColor(2);
h_solvedMET_pz->SetLineColor(4);
h_promptGenMET_pz->SetLineColor(6);

h_mW->SetLineWidth(2);
h_mW_xCheck->SetLineWidth(2);

h_mW->SetLineColor(2);
h_mW_xCheck->SetLineColor(4);


cout<<"h_genMET_pz Entries	"<<h_genMET_pz->GetEntries()<<endl;
cout<<"h_solvedMET_pz Entries	"<<h_solvedMET_pz->GetEntries()<<endl;
cout<<"h_promptGenMET_pz Entries"<<h_promptGenMET_pz->GetEntries()<<endl;
cout<<"h_mW Entries		"<<h_mW->GetEntries()<<endl;
cout<<"h_mW_xCheck		"<<h_mW_xCheck->GetEntries()<<endl;
h_genMET_pz->Scale(1/h_genMET_pz->Integral());
h_solvedMET_pz->Scale(1/h_solvedMET_pz->Integral());
h_promptGenMET_pz->Scale(1/h_promptGenMET_pz->Integral());

TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9, "");
leg1->AddEntry(h_genMET_pz, "All nu." ,"f");
leg1->AddEntry(h_solvedMET_pz, "Solved nu." ,"f");
leg1->AddEntry(h_promptGenMET_pz, "Prompt nu." ,"f");

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
c1->cd();
c1->SetTitle("");

h_solvedMET_pz->SetMaximum(4*h_solvedMET_pz->GetMaximum());
h_solvedMET_pz->Draw("hist");
h_genMET_pz->Draw("hist SAME");
h_promptGenMET_pz->Draw("hist SAME");
leg1->Draw("SAME");

TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
c2->cd();
c2->SetTitle("");
//h_mW->Draw("hist");
h_mW_xCheck->Draw("hist");
//h_mW->Draw("SAME hist");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/top_Reco_sol2_mW.png");
}
