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
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "MVAnalysis.h"

using namespace std;

float Mtilde(float T_mass, float t_mass, float mh){
return (T_mass - t_mass + 175.5 - mh + 125);
}

int MVA_score(){

InputVariables varList;

int file_size=1;
std::vector<TString> file;
TString file_path;
int year=2;

std::string mvAlgo_ {"BDTG"};
std::string xmlfile_TprimeVsNonHiggs;
std::string xmlfile_TprimeVsHiggs;

if(year==2016){
file_path = "/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/UL/v2/2016/";
file.push_back("output_TTGG_0Jets_pythia8.root");
file.push_back("output_TTGJets_pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_pythia8.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_pythia8.root");
file.push_back("output_WW_pythia8.root");
file.push_back("output_WZ_pythia8.root");
file.push_back("output_ZZ_pythia8.root");
file.push_back("output_TTWJetsToLNu_pythia8.root");
file.push_back("ZGToLLG_pythia8.root");
file.push_back("output_DYJetsToLL_M-50_pythia8.root");
file.push_back("output_WGToLNuG_pythia8.root");
file.push_back("output__TGJets__pythia8.root");
file.push_back("output_TTJets_pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_pythia8.root");
file.push_back("output_ttHJetToGG_M125_pythia8.root");
file.push_back("output_VHToGG_M125_pythia8.root");
file.push_back("output_VBFHToGG_M125_pythia8.root");
file.push_back("output_GluGluHToGG_M125_pythia8.root");
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
file.push_back("output_DoubleEG_Run2016.root");

file_size = file.size();
xmlfile_TprimeVsNonHiggs = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_TprimeAllVsHiggs/weights/TMVAClassification_BDT.weights.xml";
xmlfile_TprimeVsHiggs ="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_Tprime600_700VsHiggs/weights/TMVAClassification_BDT.weights.xml";
}

if(year==2017){
file_path = "/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/UL/v2/2017/";
file.push_back("output_TTGG_0Jets_pythia8.root");
file.push_back("output_TTGJets_pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_pythia8.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_pythia8.root");
file.push_back("output_WW_pythia8.root");
file.push_back("output_WZ_pythia8.root");
file.push_back("output_ZZ_pythia8.root");
file.push_back("output_TTWJetsToLNu_pythia8.root");
file.push_back("ZGToLLG_pythia8.root");
file.push_back("output_DYJetsToLL_M-50_pythia8.root");
file.push_back("output_WGToLNuG_pythia8.root");
file.push_back("output__TGJets__pythia8.root");
file.push_back("output_TTJets_pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_pythia8.root");
file.push_back("output_ttHJetToGG_M125_pythia8.root");
file.push_back("output_VHToGG_M125_pythia8.root");
file.push_back("output_VBFHToGG_M125_pythia8.root");
file.push_back("output_GluGluHToGG_M125_pythia8.root");
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
file.push_back("output_DoubleEG_Run2017.root");

file_size = file.size();
xmlfile_TprimeVsNonHiggs = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_TprimeAllVsHiggs/weights/TMVAClassification_BDT.weights.xml";
xmlfile_TprimeVsHiggs ="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_Tprime600_700VsHiggs/weights/TMVAClassification_BDT.weights.xml";
}

if(year==2018){
file_path = "/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/UL/v2/2018/";
file.push_back("output_TTGG_0Jets_pythia8.root");
file.push_back("output_TTGJets_pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_pythia8.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_pythia8.root");
file.push_back("output_WW_pythia8.root");
file.push_back("output_WZ_pythia8.root");
file.push_back("output_ZZ_pythia8.root");
file.push_back("output_TTWJetsToLNu_pythia8.root");
file.push_back("ZGToLLG_pythia8.root");
file.push_back("output_DYJetsToLL_M-50_pythia8.root");
file.push_back("output_WGToLNuG_pythia8.root");
file.push_back("output__TGJets__pythia8.root");
file.push_back("output_TTJets_pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_pythia8.root");
file.push_back("output_ttHJetToGG_M125_pythia8.root");
file.push_back("output_VHToGG_M125_pythia8.root");
file.push_back("output_VBFHToGG_M125_pythia8.root");
file.push_back("output_GluGluHToGG_M125_pythia8.root");
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
file.push_back("output_EGamma_Run2018.root");

file_size = file.size();
xmlfile_TprimeVsNonHiggs = "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_TprimeAllVsHiggs/weights/TMVAClassification_BDT.weights.xml";
xmlfile_TprimeVsHiggs ="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_Tprime600_700VsHiggs/weights/TMVAClassification_BDT.weights.xml";
}

if(year==2){
file_path = "/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/UL/v2/RunII/";
//file_path = "/eos/user/p/prsaha/Tprime_analysis/nTuples/output_data_16/";
//file_path = "/afs/cern.ch/work/p/prsaha/public/Tprime_analysis/flashgg_legacy_runII_v4/CMSSW_10_6_8/src/flashgg/";
//file.push_back("output_numEvent10000.root");
file.push_back("output_TTGG_0Jets_pythia8.root");
file.push_back("output_TTGJets_pythia8.root");
file.push_back("output_DiPhotonJetsBox_MGG-80toInf_pythia8.root");
file.push_back("output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_pythia8.root");
file.push_back("output_WW_pythia8.root");
file.push_back("output_WZ_pythia8.root");
file.push_back("output_TTWJetsToLNu_pythia8.root");
file.push_back("output_ZGToLLG_pythia8.root");
file.push_back("output_DYJetsToLL_M-50_pythia8.root");
file.push_back("output_WGToLNuG_pythia8.root");
file.push_back("output__TGJets_pythia8.root");
file.push_back("output_TTJets_pythia8.root");
file.push_back("output_THQ_ctcvcp_HToGG_M125_pythia8.root");
file.push_back("output_ttHJetToGG_M125_pythia8.root");
file.push_back("output_VHToGG_M125_pythia8.root");
file.push_back("output_VBFHToGG_M125_pythia8.root");
file.push_back("output_GluGluHToGG_M125_pythia8.root");
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
file.push_back("output_allData_RunII.root");

file_size = file.size();
//xmlfile_TprimeVsNonHiggs    ="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_Tprime1100_1200VsHiggs_UL/weights/TMVAClassification_BDTG.weights.xml";
//xmlfile_TprimeVsHiggs       ="/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2_Tprime1100_1200VsHiggs_UL/weights/TMVAClassification_BDTG.weights.xml";
xmlfile_TprimeVsNonHiggs    ="/afs/cern.ch/work/p/prsaha/public/Tprime_analysis/flashgg_legacy_runII_UL_v1/CMSSW_10_6_8/src/flashgg/Taggers/data/Tprime_search_training/UL/THQLeptonicTag_TprimeM600_M700Vs_HiggsBkg_BDTG_RunII.weights.xml";
xmlfile_TprimeVsHiggs		="/afs/cern.ch/work/p/prsaha/public/Tprime_analysis/flashgg_legacy_runII_UL_v1/CMSSW_10_6_8/src/flashgg/Taggers/data/Tprime_search_training/UL/THQLeptonicTag_TprimeM600_M700Vs_HiggsBkg_BDTG_RunII.weights.xml";
}

string procs[file_size] 	= {"ttgg", "ttgjets","DiPhotonJetsBox","gjets","WW","WZ","ttwjets","ZG","DYJets","WG","tgjets","ttjets","thq_125","tth_125","vh_125","vbf_125","ggh_125","TprimeM600_125","TprimeM625_125","TprimeM650_125","TprimeM675_125","TprimeM700_125","TprimeM800_125","TprimeM900_125","TprimeM1000_125","TprimeM1100_125","TprimeM1200_125","Data"};
//string procs_outTree[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox","gjets","WW","WZ","ttwjets","ZG","DYJets","WG","tgjets","ttjets","thq_125","tth_125","vh_125","vbf_125","ggh_125","TprimeM600_125","TprimeM625_125","TprimeM650_125","TprimeM675_125","TprimeM700_125","TprimeM800_125","TprimeM900_125","TprimeM1000_125","TprimeM1100_125","TprimeM1200_125","Data"};

string procs_outTree[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox","gjets","WW","WZ","ttwjets","ZG","DYJets","WG","tgjets","ttjets","thq_125","tth_125","vh_125","vbf_125","ggh_125","Tprime_600","Tprime_625","Tprime_650","Tprime_675","Tprime_700","Tprime_800","Tprime_900","Tprime_1000","Tprime_1100","Tprime_1200","Data"};

string procs_outFileName[file_size] = {"ttgg", "ttgjets","DiPhotonJetsBox","gjets","WW","WZ","ttwjets","ZG","DYJets","WG","tgjets","ttjets","thq_125","tth_125","vh_125","vbf_125","ggh_125","Tprime_600","Tprime_625","Tprime_650","Tprime_675","Tprime_700","Tprime_800","Tprime_900","Tprime_1000","Tprime_1100","Tprime_1200","Data"};
ofstream myfile;
myfile.open ("Yield.txt");

if (myfile.is_open()) myfile << "Sample\t\t"<<"Yield Before Cut\t"<<"Yield After Cut\t"<<"Fraction\t"<<endl;
for(int i=0; i<file.size(); i++)
	{
        TFile *file_ = new TFile(file_path + file.at(i), "READ");
        TTree* tree_ = (TTree*)file_->Get(Form("tagsDumper/trees/%s_13TeV_THQLeptonicTag", procs[i].c_str()));
	Float_t qdipho_mass, qweight; 
//output file----------------------------------------------------------------------------------------
	TFile *file_output = TFile::Open(Form("output_files/Run%i/output_%s.root",year, procs_outFileName[i].c_str()), "RECREATE");
  	TTree *t1 = new TTree(Form("%s_13TeV_THQLeptonicTag", procs_outTree[i].c_str()), Form("%s_13TeV_THQLeptonicTag", procs_outTree[i].c_str()));
//---------------------------------------------------------------------------------------------------
cout<<"Running  "<< procs[i].c_str() <<endl; 

	float qdipho_leadPt;
	float qdipho_subleadPt;
	float qdipho_leadEta;
    float qdipho_subleadEta;
    float qdipho_leadIDMVA;
    float qdipho_subleadIDMVA;
    float qdipho_lead_haspixelseed;
    float qdipho_sublead_haspixelseed;
    float qn_jets;
    float qn_bjets;
    float qn_centraljets;
    float qlepton_ch;
    float qlepton_leadPt;
    float qlepton_leadEta;
    float qfwdJet1_pt;
    float qfwdJet1_eta;
    float qfwdJet1_discr;
    float qtop_mt11;
    float qdRtHchainfwdjet;
    float qdRleptonbjet;
    float qdRleptonfwdjet;
    float qdRbjetfwdjet;
    float qdRleadphofwdjet;
    float qdRsubleadphofwdjet;
    float qbjet1_pt;
    float qbjet2_pt;
    float qbjet3_pt;
    float qbjet1_eta;
    float qbjet2_eta;
    float qbjet3_eta;
    float qbjet1_discr;
    float qbjet2_discr;
    float qbjet3_discr;
    float qjet1_pt;
    float qjet2_pt;
    float qjet3_pt;
    float qjet1_eta;
    float qjet2_eta;
    float qjet3_eta;
    float qjet1_discr;
    float qjet2_discr;
    float qjet3_discr;
	float qXtt0;
	float qtop_mass;
	float qTprime_mass;
	float qTprime_mt;
	float qHT;
	float qrecoMET_pt;
	float qsolvedMET_pt;
	float qdipho_pt;
	float qMVAscore_tHqVsttH_BDT;
	ULong64_t qevent;
	UInt_t qrun, qlumi;
    tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
    tree_->SetBranchAddress("dipho_leadPt", &qdipho_leadPt);
    tree_->SetBranchAddress("dipho_subleadPt", &qdipho_subleadPt);
    tree_->SetBranchAddress("dipho_leadEta", &qdipho_leadEta);
    tree_->SetBranchAddress("dipho_subleadEta", &qdipho_subleadEta);
    tree_->SetBranchAddress("dipho_leadIDMVA", &qdipho_leadIDMVA);
    tree_->SetBranchAddress("dipho_subleadIDMVA", &qdipho_subleadIDMVA);
    tree_->SetBranchAddress("dipho_lead_haspixelseed", &qdipho_lead_haspixelseed);
    tree_->SetBranchAddress("dipho_sublead_haspixelseed", &qdipho_sublead_haspixelseed);
    tree_->SetBranchAddress("n_jets", &qn_jets);
    tree_->SetBranchAddress("n_bjets", &qn_bjets);
    tree_->SetBranchAddress("n_centraljets", &qn_centraljets);
    tree_->SetBranchAddress("lepton_charge", &qlepton_ch);
    tree_->SetBranchAddress("lepton_leadPt", &qlepton_leadPt);
    tree_->SetBranchAddress("lepton_leadEta", &qlepton_leadEta);
    tree_->SetBranchAddress("fwdjet1_pt", &qfwdJet1_pt);
    tree_->SetBranchAddress("fwdjet1_eta", &qfwdJet1_eta);
    tree_->SetBranchAddress("fwdjet1_discr", &qfwdJet1_discr);
    tree_->SetBranchAddress("top_mt", &qtop_mt11);
    tree_->SetBranchAddress("dr_tHchainfwdjet", &qdRtHchainfwdjet);
    tree_->SetBranchAddress("dr_leptonbjet", &qdRleptonbjet);
    tree_->SetBranchAddress("dr_leptonfwdjet", &qdRleptonfwdjet);
    tree_->SetBranchAddress("dr_bjetfwdjet", &qdRbjetfwdjet);
    tree_->SetBranchAddress("dr_leadphofwdjet", &qdRleadphofwdjet);
    tree_->SetBranchAddress("dr_subleadphofwdjet", &qdRsubleadphofwdjet);
    tree_->SetBranchAddress("bjet1_pt", &qbjet1_pt);
    tree_->SetBranchAddress("bjet2_pt", &qbjet2_pt);
	tree_->SetBranchAddress("bjet3_pt", &qbjet3_pt);
	tree_->SetBranchAddress("bjet1_eta", &qbjet1_eta);
	tree_->SetBranchAddress("bjet2_eta", &qbjet2_eta);
    tree_->SetBranchAddress("bjet3_eta", &qbjet3_eta);
    tree_->SetBranchAddress("bjet1_discr", &qbjet1_discr);
    tree_->SetBranchAddress("bjet2_discr", &qbjet2_discr);
    tree_->SetBranchAddress("bjet3_discr", &qbjet3_discr);
    tree_->SetBranchAddress("jet1_pt", &qjet1_pt);
    tree_->SetBranchAddress("jet2_pt", &qjet2_pt);
    tree_->SetBranchAddress("jet3_pt", &qjet3_pt);
    tree_->SetBranchAddress("jet1_eta", &qjet1_eta);
    tree_->SetBranchAddress("jet2_eta", &qjet2_eta);
    tree_->SetBranchAddress("jet3_eta", &qjet3_eta);
    tree_->SetBranchAddress("jet1_discr", &qjet1_discr);
    tree_->SetBranchAddress("jet2_discr", &qjet2_discr);
    tree_->SetBranchAddress("jet3_discr", &qjet3_discr);
	tree_->SetBranchAddress("Xtt0", &qXtt0);
	tree_->SetBranchAddress("top_mass", &qtop_mass);
	tree_->SetBranchAddress("Tprime_mass", &qTprime_mass);
	tree_->SetBranchAddress("Tprime_mt", &qTprime_mt);

    tree_->SetBranchAddress("weight", &qweight);
    tree_->SetBranchAddress("n_jets", &qn_jets);
	tree_->SetBranchAddress("HT", &qHT);
	tree_->SetBranchAddress("recoMET_pt", &qrecoMET_pt);
	tree_->SetBranchAddress("solvedMET_pt", &qsolvedMET_pt);
	tree_->SetBranchAddress("dipho_pt", &qdipho_pt);
//  tree_->SetBranchAddress("n_M_bjets", &qn_M_bjets);
	tree_->SetBranchAddress("MVAscore_tHqVsttH_BDT", &qMVAscore_tHqVsttH_BDT);
	tree_->SetBranchAddress("event", &qevent);
    tree_->SetBranchAddress("run", &qrun);
	tree_->SetBranchAddress("lumi", &qlumi);
    tree_->SetBranchStatus("*", 1);
    Int_t nentries=(Int_t)tree_->GetEntries();	


   	std::unique_ptr<MVAnalysis> mvAna_NonHiggs {nullptr};
	std::unique_ptr<MVAnalysis> mvAna_Higgs {nullptr};

	mvAna_NonHiggs   = std::unique_ptr<MVAnalysis>(new MVAnalysis(mvAlgo_, xmlfile_TprimeVsNonHiggs));
	mvAna_Higgs   = std::unique_ptr<MVAnalysis>(new MVAnalysis(mvAlgo_, xmlfile_TprimeVsHiggs));
	float MVAscore_TprimeVsNonHiggs=-999;
    float MVAscore_TprimeVsHiggs=-999;
	float Mtilde_=-999;
	t1->Branch("event", &qevent);
	t1->Branch("lumi", &qlumi);
	t1->Branch("run", &qrun);
	t1->Branch("MVAscore_TprimeVsNonHiggs", &MVAscore_TprimeVsNonHiggs);
	t1->Branch("MVAscore_TprimeVsHiggs", &MVAscore_TprimeVsHiggs);
	t1->Branch("weight", &qweight);
	t1->Branch("dipho_mass", &qdipho_mass);
	t1->Branch("Tprime_mass", &qTprime_mass);
	t1->Branch("lepton_leadPt", &qlepton_leadPt);
	t1->Branch("T_Mtilde",&Mtilde_);

	float Yield_BCut=0;
    float Yield_ACut=0;

        for(int ievent=0; ievent < nentries; ievent++)
        {
        tree_->GetEntry( ievent );
//cout<<"Xtt0==============   "<<qXtt0<<endl;
		varList.dipho_leadPtOvermass_ = qdipho_leadPt/qdipho_mass;
        varList.dipho_subleadPtOvermass_ = qdipho_subleadPt/qdipho_mass;
        varList.dipho_leadEta_ = qdipho_leadEta;
        varList.dipho_subleadEta_= qdipho_subleadEta;
        varList.dipho_leadIDMVA_= qdipho_leadIDMVA;
        varList.dipho_subleadIDMVA_= qdipho_subleadIDMVA;
        varList.dipho_lead_haspixelseed_= qdipho_lead_haspixelseed;
        varList.dipho_sublead_haspixelseed_= qdipho_sublead_haspixelseed;
        varList.n_jets_= qn_jets;
        varList.n_bjets_= qn_bjets;
        varList.n_centraljets_= qn_centraljets;
        varList.lepton_ch_= qlepton_ch;
        varList.lepton_leadPt_= qlepton_leadPt;
        varList.lepton_leadEta_= qlepton_leadEta;
        varList.fwdJet1_pt_= qfwdJet1_pt;
//        varList.fwdJet1_eta_= qfwdJet1_eta;
        varList.fwdJet1_discr_= qfwdJet1_discr;
//        varList.top_mt11_= qtop_mt11;
        varList.dRtHchainfwdjet_= qdRtHchainfwdjet;
        varList.dRleptonbjet_= qdRleptonbjet;
        varList.dRleptonfwdjet_= qdRleptonfwdjet;
        varList.dRbjetfwdjet_= qdRbjetfwdjet;
        varList.dRleadphofwdjet_= qdRleadphofwdjet;
        varList.dRsubleadphofwdjet_= qdRsubleadphofwdjet;
        varList.bjet1_pt_= qbjet1_pt;
//        varList.bjet2_pt_= qbjet2_pt;
//        varList.bjet3_pt_= qbjet3_pt;
        varList.bjet1_eta_= qbjet1_eta;
//        varList.bjet2_eta_= qbjet2_eta;
//        varList.bjet3_eta_= qbjet3_eta;
        varList.bjet1_discr_= qbjet1_discr;
//        varList.bjet2_discr_= qbjet2_discr;
//        varList.bjet3_discr_= qbjet3_discr;
        varList.jet1_pt_= qjet1_pt;
        varList.jet2_pt_= qjet2_pt;
//        varList.jet3_pt_= qjet3_pt;
        varList.jet1_eta_= qjet1_eta;
        varList.jet2_eta_= qjet2_eta;
//        varList.jet3_eta_= qjet3_eta;
        varList.jet1_discr_= qjet1_discr;
        varList.jet2_discr_= qjet2_discr;
//        varList.jet3_discr_= qjet3_discr;
//	varList.Xtt0_ = qXtt0;
//	varList.top_mass_ = qtop_mass;
//	varList.Tprime_mass_ = qTprime_mass;
//	varList.Tprime_mt_ = qTprime_mt;
	varList.ScalarTPtOverAllPt_ = (qsolvedMET_pt + qdipho_pt + qlepton_leadPt + qbjet1_pt)/(qHT + qrecoMET_pt + qlepton_leadPt);
	varList.recoMET_pt_ = qrecoMET_pt;
//------------------------------------DEBUGGING---------------------------
	bool debug=false;
	if(debug){
        std::cout<<"dipho_leadPtOvermass_ 	"<< qdipho_leadPt/qdipho_mass<<endl;
        std::cout<<"dipho_subleadPtOvermass_ 	"<< qdipho_subleadPt/qdipho_mass<<endl;
        std::cout<<"dipho_leadEta_ 	"<< qdipho_leadEta<<endl;
        std::cout<<"dipho_subleadEta_	"<< qdipho_subleadEta<<endl;
        std::cout<<"dipho_leadIDMVA_	"<< qdipho_leadIDMVA<<endl;
        std::cout<<"dipho_subleadIDMVA_	"<< qdipho_subleadIDMVA<<endl;
        std::cout<<"dipho_lead_haspixelseed_	"<< qdipho_lead_haspixelseed<<endl;
        std::cout<<"dipho_sublead_haspixelseed_	"<< qdipho_sublead_haspixelseed<<endl;
        std::cout<<"n_jets_		"<< qn_jets<<endl;
        std::cout<<"n_bjets_		"<< qn_bjets<<endl;
        std::cout<<"n_centraljets_	"<< qn_centraljets<<endl;
        std::cout<<"lepton_ch_		"<< qlepton_ch<<endl;
        std::cout<<"lepton_leadPt_	"<< qlepton_leadPt<<endl;
        std::cout<<"lepton_leadEta_	"<< qlepton_leadEta<<endl;
        std::cout<<"fwdJet1_pt_		"<< qfwdJet1_pt<<endl;
//        std::cout<<"fwdJet1_eta_"<< qfwdJet1_eta<<endl;
        std::cout<<"fwdJet1_discr_	"<< qfwdJet1_discr<<endl;
//        std::cout<<"top_mt11_"<< qtop_mt11<<endl;
        std::cout<<"dRtHchainfwdjet_	"<< qdRtHchainfwdjet<<endl;
        std::cout<<"dRleptonbjet_	"<< qdRleptonbjet<<endl;
        std::cout<<"dRleptonfwdjet_	"<< qdRleptonfwdjet<<endl;
        std::cout<<"dRbjetfwdjet_	"<< qdRbjetfwdjet<<endl;
        std::cout<<"dRleadphofwdjet_	"<< qdRleadphofwdjet<<endl;
        std::cout<<"dRsubleadphofwdjet_"<< qdRsubleadphofwdjet<<endl;
        std::cout<<"bjet1_pt_	"<< qbjet1_pt<<endl;
//        std::cout<<"bjet2_pt_	"<< qbjet2_pt<<endl;
//        std::cout<<"bjet3_pt_	"<< qbjet3_pt<<endl;
        std::cout<<"bjet1_eta_	"<< qbjet1_eta<<endl;
//        std::cout<<"bjet2_eta_"<< qbjet2_eta<<endl;
//        std::cout<<"bjet3_eta_"<< qbjet3_eta<<endl;
        std::cout<<"bjet1_discr_"<< qbjet1_discr<<endl;
//        std::cout<<"bjet2_discr_"<< qbjet2_discr<<endl;
//        std::cout<<"bjet3_discr_"<< qbjet3_discr<<endl;
        std::cout<<"jet1_pt_	"<< qjet1_pt<<endl;
        std::cout<<"jet2_pt_	"<< qjet2_pt<<endl;
//        std::cout<<"jet3_pt_"<< qjet3_pt<<endl;
        std::cout<<"jet1_eta_	"<< qjet1_eta<<endl;
        std::cout<<"jet2_eta_	"<< qjet2_eta<<endl;
//        std::cout<<"jet3_eta_"<< qjet3_eta<<endl;
//        std::cout<<"jet1_discr_"<< qjet1_discr<<endl;
//        std::cout<<"jet2_discr_"<< qjet2_discr<<endl;
//        std::cout<<"jet3_discr_"<< qjet3_discr<<endl;
//        std::cout<<"Xtt0_ "<< qXtt0<<endl;
//        std::cout<<"top_mass_ "<< qtop_mass<<endl;
//        std::cout<<"Tprime_mass_ "<< qTprime_mass<<endl;
//        std::cout<<"Tprime_mt_ "<< qTprime_mt<<endl;
	}
//-------------------------------------------------------------------------------
	if ( qlepton_leadPt>10 )Yield_BCut = Yield_BCut + qweight;
	float mvareader_NonHiggs = -99.0;
	float mvareader_Higgs = -99.0;
	mvareader_NonHiggs = mvAna_NonHiggs->evaluate(mvAlgo_, varList);
	mvareader_Higgs = mvAna_Higgs->evaluate(mvAlgo_, varList);
	MVAscore_TprimeVsNonHiggs = mvAna_NonHiggs->convert_tmva_to_prob(mvareader_NonHiggs);
	MVAscore_TprimeVsHiggs = mvAna_Higgs->convert_tmva_to_prob(mvareader_Higgs);
	Mtilde_ = Mtilde(qTprime_mass, qtop_mass, qdipho_mass);
	t1->Fill();
//	cout<<"MVA Score_NonHiggs=       "<<mvareader_NonHiggs<<endl;
//	if (MVAscore_TprimeVsHiggs>0.63 && qlepton_leadPt>10)cout<<"Dipho_mass	="<<qdipho_mass<<"MVA Score_Higgs=     "<<MVAscore_TprimeVsHiggs<<endl;			
	if ((qTprime_mass>650 && qTprime_mass<1600) && MVAscore_TprimeVsHiggs>0.2 && qlepton_leadPt>10)Yield_ACut = Yield_ACut + qweight;
//if(MVAscore_TprimeVsNonHiggs>0. && MVAscore_TprimeVsHiggs > 0.03 /*&&(qdipho_mass<115 || qdipho_mass>135)*/){cout <<"lepton_leadPt_   "<<qlepton_leadPt<<endl;}
/*	if(abs(qMVAscore_tHqVsttH_BDT-MVAscore_TprimeVsHiggs) >0.001 ){
	cout<<"Score from flashgg  "<<qMVAscore_tHqVsttH_BDT<<endl;
	cout<<"[WARNING] Score is not matching"<<(qMVAscore_tHqVsttH_BDT-MVAscore_TprimeVsHiggs)<<endl;
	}
*/
	}
	t1->Write();
	if (myfile.is_open()) myfile<<procs[i].c_str()<< "\t\t"<<Yield_BCut<<"\t\t"<<Yield_ACut<<"\t\t"<<Yield_ACut/Yield_BCut<<endl;
//	cout<<"Before cut 	"<<procs[i].c_str()<<" ="<<Yield_BCut<<endl;
//	cout<<"After cut 	"<<procs[i].c_str()<<" ="<<Yield_ACut<<endl;
//	cout<<"Fraction		"<<procs[i].c_str()<<" ="<<Yield_ACut/Yield_BCut<<endl;
	}
return 0;
}

int main(int argc, char** argv){

	return MVA_score();

}
