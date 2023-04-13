#ifndef __MVAnalysis__h
#define __MVAnalysis__h

#include <fstream>
#include <string>

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

typedef struct
{
	float dipho_leadPtOvermass_;
	float dipho_subleadPtOvermass_;
	float dipho_leadEta_;
        float dipho_subleadEta_;
        float dipho_leadIDMVA_;
        float dipho_subleadIDMVA_;
        float dipho_lead_haspixelseed_;
        float dipho_sublead_haspixelseed_;
        float n_jets_;
        float n_bjets_;
        float n_centraljets_;
        float lepton_ch_;
        float lepton_leadPt_;
        float lepton_leadEta_;
        float fwdJet1_pt_;
        float fwdJet1_eta_;
        float fwdJet1_discr_;
        float top_mt11_;
        float dRtHchainfwdjet_;
        float dRleptonbjet_;
        float dRleptonfwdjet_;
        float dRbjetfwdjet_;
        float dRleadphofwdjet_;
        float dRsubleadphofwdjet_;
        float bjet1_pt_;
        float bjet2_pt_;
        float bjet3_pt_;
        float bjet1_eta_;
        float bjet2_eta_;
        float bjet3_eta_;
        float bjet1_discr_;
        float bjet2_discr_;
        float bjet3_discr_;
        float jet1_pt_;
        float jet2_pt_;
        float jet3_pt_;
        float jet1_eta_;
        float jet2_eta_;
        float jet3_eta_;
        float jet1_discr_;
        float jet2_discr_;
        float jet3_discr_;
	float Xtt0_;
	float top_mass_;
	float Tprime_mass_;
	float Tprime_mt_;
	float ScalarTPtOverAllPt_;
	float recoMET_pt_; 
}  InputVariables;


class MVAnalysis {

 public:

  MVAnalysis(const std::string& mva_algo, const std::string& xmlfile);
  virtual ~MVAnalysis() {}
  double evaluate(const std::string& tag, const InputVariables& varList);
  double convert_tmva_to_prob(double score);
  InputVariables varList_;
  std::unique_ptr<TMVA::Reader> reader_;
};
#endif
