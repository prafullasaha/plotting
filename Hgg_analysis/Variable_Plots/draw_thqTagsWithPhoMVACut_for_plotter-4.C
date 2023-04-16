{
/*  Plotter *p = new Plotter("root://eoscms.cern.ch//store/user/gkole/Hgg/thq/28Apr2019/",
			   42.00 // 12.89 inv /fb for ICHEP already applied in fggRunJobs
			   );
*/
    Plotter *p = new Plotter("/",
                           35.9 // 12.89 inv /fb for ICHEP already applied in fggRunJobs
                           );


  // declare process labels, plotting styles and input files
  // 1st argument is label, 2nd is root filename, 3rd is actual tree+prefix, line-color, fil color)
  p->addData("tHq",     "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_THQ_ctcvcp_HToGG_M125_13TeV-madgraph-pythia8_SM.root",                               "thq_125");

  p->addMC  ("DiPhotonJetsBox", "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root", "DiPhotonJetsBox", kBlack, kGreen-2);
  p->addMC  ("GJet", "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root", "gjets", kBlack, kPink-3);
//  p->addMC  ("ttH", "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/2017/output_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root",               "tth_125", kBlack, kBlue-1);
  p->addMC  ("TTGG",   "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_TTGG_0Jets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root",                  "ttgg", kBlack, kOrange-3);
  p->addMC  ("TTGJets", "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root",              "ttgjets", kBlack, kYellow-3);
//  p->addMC  ("TGJets", "../output_TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8.root",                "tgjets", kBlack, kRed-1);
  p->addMC  ("DiPhotonJetsBox2BJets", "/eos/user/p/prsaha/Hgg_analysis_LRun2_NewPreSel/MVA_opt_inputs/UL2017/output_DiPhotonJetsBox2BJets_MGG-80toInf_13TeV-Sherpa.root", "DiPhotonJetsBox2BJets", kBlack, kGreen-4);
  //  p->addMC  ("QCD",      "output_QCD.root",                                "qcd",   kBlack, kGray);
  //  p->addMC  ("DY",       "output_DYJetsToLL.root",                         "DYjet", kBlack, kGreen-2);
  //  p->addMC  ("GJet",     "output_GJet.root",                               "gjet",  kBlack, kBlue-1);
  //  p->addMC  ("DiPhoton", "output_DiPhotonJetsBox.root",                    "dipho", kBlack, kOrange-3);

  // make plots
  //  p->plot("mass",40,100.0,200.0, true);
  //  p->plot("leadPt",60,0,300);

  //-------
  //plot("observable", int nbins, double observableMin,  double observableMax,  bool drawdata = true,  bool log = false)
  //-------

  // make html plots
  p->startHTML();

  


  // blinding
  ////  p->addDataOnlyCut("mass < 115 || mass >= 135");

  // apply cut on both data and MC
  //  p->addDataOnlyCut("diphoMVA > -0.5");
  ////  p->plot("mass",40,100.0,200.0);
  ////p->removeLastDataOnlyCut(); 

  //  p->plot("leadPt",60,0,300);
  //  p->plot("nvtx",50,0,50);


  // 28Apr2019 good variables for thq

  p->plot("dipho_pt", 30, 0,600);
  p->plot("dipho_leadPt", 30, 0,600);
  p->plot("dipho_leadEta", 30, -3, 3);
  p->plot("dipho_leadIDMVA", 30, 0, 1);
  p->plot("dipho_lead_haspixelseed", 10, 0, 1);
  p->plot("dipho_subleadPt", 30, 0,600);
  p->plot("dipho_subleadEta", 30, -3, 3);
  p->plot("dipho_subleadIDMVA", 30, 0, 1);
  p->plot("dipho_sublead_haspixelseed", 10, 0, 1);
  p->plot("n_jets",       10, 0, 10);
  p->plot("n_bjets",      10, 0, 10);
  p->plot("n_centraljets", 10, 0, 10);
  p->plot("lepton_charge", 4, -2, 2);
  p->plot("lepton_leadPt", 30, 0, 600);
  p->plot("lepton_leadEta", 30, -3, 3);
  p->plot("fwdjet1_pt", 30, 0, 600);
  p->plot("fwdjet1_eta", 30, -5, 5);
  p->plot("fwdjet1_discr", 30, 0, 1);
  p->plot("top_mt", 30, 0, 800);
  p->plot("dr_tHchainfwdjet", 30, 0, 7);
  p->plot("dr_leptonbjet", 30, 0, 7);
  p->plot("dr_leptonfwdjet", 30, 0, 7);
  p->plot("dr_bjetfwdjet", 30, 0, 7);
  p->plot("dr_leadphofwdjet", 30, 0, 7);
  p->plot("dr_subleadphofwdjet", 30, 0, 7);
  p->plot("bjet1_discr", 30, 0, 1);
  p->plot("bjet2_discr", 30, 0, 1);
  p->plot("bjet3_discr", 30, 0, 1);
  p->plot("bjet1_pt",  30, 0, 600);
  p->plot("bjet2_pt", 30, 0, 600);
  p->plot("bjet3_pt",  30, 0, 600);
  p->plot("bjet1_eta", 30, -5, 5);
  p->plot("bjet2_eta", 30, -5, 5);
  p->plot("bjet3_eta", 30, -5, 5);
  p->plot("jet1_pt", 30, 0, 600);
  p->plot("jet2_pt", 30, 0, 600);
  p->plot("jet3_pt", 30, 0, 600);
  p->plot("jet1_eta", 30, -5, 5);
  p->plot("jet2_eta", 30, -5, 5);
  p->plot("jet3_eta", 30, -5, 5);
  p->plot("jet1_discr", 30, 0, 1);
  p->plot("jet2_discr", 30, 0, 1);
  p->plot("jet3_discr", 30, 0, 1);
  p->plot("MVAscore_tHqVsttH_DNN", 30, 0, 1);
//  p->plot("MVA_thqVsNonPeakingBkg", 30, -0.5, 0.5);
//  p->plot("MVAresult_thq", 30, -0.5, 0.5);   
//  p->plot("dipho_mass", 50, 100, 180);



  //  p->plot("diphoMVA",100,-1.0,1.0);
//
//  p->plot("leadIDMVA",100,-1.0,1.0);
//  p->plot("subleadIDMVA",100,-1.0,1.0);
//  p->plot("genmatch1",5,-1.0,4.0,"",true);
//  p->plot("genmatch2",5,-1.0,4.0,"",true);
//  p->plot("genmatch1+genmatch2",6,-1.0,5.0,"",true);
//  p->plot("genmatch1*genmatch2",6,-1.0,5.0,"",true);
//  p->plot("hasGenmatch1",3,-1.0,2.0,"",true);
//  p->plot("hasGenmatch2",3,-1.0,2.0,"",true);
  

//  p->writeHTML("/tmp/gkole/THQLeptonic_Tags_v1.html");

}
