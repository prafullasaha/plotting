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
#include "TLatex.h"
#include "THStack.h"

void estimate_mean_and_error(TH1* h_sig, double &mean_signal, double &width_signal)
{
    //--- Do the mean and width calculation ---//
    int bin_max = h_sig->GetMaximumBin();
    mean_signal = h_sig->GetBinCenter(bin_max);
    width_signal = 0.;
    double binW = h_sig->GetBinWidth(1);

    double all_integral = 0.;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
        all_integral += h_sig->GetBinContent(i)*binW;

    double acc_integral = h_sig->GetBinContent(bin_max)*binW;
    for(int i=1;i<(int)h_sig->GetNbinsX();++i)
    {
        acc_integral += h_sig->GetBinContent(bin_max+i)*binW;
        acc_integral += h_sig->GetBinContent(bin_max-i)*binW;
        if( acc_integral/all_integral >= 0.682 ) {
            width_signal = h_sig->GetBinCenter(bin_max+i) - mean_signal;
            break;
        }
    }

    printf("[self] ratio = %.2f (%.2f/%.2f)\n", acc_integral/all_integral, acc_integral, all_integral );
    printf("[self] mass = %.2f \\pm %.2f\n", mean_signal, width_signal);
}

void fit_topmass(TString object, TString T_mass, double init_mean, double lower_bound, double upper_bound, double init_sigma){

gStyle->SetOptStat(0);
gROOT->SetBatch();

TString file_name="/eos/user/p/prsaha/Tprime_analysis/MVA_inputs/RunII/output_TprimeBToTH_Hgg_M-"+ T_mass + "_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8.root";

TFile *file = new TFile(file_name, "READ");

TTree *tree = (TTree*)file->Get("tagsDumper/trees/Tprime_" + T_mass + "_13TeV_THQLeptonicTag");

TH1F* h_mass =new TH1F("h_mass","h_mass",100,lower_bound, upper_bound);
TH1F* h_tmass =new TH1F("h_tmass","h_tmass",100,100,300);

TLegend *leg1 = new TLegend(0.7, 0.7, 0.9, 0.9, "");

tree->Draw(object + "_mass >> h_mass", "weight", "hist");
tree->Draw("top_mass >> h_tmass", "weight", "hist");

h_mass->SetLineWidth(2);
h_tmass->SetLineWidth(2);

/*
cout<<"h_genMET_pz Entries"<<h_genMET_pz->GetEntries()<<endl;
cout<<"h_solvedMET_pz Entries"<<h_solvedMET_pz->GetEntries()<<endl;
cout<<"h_promptGenMET_pz Entries"<<h_promptGenMET_pz->GetEntries()<<endl;
*/

TF1 *double_gaus = new TF1("double_gaus","([5])*([0]/sqrt(2*TMath::Pi())*[2])*exp(-pow((x-[1]),2)/2*[2]*[2])+(1-[5])*([3]/sqrt(2*TMath::Pi())*[4])*exp(-pow((x-[1]),2)/2*[4]*[4])",500,900);

using namespace RooFit;
RooRealVar  top_mass("top_mass", "top_mass", lower_bound, upper_bound);
RooRealVar  mass("mass", "mass", lower_bound, upper_bound);
//RooDataHist data("data","dataset with T' mass", mass , h_mass) ;
//RooDataHist data("data","dataset with T' mass", top_mass , h_mass) ;
RooDataSet data("data","dataset with T' mass", tree, top_mass);//, "top_mass > 0", "weight") ;


RooRealVar  mu("mu", "mu", init_mean, lower_bound, upper_bound);
RooRealVar  sigma("sigma", "sigma", init_sigma, 0.1, 100.);
RooGaussian gaus("gaus", "gaus", top_mass, mu, sigma);

RooRealVar  mu_2nd("mu_2nd", "mu_2nd", init_mean, lower_bound, upper_bound);
RooRealVar  sigma_2nd("sigma_2nd", "sigma_2nd", init_sigma, 0.1, 100.0);
RooGaussian gaus_2nd("gaus_2nd", "gaus_2nd", top_mass, mu_2nd, sigma_2nd);

RooRealVar  mu_3("mu_3", "mu_3", init_mean, lower_bound, upper_bound);
RooRealVar  sigma_3("sigma_3", "sigma_3", init_sigma, 0.1, 100.0);
RooGaussian gaus_3("gaus_3", "gaus_3", top_mass, mu_3, sigma_3);

RooRealVar  mu_4("mu_4", "mu_4", init_mean, lower_bound, upper_bound);
RooRealVar  sigma_4("sigma_4", "sigma_4", init_sigma, 0.1, 100.0);
RooGaussian gaus_4("gaus_4", "gaus_4", top_mass, mu, sigma_4);

RooRealVar  frac("frac", "frac", 0.8, 0.0, 1.0);
RooAddPdf   model_2("model_2", "model_2", RooArgList(gaus, gaus_2nd ), RooArgList(frac));

RooRealVar frac1("frac1","fg1", 0.8, 0, 1);
RooAddPdf model_3("model_3","model_3", RooArgList(model_2,gaus_3), frac1);

RooRealVar frac2("frac2","fg2", 0.8, 0, 1);
RooAddPdf model("model","model", RooArgList(model_3,gaus_4), frac2);


model.fitTo(data,Minos(true), NumCPU(8));

//cout<<"par 1=	-----------------------------------------------------------------"<<model.GetParameter(0)<<endl;
//model.fitTo(data, RooFit::Minimizer("Minuit2","minimize"),RooFit::Minos(1),RooFit::Hesse(1),RooFit::PrintLevel(-1),RooFit::Strategy(0),RooFit::SumW2Error(kTRUE));

//model.fitTo(data, Minos(true));
//model.fitTo(data,NumCPU(8));

RooDataSet *pseudo_data = model.generate(top_mass, 100 * 1000);
    TH1 *model_hist = pseudo_data->createHistogram("top_mass", 100 * 10);
    double std_mean = h_mass->GetMean();
    double std_dev = h_mass->GetStdDev();
//    double mode_1 = model_hist->GetMean();
//    double mode_sigma_1 = model_hist->GetStdDev();
    double mode, mode_sigma;	
    estimate_mean_and_error(model_hist, mode, mode_sigma);

TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
c1->cd();
c1->SetTitle("");
c1->SetGridx();
RooPlot *frame_mass=top_mass.frame();
frame_mass->SetTitle("");
frame_mass->GetXaxis()->SetTitle(object +" mass(GeV)");
frame_mass->GetYaxis()->SetTitleOffset(1.5);
data.plotOn(frame_mass);
model.plotOn(frame_mass);
frame_mass->Draw();

TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextAlign(11);
    latex.SetTextSize(20);
//    latex.DrawLatex( 0.6, 0.80, "std. hist " );
//    latex.DrawLatex( 0.6, 0.70, "fit. mode " );
//latex.DrawLatex( 0.6, 0.90, "fit. mode hist " );
//    latex.DrawLatex( 0.72, 0.80, Form("  : %.2f #pm %.2f", std_mean, std_dev) );
    latex.DrawLatex( 0.150, 0.85, Form("#scale[0.75]{Mean : %.2f GeV}", mode) );
	latex.DrawLatex( 0.150, 0.80, Form("#scale[0.75]{#sigma_{eff} : %.2f GeV}",mode_sigma/2) );
//	latex.DrawLatex( 0.77, 0.90, Form("  : %.2f #pm %.2f", mode_1, mode_sigma_1) );
//h_mass->Fit(double_gaus, "R");
//h_mass->Draw("");
//h_tmass->Draw("hist");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/Tmass_fit/"+object+"_massOn_Tprime"+T_mass+".png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/Tmass_fit/"+object+"_massOn_Tprime"+T_mass+".pdf");
} 
