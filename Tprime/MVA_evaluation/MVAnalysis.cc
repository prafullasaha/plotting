#include <iostream>
#include <memory>
#include "MVAnalysis.h"

using std::string;
using std::cout;
using std::endl;

MVAnalysis::MVAnalysis(const string& mva_algo, const string& xmlfile)
{

  reader_ = std::unique_ptr<TMVA::Reader>(new TMVA::Reader("!Color:!Silent"));

        reader_->AddVariable( "dipho_leadPt/dipho_mass", &varList_.dipho_leadPtOvermass_ );
        reader_->AddVariable( "dipho_subleadPt/dipho_mass", &varList_.dipho_subleadPtOvermass_ );
        reader_->AddVariable( "dipho_leadEta", &varList_.dipho_leadEta_ );
        reader_->AddVariable( "dipho_subleadEta", &varList_.dipho_subleadEta_ );
        reader_->AddVariable( "dipho_leadIDMVA", &varList_.dipho_leadIDMVA_ );
        reader_->AddVariable( "dipho_subleadIDMVA", &varList_.dipho_subleadIDMVA_ );
        reader_->AddVariable( "dipho_lead_haspixelseed", &varList_.dipho_lead_haspixelseed_ );
        reader_->AddVariable( "dipho_sublead_haspixelseed", &varList_.dipho_sublead_haspixelseed_ );
        reader_->AddVariable( "n_jets"  ,              &varList_.n_jets_);
        reader_->AddVariable( "n_bjets",               &varList_.n_bjets_ );
        reader_->AddVariable( "n_centraljets",         &varList_.n_centraljets_);
        reader_->AddVariable( "lepton_charge",         &varList_.lepton_ch_);
        reader_->AddVariable( "lepton_leadPt",         &varList_.lepton_leadPt_);
        reader_->AddVariable( "lepton_leadEta",         &varList_.lepton_leadEta_);
        reader_->AddVariable( "fwdjet1_pt",           &varList_.fwdJet1_pt_);
//        reader_->AddVariable( "fwdjet1_eta",           &varList_.fwdJet1_eta_);
        reader_->AddVariable( "fwdjet1_discr",           &varList_.fwdJet1_discr_);
//        reader_->AddVariable( "top_mt",                 &varList_.top_mt11_  );
        reader_->AddVariable( "dr_tHchainfwdjet",       &varList_.dRtHchainfwdjet_  );
        reader_->AddVariable( "dr_leptonbjet",          &varList_.dRleptonbjet_  );
        reader_->AddVariable( "dr_leptonfwdjet",        &varList_.dRleptonfwdjet_  );
        reader_->AddVariable( "dr_bjetfwdjet",    &varList_.dRbjetfwdjet_);
        reader_->AddVariable( "dr_leadphofwdjet",       &varList_.dRleadphofwdjet_  );
        reader_->AddVariable( "dr_subleadphofwdjet" ,   &varList_.dRsubleadphofwdjet_);
        reader_->AddVariable( "bjet1_pt",              &varList_.bjet1_pt_);
//        reader_->AddVariable( "bjet2_pt",              &varList_.bjet2_pt_);
//        reader_->AddVariable( "bjet3_pt",              &varList_.bjet3_pt_);
        reader_->AddVariable( "bjet1_eta",              &varList_.bjet1_eta_);
//        reader_->AddVariable( "bjet2_eta",              &varList_.bjet2_eta_);
//        reader_->AddVariable( "bjet3_eta",              &varList_.bjet3_eta_);
        reader_->AddVariable( "bjet1_discr",            &varList_.bjet1_discr_);
//        reader_->AddVariable( "bjet2_discr",            &varList_.bjet2_discr_);
//        reader_->AddVariable( "bjet3_discr",            &varList_.bjet3_discr_);
        reader_->AddVariable( "jet1_pt",                &varList_.jet1_pt_);
        reader_->AddVariable( "jet2_pt",                &varList_.jet2_pt_);
//        reader_->AddVariable( "jet3_pt",                &varList_.jet3_pt_);
        reader_->AddVariable( "jet1_eta",               &varList_.jet1_eta_);
        reader_->AddVariable( "jet2_eta",               &varList_.jet2_eta_);
//        reader_->AddVariable( "jet3_eta",               &varList_.jet3_eta_);
//        reader_->AddVariable( "jet1_discr",               &varList_.jet1_discr_);
//        reader_->AddVariable( "jet2_discr",               &varList_.jet2_discr_);
//        reader_->AddVariable( "jet3_discr",               &varList_.jet3_discr_);
//	reader_->AddVariable( "Xtt0",               &varList_.Xtt0_);
//	reader_->AddVariable( "top_mass",               &varList_.top_mass_);
//	reader_->AddVariable( "Tprime_mass",               &varList_.Tprime_mass_);
//	reader_->AddVariable( "Tprime_mt",               &varList_.Tprime_mt_);
	reader_->AddVariable( "(solvedMET_pt + dipho_pt + lepton_leadPt + bjet1_pt)/(HT + recoMET_pt + lepton_leadPt)",               &varList_.ScalarTPtOverAllPt_);
	reader_->AddVariable( "recoMET_pt", &varList_.recoMET_pt_);
//  reader_->BookMVA(mva_algo.c_str(), "/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/Training/dataset_Run2018_TprimeVsNonHiggs/weights/TMVAClassification_BDT.weights.xml");
	reader_->BookMVA(mva_algo.c_str(), xmlfile.c_str());

}

double MVAnalysis::evaluate(const string& mva_algo, const InputVariables& varList) {
  memcpy(&varList_, &varList, sizeof(varList)); // use move syntax here                                                                                                      
  return reader_->EvaluateMVA(mva_algo.c_str());
}

double MVAnalysis::convert_tmva_to_prob(double score)
{
  // Undo TMVA transformation
  double raw_score = -0.5 * log( (2 / (score + 1)) - 1);

  // Apply logistic (sigmoid) transformation
  double prob = 1 / (1 + exp(-raw_score));
  return prob;
}
