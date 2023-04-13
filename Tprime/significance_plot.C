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

void significance_plot(){

gStyle->SetOptStat(0);
gROOT->SetBatch(1);
TString file_path;
const int file_size = 10;
std::vector<TString> file;
int training_file=3;
string training[]={"600_700", "800_1000", "1100_1200"};
double mass[]={600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200};
TGraph *yield_graph[training_file];
//file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files/Run2/";
//file_path = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files_Tprime600_700VsHiggs/Run2/";
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
file.push_back("output_allData.root");
string procs[file_size] = {"Tprime_600","Tprime_625","Tprime_650","Tprime_675","Tprime_700","Tprime_800","Tprime_900","Tprime_1000","Tprime_1100","Tprime_1200","Data"};
string procs_[file_size] = {"T'(600)","T'(625)","T'(650)","T'(675)","T'(700)","T'(800)","T'(900)","T'(1000)","T'(1100)","T'(1200)"};

float xsbr[] = {0.1764, 0.1489, 0.1213, 0.1050, 0.0886, 0.0459, 0.0251, 0.0145, 0.00867, 0.00536};

TMultiGraph *mg = new TMultiGraph();

TLegend *leg1 = new TLegend(0.2, 0.7, 0.4, 0.9, "");
//leg1->SetNColumns(4);
for(int j=0; j<training_file; j++){
file_path = Form("/eos/user/p/prsaha/for_Maxime/output_files_Tprime%sVsHiggs_BDTG/Run2/", training[j].c_str());
cout<<"training[j]= "<<training[j]<<endl;
double abs_eff[10];
 for(int i=0; i<file.size(); i++)
    {
	TFile *file_ = new TFile(file_path + file.at(i), "READ");
    TTree* tree_ = (TTree*)file_->Get(Form("%s_13TeV_THQLeptonicTag", procs[i].c_str()));
//cout<<"process=     "<<procs[i].c_str()<<"   "<<xsbr[i]<<endl;
	Float_t qdipho_mass, qTprime_mass, qweight, qMVA_HiggsBkg, qMVA_NonHiggsBkg;
    tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
    tree_->SetBranchAddress("Tprime_mass", &qTprime_mass);
    tree_->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA_HiggsBkg);
    tree_->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA_NonHiggsBkg);
    tree_->SetBranchAddress("weight", &qweight);
    tree_->SetBranchStatus("*", 1);
	Int_t nentries=(Int_t)tree_->GetEntries();
    float s=0;
	bool cut=false;
    	for(int ievent=0; ievent < nentries; ievent++)
        	{
            tree_-> GetEntry( ievent );
    		if(training[j]  == "600_700" ){
        		cut = ((qTprime_mass>480 && qTprime_mass<800) && qMVA_HiggsBkg> 0.63);
        	}
    		else if(training[j]  == "800_1000"){
        		cut = ((qTprime_mass>550 && qTprime_mass<1150) && qMVA_HiggsBkg> 0.4);
        	}
    		else if(training[j]  == "1100_1200"){
        		cut = ((qTprime_mass>650 && qTprime_mass<1600) && qMVA_HiggsBkg> 0.4);
        	}

//			s= s+(qweight);
			if(cut==1 /*&& (qdipho_mass > 115 && qdipho_mass < 135)*//*&& (qdipho_mass < 115 || qdipho_mass > 135)*/)
				{
            	s= s+(qweight);
            	}
            cut=0;
			}
//cout<<"Signal = "<<s<<endl;
//cout<<procs_[i].c_str()<<" 		& $"<<Form("%0.2f",s)<<"$ \\\\"<<endl;//<<"    "<<s/1892.391<<endl;
		abs_eff[i]= s/(137*xsbr[i]);
//cout<<procs_[i].c_str()<<"        & $"<<Form("%0.2f",s)<<"$ \\\\"<<"    "<<s/(137*xsbr[i])<<endl;
cout<<procs_[i].c_str()<<"        "<<Form("%0.3f",s)<<"    "<<Form("%0.3f",(s/(137*xsbr[i])))<<endl;
//cout<<i<<"        "<<mass[i]<<"       "<<abs_eff[i]<<endl;
//	yield_graph[j]->SetPoint(i, mass_ , abs_eff);
	}
	yield_graph[j] = new TGraph(10, mass, abs_eff);
    leg1->AddEntry(yield_graph[j], training[j].c_str(),"l");
    yield_graph[j]->SetLineColor(2+j);
    yield_graph[j]->SetMarkerColor(2+j);
    yield_graph[j]->SetLineWidth(2);
    yield_graph[j]->SetMarkerStyle(20);
    mg->Add(yield_graph[j]);
	}//loop for training file

//mg->GetXaxis()->SetTitle("Higgs-MVA");
//mg->GetYaxis()->SetTitle("Total Yield");
TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);

TCanvas *c2 = new TCanvas("c2", "c2", 700, 500);
c2->cd();
c2->SetGridy();
c2->SetGridx();
//c2->SetLogy();
mg->Draw("APL");
mg->SetMaximum(0.5);
mg->GetXaxis()->SetTitle("T^{'} mass (GeV)");
mg->GetYaxis()->SetTitle("Efficiency.");
leg1->Draw("SAME");


//c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/MVA_Tprime_comp_NonHiggsBkg.pdf");
//c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/YieldHiggsBkg_frac_TmassGT375_HiggsBkgTng.pdf");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Eff_AfterOpt_test.png");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/Eff_AfterOpt_test.pdf");
} 


