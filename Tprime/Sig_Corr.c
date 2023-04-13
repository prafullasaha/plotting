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

void Sig_Corr(){

gStyle->SetOptStat(0);
gROOT->SetBatch(1);
TString file_path_1;
TString file_path_2;
const int file_size = 17;
std::vector<TString> file;
//file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files/Run2/";
//file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files_Tprime600_700VsHiggs/Run2/";
//file_path = "/eos/user/p/prsaha/for_Maxime/output_files_Tprime800_1000VsHiggs_BDTG/Run2/";
file_path_1 = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/UL/output_files_Tprime600_700VsHiggs_BDTG_UL/Run2/";
file_path_2 = "/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/UL/output_files_Tprime1100_1200VsHiggs_BDTG_UL/Run2/";

/*file.push_back("output_Tprime_600.root");
file.push_back("output_Tprime_625.root");
file.push_back("output_Tprime_650.root");
file.push_back("output_Tprime_675.root");
file.push_back("output_Tprime_700.root");
file.push_back("output_Tprime_800.root");
file.push_back("output_Tprime_900.root");
file.push_back("output_Tprime_1000.root");
file.push_back("output_Tprime_1100.root");
file.push_back("output_Tprime_1200.root");


file.push_back("output_tth_125.root");
file.push_back("output_thq_125.root");
file.push_back("output_vh_125.root");
file.push_back("output_vbf_125.root");
file.push_back("output_ggh_125.root");
*/
file.push_back("output_ttgg.root");
file.push_back("output_ttgjets.root");
file.push_back("output_DiPhotonJetsBox.root");
//file.push_back("output_DiPhotonJetsBox2BJets.root");
file.push_back("output_gjets.root");
file.push_back("output_ttjets.root");
file.push_back("output_tgjets.root");
file.push_back("output_ttwjets.root");
file.push_back("output_ZG.root");
file.push_back("output_WG.root");
file.push_back("output_DYJets.root");
file.push_back("output_Data.root");
//string procs[file_size] = {"Tprime_600","Tprime_625","Tprime_650","Tprime_675","Tprime_700","Tprime_800","Tprime_900","Tprime_1000","Tprime_1100","Tprime_1200","tth_125","thq_125","vh_125","vbf_125","ggh_125","ttgg", "ttgjets","DiPhotonJetsBox","gjets","ttjets","tgjets","ttwjets","ZG","WG","DYJets","Data"};
//string procs_[file_size] = {"T'(600)","T'(625)","T'(625)","T'(675)","T'(700)","T'(800)","T'(900)","T'(1000)","T'(1100)","T'(1200)","$t\\bar{t}H$","tHq","VH","VBF","GGH","$t\\bar{t}+\\gamma\\gamma$", "$t\\bar{t}\\gamma + jets$","$\\gamma\\gamma + jets$","$\\gamma + jets$","$t\\bar{t} + jets$","$t\\gamma+jets$","TTW","$Z + \\gamma$","$W + \\gamma$","Drell-Yan","Data"};

string procs[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox","gjets","ttjets","tgjets","ttwjets","ZG","WG","DYJets","Data"};
string procs_[file_size] = {"$t\\bar{t}+\\gamma\\gamma$", "$t\\bar{t}\\gamma + jets$","$\\gamma\\gamma + jets$","$\\gamma + jets$","$t\\bar{t} + jets$","$t\\gamma+jets$","TTW","$Z + \\gamma$","$W + \\gamma$","Drell-Yan","Data"};



float xsbr[] = {
0.1764, 0.1489, 0.1213, 0.1050, 0.0886, 0.0459, 0.0251, 0.0145, 0.00867, 0.00536,
1,1,1,1,1,
1,1,1,1,1,
1,1,1,1,1,
1};

TGraph *yield_graph[file_size];

TMultiGraph *mg = new TMultiGraph();

TLegend *leg1 = new TLegend(0.85, 0.2, 0.95, 0.87, "");
//leg1->SetNColumns(4);


for(int i=0; i<file.size(); i++)
    {
	TFile *file_1 = new TFile(file_path_1 + file.at(i), "READ");
	TFile *file_2 = new TFile(file_path_2 + file.at(i), "READ");
    TTree* tree_1 = (TTree*)file_1->Get(Form("%s_13TeV_THQLeptonicTag", procs[i].c_str()));
	TTree* tree_2 = (TTree*)file_2->Get(Form("%s_13TeV_THQLeptonicTag", procs[i].c_str()));
//cout<<"process=     "<<procs[i].c_str()<<endl;
	Float_t qdipho_mass_1, qTprime_mass_1, qweight_1, qMVA_HiggsBkg_1, qMVA_NonHiggsBkg_1;
	Float_t qdipho_mass_2, qTprime_mass_2, qweight_2, qMVA_HiggsBkg_2, qMVA_NonHiggsBkg_2;
	ULong64_t qevent_1, qevent_2;

    tree_1->SetBranchAddress("dipho_mass", &qdipho_mass_1);
    tree_1->SetBranchAddress("Tprime_mass", &qTprime_mass_1);
    tree_1->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA_HiggsBkg_1);
    tree_1->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA_NonHiggsBkg_1);
    tree_1->SetBranchAddress("weight", &qweight_1);
	tree_1->SetBranchAddress("event", &qevent_1);
    tree_1->SetBranchStatus("*", 1);
	Int_t nentries_1 = (Int_t)tree_1->GetEntries();

    tree_2->SetBranchAddress("dipho_mass", &qdipho_mass_2);
    tree_2->SetBranchAddress("Tprime_mass", &qTprime_mass_2);
    tree_2->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA_HiggsBkg_2);
    tree_2->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA_NonHiggsBkg_2);
    tree_2->SetBranchAddress("weight", &qweight_2);
    tree_2->SetBranchAddress("event", &qevent_2);
    tree_2->SetBranchStatus("*", 1);
    Int_t nentries_2 = (Int_t)tree_2->GetEntries();

	yield_graph[i] =new TGraph();
	int N=0;
	double MVA1=0.0;
//    for(double MVA1=0.4;MVA1<=0.6;MVA1=MVA1+0.002){
	N++;
    float s=0;
	float sumW2=0;
	float nEvent=0;
    	for(int ievent=0; ievent < nentries_1; ievent++)
        	{
            tree_1-> GetEntry( ievent );
			if(qMVA_HiggsBkg_1 > 0.6 && qMVA_HiggsBkg_1 < 2 && (qTprime_mass_1 > 480 && qTprime_mass_1 < 800) && (qdipho_mass_1 > 115 && qdipho_mass_1 < 135) /* && (qdipho_mass_1 < 115 || qdipho_mass_1 > 135)*/)
				{

			//----------------------------------------------------------------------------------------------------------------------
		        for(int ievent=0; ievent < nentries_2; ievent++)
        	    {
            	tree_2-> GetEntry( ievent );
            	if(qMVA_HiggsBkg_2 > 0.4 && qMVA_HiggsBkg_2 < 2 && (qTprime_mass_2 > 650 && qTprime_mass_2 < 1150 ) && (qdipho_mass_2 > 115 && qdipho_mass_2 < 135)/* && (qdipho_mass_2 < 115 || qdipho_mass_2 > 135)*/)
                	{
					if(qevent_1 == qevent_2/*&& qweight_1 == qweight_2*/){
//					cout<<"qdipho_mass_1\t="<<qdipho_mass_1 <<"qdipho_mass_2\t="<<qdipho_mass_2<<endl;
                	s= s+(qweight_1);
                	sumW2 = sumW2 + (qweight_1*qweight_1);
                	nEvent++;
					}
               		}

            	}
			//----------------------------------------------------------------------------------------------------------------------
			
            	}

			}

//cout<<procs_[i].c_str()<<" 		& $"<<Form("%0.2f",s)<<"$ \\\\"<<endl;//<<"    "<<s/1892.391<<endl;
//cout<<procs_[i].c_str()<<"        & $"<<Form("%0.2f",s)<<"$ \\\\"<<"    "<<s/(137*xsbr[i]*1000*0.00227)<<endl;
//cout<<Form("%s\t\t",procs_[i].c_str())<<nEvent<<"\tSumW\t"<<Form("%0.2f",s)<<"\t"<<sqrt(sumW2)<<endl;
cout<<Form("%s \t %0.0f\t\t",procs_[i].c_str(),nEvent)<<"\t"<<Form("%0.2f \\pm %0.3f", s, sqrt(sumW2))<<"\t"<<endl;

	yield_graph[i]->SetPoint(N-1, MVA1, s);
//	}
	leg1->AddEntry(yield_graph[i], procs_[i].c_str(),"l");
	if(i==0){
		yield_graph[i]->SetLineColor(41);
        yield_graph[i]->SetMarkerColor(41);
	}
	else if( i==10 ){
        yield_graph[i]->SetLineColor(49);
        yield_graph[i]->SetMarkerColor(49);

	}
	else{
	yield_graph[i]->SetLineColor(i);
	yield_graph[i]->SetMarkerColor(i);
	}
	yield_graph[i]->SetLineWidth(2);
	yield_graph[i]->SetMarkerStyle(20);
	mg->Add(yield_graph[i]);	
	}

//mg->GetXaxis()->SetTitle("Higgs-MVA");
//mg->GetYaxis()->SetTitle("Total Yield");
TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);

TCanvas *c2 = new TCanvas("c2", "c2", 700, 600);
c2->cd();
c2->SetGridy();
c2->SetGridx();
//c2->SetLogy();
mg->Draw("APL");
mg->GetXaxis()->SetTitle("Higgs-MVA");
mg->GetYaxis()->SetTitle("Total Yield");
leg1->Draw("SAME");


//c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_NonHiggsBkg.pdf");
//c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/YieldHiggsBkg_frac_TmassGT375_HiggsBkgTng.pdf");
//c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/YieldHiggsBkg_frac_TmassGT375_HiggsBkgTng.png");
} 


