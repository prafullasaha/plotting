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
#include "tdrStyle/tdrstyle.C"
#include "tdrStyle/CMS_lumi.C"

int MVA_distribution( int year=2, bool BDT_Higgs =false, bool BDT_NonHiggs = false){

//gROOT->SetBatch(true);
//setTDRStyle();
const int file_size=16;
float lumi=0;
double min_score=0;
double max_score=1;
int nbins=30;
int nbins_2DH=30;
if(BDT_Higgs){
	nbins=20;
	nbins_2DH =100;
	min_score=0.;
	max_score=1.;
	};

if(BDT_NonHiggs){
	nbins=30;
	nbins_2DH =100;
	min_score=-0.4;
	max_score=0.4;
	};

double MVA1_min=0.;
double MVA1_max=1.;
double MVA2_min=0.;
double MVA2_max=1.;

double MVA1_cut=0.04;//For ttH bkg
double MVA2_cut=0.;//For non-Higgs bkg
float bin_width = (max_score-min_score)/nbins;

//TString file[];
std::vector<TString> file;
TString file_path;
cout<<"year"<<year<<endl;
string method;
string T_mass[2]={"600","700"};

if(year == 2){
//file_path = Form("/eos/user/p/prsaha/Tprime_analysis/MVAOpt_inputs/output_files_Tprime%s_%sVsHiggs_BDTG/Run2/", T_mass[0].c_str(), T_mass[1].c_str() );
	file_path = Form("/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/output_files_Tprime%s_%sVsHiggs_BDTG_UL/Run2/", T_mass[0].c_str(), T_mass[1].c_str() );
	file.push_back("output_Data.root");
    file.push_back(Form("output_Tprime_%s.root",T_mass[0].c_str()));
    file.push_back(Form("output_Tprime_%s.root",T_mass[1].c_str()));
    file.push_back("output_tth_125.root");
    file.push_back("output_thq_125.root");
    file.push_back("output_vh_125.root");
	file.push_back("output_ttgg.root");
	file.push_back("output_ttgjets.root");
	file.push_back("output_DiPhotonJetsBox.root");
	file.push_back("output_gjets.root");
	file.push_back("output_ttjets.root");
	file.push_back("output_tgjets.root");
	file.push_back("output_ttwjets.root");
	file.push_back("output_ZG.root");
	file.push_back("output_WG.root");
	file.push_back("output_DYJets.root");
	file.push_back(Form("output_Tprime_%s.root",T_mass[0].c_str()));
	file.push_back(Form("output_Tprime_%s.root",T_mass[1].c_str()));
	file.push_back("output_tth_125.root");
	file.push_back("output_thq_125.root");
	file.push_back("output_vh_125.root");
//	file.push_back("output_Data.root");
	lumi=138;
	}


string procs[file_size] = {"Data", Form("Tprime_%s",T_mass[0].c_str()), Form("Tprime_%s",T_mass[1].c_str()),"tth_125","thq_125","vh_125","ttgg", "ttgjets","DiPhotonJetsBox","gjets","ttjets","tgjets"/*,"WW","WZ","ZZ"*/,"ttwjets","ZG","WG",/*"ttZ","tZq",*/"DYJets"};
//string procs_[file_size] = {"tt#gamma#gamma", "tt#gamma + jets","#gamma#gamma + jets", "#gamma#gamma + 2 b jets","#gamma + jets","tHq","ttH","Data"/*, "ttjets", "gjetsPt20to40","DYJets"*/};

string procs_[file_size] = {"Data",Form("Tprime_%s",T_mass[0].c_str()), Form("Tprime_%s",T_mass[1].c_str()), "ttH","tHq","VH","tt#gamma#gamma", "tt#gamma + jets","#gamma#gamma + jets","#gamma + jets","tt + jets","t#gamma+jets",/*"WW","WZ","ZZ",*/"TTW","Z + #gamma","W + #gamma",/*"ttZ","tZq",*/"Drell-Yan"/*, "ttjets", "gjetsPt20to40","DYJets"*/};

THStack* hs = new THStack("hs",";MVA_score;Events");
TH1F* bkg_others=new TH1F("bkg_others",";BDT_NonHiggs_score",nbins,min_score,max_score);

TLegend *leg1 = new TLegend(0.25, 0.65, 0.9, 0.84, "");
	leg1->SetNColumns(4);
//TLegend *leg2 = new TLegend(0.6, 0.6, 0.9, 0.89, "");
int count=0;

TH1F* hist_Data=new TH1F("MVA_score_data",";MVA_score",nbins,min_score,max_score);
TH1F* hist_Tprime1=new TH1F("MVA_score_T1",";MVA_score",nbins,min_score,max_score);
TH1F* hist_Tprime2=new TH1F("MVA_score_T2",";MVA_score",nbins,min_score,max_score);
TH1F* hist_HiggsBkg=new TH1F("MVA_score_tth",";MVA_score",nbins,min_score,max_score);
TH1F* totalMC=new TH1F("totalMC",";BDT_NonHiggs_score",nbins,min_score,max_score);
TGraphErrors *gr_Data = new TGraphErrors();
TGraphErrors *gr_Ratio = new TGraphErrors();
TH2F* h2_thq=new TH2F("MVA_thq","Tprime;BDTscore_TprimeVsHiggsBkg;BDTscore_TprimeVsNonHiggsBkg",nbins_2DH,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_tth=new TH2F("MVA_tth","HiggsBkg;BDTscore_TprimeVsHiggsBkg;BDTscore_TprimeVsNonHiggsBkg",nbins_2DH,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_bkg=new TH2F("MVA_sig","NonHiggsBkg;BDTscore_TprimeVsHiggsBkg;BDTscore_TprimeVsNonHiggsBkg",nbins_2DH,MVA1_min,MVA1_max,nbins,MVA2_min,MVA2_max);
TH2F* h2_TVsDiPhoMass = new TH2F("h2_TVsDiPhoMass","Data Events;Diphoton mass;Tprime mass",50,100,180,50,0,1200);
TH1F* hist[file_size];

gStyle->SetOptStat(0);
gStyle->SetCanvasPreferGL(true);
//gStyle->SetErrorX(0);
float totalMCYield=0;
float DataYield=0;
int MVA_no = 1;
//-----------------------BDT_Higgs-------------------------------------------------------------------------
if(BDT_Higgs){
	cout<<"Running BDT_Higgs distribution----------------------------------------"<<endl;
	method = Form("Tprime%s_%sVsHiggs_BDTG",T_mass[0].c_str(), T_mass[1].c_str());

	for(int i=0; i<file_size; i++)
		{
    	TFile *file_ = new TFile(file_path + file.at(i), "READ");
    	TTree* tree_ = (TTree*)file_->Get(Form("%s_13TeV_THQLeptonicTag", procs[i].c_str()));
		cout<<"process=     "<<procs[i].c_str()<<endl;
    	Float_t qdipho_mass, qTprime_mass, qweight;
    	Float_t qMVA1, qMVA2;
    	tree_->SetBranchAddress("dipho_mass", &qdipho_mass);
		tree_->SetBranchAddress("Tprime_mass", &qTprime_mass);
    	tree_->SetBranchAddress("MVAscore_TprimeVsHiggs", &qMVA1);//MVAresult_thq
    	tree_->SetBranchAddress("MVAscore_TprimeVsNonHiggs", &qMVA2);
    	tree_->SetBranchAddress("weight", &qweight);
    	tree_->SetBranchStatus("*", 1);
   		Int_t nentries=(Int_t)tree_->GetEntries();
   		hist[i]=new TH1F("MVA_score_Bkg"," ;m_{#gamma#gamma}",nbins,min_score,max_score);

    	for(int ievent=0; ievent < nentries; ievent++)
        	{
            tree_-> GetEntry( ievent );
//          if(qweight > 0 && qMVA1 >= MVA1_cut && qMVA2 >= MVA2_cut){
//			if(qdipho_mass > 115 && qdipho_mass < 135){
            	if(procs[i]=="Data")
            	{
				if(qMVA1 >= MVA1_cut && qMVA2 >= MVA2_cut) h2_TVsDiPhoMass->Fill(qdipho_mass, qTprime_mass, qweight);
//                if(qdipho_mass<115 || qdipho_mass>135){
                hist_Data->Fill(qMVA1, qweight);
//                }
                }
                else if(procs[i]== Form("Tprime_%s",T_mass[0].c_str()))
                {
                hist_Tprime1->Fill(qMVA1, qweight);
//                h2_thq->Fill(qMVA1, qMVA2, qweight);
                }
                else if(procs[i]== Form("Tprime_%s",T_mass[1].c_str()))
                {
                hist_Tprime2->Fill(qMVA1, qweight);
                h2_thq->Fill(qMVA1, qMVA2, qweight);
				}
                else if(procs[i]=="tth_125" || procs[i]=="thq_125" || procs[i]=="vh_125")
                {
//		if(qweight < 3){
                hist_HiggsBkg->Fill(qMVA1, qweight);
                h2_tth->Fill(qMVA1, qMVA2, qweight);
//		}
                }
                else
                {
//				if(qdipho_mass<115 || qdipho_mass>135){
                hist[i]->Fill(qMVA1, qweight);
//				}
                hist[i]->SetFillColor(i);
                h2_bkg->Fill(qMVA1, qMVA2, qweight);
                }
//                }
//			}
        	}
        if(procs[i] != Form("Tprime_%s",T_mass[0].c_str()) || procs[i] != Form("Tprime_%s",T_mass[1].c_str()) || procs[i] != "Data" || procs[i] != "tth_125" || procs[i] != "thq_125" || procs[i] != "vh_125"){
        totalMCYield= totalMCYield + hist[i]->Integral();
        }
        }
}

DataYield= hist_Data->Integral();
cout<<"totalMCYield   ="<<totalMCYield<<endl;
cout<<"DataYield   ="<<DataYield<<endl;
cout<<"Higgs Yield   ="<<hist_HiggsBkg->Integral()<<endl;
cout<<"Tprime Yield   ="<<hist_Tprime2->Integral()<<endl;
hist_Data->SetBinErrorOption(TH1::kPoisson);
cout<<"hist_data->GetBinError(9) "<<hist_Data->GetBinError(9)<<endl;
cout<<"Err. Method\t"<<hist_Data->GetBinErrorOption()<<endl;
    double q_sum=0;
for(int j=0; j<file_size; j++)
{
	if(procs[j] != Form("Tprime_%s",T_mass[0].c_str()) || procs[j] != Form("Tprime_%s",T_mass[j].c_str()) || procs[j] != "Data" || procs[j] != "tth_125" || procs[j] != "thq_125" || procs[j] != "vh_125")
	{
	hist[j]->SetBinErrorOption(TH1::kPoisson);
	for(int bin=1; bin < hist[j]->GetNbinsX()+1; bin++){
//		cout<<"Hist with bin content"<<hist[j]->GetBinContent(bin)<<endl;
		if(hist[j]->GetBinContent(bin)==0) {
//			cout<<"Hist with bin"<<hist[j]->GetBinError(bin)<<endl;
			hist[j]->SetBinError( bin, (hist[j]->GetBinError(bin)+1.0 ));
		}
		if(bin==9){
		q_sum += pow(hist[j]->GetBinError(bin),2); 
		}
//	cout<<j<<"\t"<<bin<<"\t"<<hist[j]->GetBinContent(bin)<<"\t"<<hist[j]->GetBinError(bin)<<endl;
	}
    hist[j]->Scale(DataYield/totalMCYield);
//	hist[j]->Sumw2();
//	totalMC->Sumw2();
	totalMC->Add(hist[j]);
//	totalMC->Sumw2();
//hist[j]->Draw("");
	}
}
//cout<<"q_sum\t"<<sqrt(q_sum)<<endl;
cout<<"GetBinErr of totalMC\t"<<totalMC->GetBinContent(20)<<" #pm "<<totalMC->GetBinError(20)<<endl;

totalMC->SetBinErrorOption(TH1::kPoisson);
for(int bin=1; bin < totalMC->GetNbinsX()+1; bin++){
//	cout<<"Hist with bin content  = "<<totalMC->GetBinContent(bin)<<"\t"<<totalMC->GetBinError(bin)<<endl;
//    cout<<"data with bin content  = "<<hist_Data->GetBinContent(bin)<<"\t"<<hist_Data->GetBinError(bin)<<endl;
//    cout<<"MC Error  = "<<totalMC->GetBinError(bin)/totalMC->GetBinContent(bin)<<endl;
    cout<<"ratio pm error  = "<< hist_Data->GetBinContent(bin)/totalMC->GetBinContent(bin)<<"\t"<<(hist_Data->GetBinContent(bin)/totalMC->GetBinContent(bin))*sqrt(pow(hist_Data->GetBinError(bin)/hist_Data->GetBinContent(bin), 2) + pow(totalMC->GetBinError(bin)/totalMC->GetBinContent(bin), 2))<<endl;
}


int count1=0;
for(int i=0 ; i<file_size; i++)
{
	if(procs[i]=="Data"){leg1->AddEntry(hist_Data, procs_[i].c_str(),"ep"); }
    else if(procs[i]=="ttgg"){hist[i]->SetFillColor(kGreen-2); hist[i]->SetLineColor(kGreen-2); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
    else if(procs[i]=="ttgjets"){ hist[i]->SetFillColor(kGreen-7);hist[i]->SetLineColor(kGreen-7); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
	else if(procs[i]=="DiPhotonJetsBox"){ hist[i]->SetFillColor(kRed+1); hist[i]->SetLineColor(kRed+1); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
	else if(procs[i]=="ttjets"){ hist[i]->SetFillColor(kSpring+10); hist[i]->SetLineColor(kSpring+10); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
	else if(procs[i]=="gjets"){ hist[i]->SetFillColor(kOrange+6); hist[i]->SetLineColor(kOrange+6); hs->Add(hist[i]); leg1->AddEntry(hist[i], procs_[i].c_str(),"f");}
//	else if(procs[i]=="Data"){leg1->AddEntry(hist_Data, procs_[i].c_str(),"ep"); }
	else if(procs[i]==Form("Tprime_%s",T_mass[0].c_str())){leg1->AddEntry(hist_Tprime1, Form("T'(%s) ",T_mass[0].c_str()), "f"); }
    else if(procs[i]==Form("Tprime_%s",T_mass[1].c_str())){leg1->AddEntry(hist_Tprime2, Form("T'(%s) ",T_mass[1].c_str()), "f"); }
    else if(procs[i]=="tth_125"){leg1->AddEntry(hist_HiggsBkg, "SMH","f"); }
    else {count1++; bkg_others->Add(hist[i]); bkg_others->SetFillColor(kViolet); bkg_others->SetLineColor(kViolet);}

}
cout<<"No of Bkg Hist=    "<<count1<<endl;
hs->Add(bkg_others);
leg1->AddEntry(bkg_others, "Others", "f");


//TLatex * tex1 = new TLatex(0.18, 0.89,TString("#bf{CMS} #it{Preliminary}"));
TLatex * tex1 = new TLatex(0.19, 0.89,TString("#scale[1.5]{#bf{CMS}}"));
	 tex1->SetNDC();
     tex1->SetTextAlign(13);
     tex1->SetTextFont(42);
     tex1->SetTextSize(0.04);
     tex1->SetLineWidth(2);

     TLatex * tex2 = new TLatex(0.73, 0.97,TString(Form("#scale[1.2]{%.0f fb^{-1} (13 TeV)}",lumi)));
     tex2->SetNDC();
     tex2->SetTextAlign(13);
     tex2->SetTextFont(42);
     tex2->SetTextSize(0.03);
     tex2->SetLineWidth(2);

TCanvas *c1 = new TCanvas("c1", "c1", 600, 700);
//TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);

TLine *l = new TLine(MVA1_cut,0,MVA1_cut,100);
	l->SetLineWidth(3);
	l->SetLineColor(13);
//	l->SetLineStyle(7);
	l->SetLineStyle(1);

TLine *l_ratio = new TLine(min_score,1,max_score,1);
	l_ratio->SetLineWidth(1);
	l_ratio->SetLineColor(kBlack);
	l_ratio->SetLineStyle(1);


//box->Draw();
//box->SetLineColorAlpha(9, 0.571);
	hist_Data->SetMarkerStyle(20);
    hist_Data->SetMarkerSize(1);
    hist_Data->SetMarkerColor(kBlack);
	hist_Data->SetLineWidth(2);
    hist_Data->SetLineColor(kBlack);

	hist_Tprime1->SetLineWidth(3);
    hist_Tprime1->SetLineColor(kRed);

	hist_Tprime2->SetLineWidth(3);
    hist_Tprime2->SetLineColor(kBlue);

	hist_HiggsBkg->SetLineWidth(3);
    hist_HiggsBkg->SetLineColor(kBlack);
	
    TH1F *hRatio = (TH1F*)hist_Data->Clone("hRatio");
    hRatio->Reset();
    hRatio->Add(hist_Data);
    hRatio->Divide(totalMC);
    hRatio->SetStats(0);
    hRatio->SetMarkerStyle(20);
    hRatio->SetMarkerSize(1);
    hRatio->SetTitle(""); // remove the ratio title
//	hRatio->SetBinErrorOption(TH1::kPoisson);
for(int bin=0; bin < hRatio->GetNbinsX()+1; bin++){
//cout<<"hRatio->GetBinError()\t"<<hRatio->GetBinError(bin)<<endl;
//cout<<"hRatio->GetError()\t"<<(hist_Data->GetBinError(bin)/totalMC->GetBinContent(bin))<<endl;
cout<<"GetBinErr of totalMC\t"<<totalMC->GetBinContent(bin)<<" #pm "<<totalMC->GetBinError(bin)<<endl;
hRatio->SetBinError(bin, (hist_Data->GetBinError(bin)/(totalMC->GetBinContent(bin))));
}
/*      	hRatio->GetYaxis()->SetRangeUser(0,2);
      	hRatio->GetYaxis()->SetTitleOffset(0.4);
      	hRatio->GetYaxis()->SetTitleSize(0.1);
      	hRatio->GetXaxis()->SetTitleSize(0.1);
      	hRatio->GetXaxis()->SetLabelSize(0.11);
	hRatio->GetYaxis()->SetLabelSize(0.09);
      	hRatio->GetYaxis()->SetTitle("Data/MC");
      	hRatio->GetXaxis()->SetTitle("BDT_NonHiggs-bkg");
*/
    TGraphAsymmErrors *g = new TGraphAsymmErrors(hRatio);
	TH1F *hRatio_stat_Err = (TH1F*)totalMC->Clone("hRatio_stat_Err");
	hRatio_stat_Err->SetStats(0);
    hRatio_stat_Err->SetTitle(""); // remove the ratio title
    hRatio_stat_Err->GetYaxis()->SetRangeUser(0.,2.);
    hRatio_stat_Err->GetYaxis()->SetTitleOffset(0.4);
    hRatio_stat_Err->GetYaxis()->SetTitleSize(0.13);
    hRatio_stat_Err->GetXaxis()->SetTitleSize(0.12);
    hRatio_stat_Err->GetXaxis()->SetLabelSize(0.10);
    hRatio_stat_Err->GetYaxis()->SetLabelSize(0.10);
    hRatio_stat_Err->GetYaxis()->SetTitle("Data / MC");
//	hRatio_stat_Err->GetXaxis()->SetTitleOffset(0.8);
    hRatio_stat_Err->GetXaxis()->SetLabelOffset(0.035);
    hRatio_stat_Err->GetYaxis()->SetLabelOffset(0.01);
//  hRatio_stat_Err->GetXaxis()->SetTitle("BDT_NonHiggs-bkg");
	hRatio_stat_Err->GetYaxis()->SetNdivisions(5);

	TGraphAsymmErrors *g_stat_Err = new TGraphAsymmErrors(hRatio_stat_Err);


	for (int ibin=0; ibin<hRatio_stat_Err->GetNbinsX()+1; ibin++)
	{
	hRatio_stat_Err->SetBinContent(ibin, 1);
	double err = hRatio->GetBinContent(ibin)*sqrt(pow((totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)),2)+pow((hist_Data->GetBinError(ibin)/hist_Data->GetBinContent(ibin)),2));
//	double err_MC = hRatio->GetBinContent(ibin) * sqrt( pow( (totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)), 2) );
    double err_MC = sqrt( pow( (totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)), 2) );

	if(! TMath::IsNaN(err_MC)){
	hRatio_stat_Err->SetBinError(ibin, err_MC);
	}
	else hRatio_stat_Err->SetBinError(ibin, 0);

	if(ibin > 0 && ibin < hRatio_stat_Err->GetNbinsX()+1 ){
	gr_Data->SetPoint(ibin-1, hist_Data->GetBinCenter(ibin), hist_Data->GetBinContent(ibin));
	gr_Data->SetPointError(ibin-1, 0, hist_Data->GetBinError(ibin));
	gr_Ratio->SetPoint(ibin-1, hRatio->GetBinCenter(ibin), hRatio->GetBinContent(ibin));
	gr_Ratio->SetPointError(ibin-1, 0, hRatio->GetBinError(ibin));
	}
	}

	hRatio_stat_Err->SetLineColor(kRed);
//	hRatio_stat_Err->SetFillStyle(3001);
	hRatio_stat_Err->SetFillColorAlpha(kRed, 0.25);

	totalMC->SetLineColor(0);
	totalMC->SetFillColorAlpha(kRed, 0.25);
//	totalMC->SetFillStyle(3001);
TBox* box;
if(BDT_Higgs){
	hRatio_stat_Err->GetYaxis()->SetRangeUser(0,2);
  	hRatio_stat_Err->GetXaxis()->SetTitle("BDT-SMH discriminant");
	
	g->GetYaxis()->SetRangeUser(0,2);
  	g->GetXaxis()->SetTitle("BDT-SMH discriminant");
	
    box =new TBox(MVA1_cut, 0, max_score, 0.7*(totalMC->GetMaximum()));
}
else{
	hRatio_stat_Err->GetYaxis()->SetRangeUser(0,2);
    hRatio_stat_Err->GetXaxis()->SetTitle("BDT-NRB");
    box =new TBox(min_score, 0, MVA2_cut, 1.2*(totalMC->GetMaximum()));
	}
	box->SetFillColorAlpha(kBlack, 0.15);
	gr_Data->SetMarkerStyle(20);
    gr_Data->SetMarkerSize(1);
    gr_Data->SetMarkerColor(kBlack);
    gr_Data->SetLineWidth(2);
    gr_Data->SetLineColor(kBlack);

	gr_Ratio->SetMarkerStyle(20);
    gr_Ratio->SetMarkerSize(1);
    gr_Ratio->SetMarkerColor(kBlack);
    gr_Ratio->SetLineWidth(2);
    gr_Ratio->SetLineColor(kBlack);
	gr_Ratio->GetXaxis()->SetRangeUser(min_score, max_score);

	leg1->AddEntry(totalMC, "Stat. Unc." ,"f");
	leg1->AddEntry((TObject*)0, "", "");
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);

TGraphAsymmErrors* ratioEr =new TGraphAsymmErrors(hist_Data, totalMC, "pois");
	ratioEr->SetLineColor(kBlack);
	ratioEr->SetFillColor(kBlack);
	ratioEr->SetFillStyle(3001);
/*
        hs->GetYaxis()->SetTitle(Form("Events/(%0.3f)",bin_width));
        hs->GetYaxis()->SetTitleOffset(0.9);
        hs->GetYaxis()->SetTitleSize(0.06);
        hs->GetYaxis()->SetLabelSize(0.04);
*/
//===============================================================================
   const double alpha = 1 - 0.6827;
  
//    TGraphAsymmErrors *g = new TGraphAsymmErrors(hRatio);
    g->SetMarkerSize(0.5);
    g->SetMarkerStyle (20);

	for(int bin=1; bin < hRatio->GetNbinsX()+1; bin++){


		double err_low=0;
		double err_high=0;

	    double N = hist_Data->GetBinContent(bin);;
    	err_low = (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    	err_low = N-err_low;
    	err_high = ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) ;
    	err_high = err_high - N;

		double err_low_data = hist_Data->GetBinErrorLow(bin);
		double err_low_MC 	= totalMC->GetBinErrorLow(bin);	

        double err_high_data = hist_Data->GetBinErrorUp(bin);
        double err_high_MC   = totalMC->GetBinErrorUp(bin);   

//		double err_low 	= hRatio->GetBinContent(bin)*sqrt(pow((err_low_data/hist_Data->GetBinContent(bin)), 2) + pow((err_low_MC/totalMC->GetBinContent(bin)),2));
//        double err_high 	= hRatio->GetBinContent(bin)*sqrt(pow((err_high_data/hist_Data->GetBinContent(bin)),2) + pow((err_high_MC/totalMC->GetBinContent(bin)),2));

		err_low 	= err_low_data/totalMC->GetBinContent(bin);
        err_high     = err_high_data/totalMC->GetBinContent(bin);



cout<<"err_low\t"<<err_low<<endl;
cout<<"err_high\t"<<err_high<<endl;

		g->SetPointEYlow(bin-1, err_low);
		g->SetPointEYhigh(bin-1, err_high);
        g->SetPointEXlow(bin-1, 0);
        g->SetPointEXhigh(bin-1, 0);
//		hRatio->SetPointEYlow(err_low);
//		hRatio->SetPointEYhigh(err_high);
	}

//   	g->SetStats(0);
    g->SetTitle("");
    g->GetYaxis()->SetRangeUser(0.,2.);
    g->GetYaxis()->SetTitleOffset(0.4);
    g->GetYaxis()->SetTitleSize(0.13);
    g->GetXaxis()->SetTitleSize(0.12);
    g->GetXaxis()->SetLabelSize(0.10);
    g->GetYaxis()->SetLabelSize(0.10);
    g->GetYaxis()->SetTitle("Data / MC");
    g->GetXaxis()->SetLabelOffset(0.035);
    g->GetYaxis()->SetLabelOffset(0.01);
    g->GetYaxis()->SetNdivisions(5);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);	
//=================================================================================
c1->cd();
TPad *pad1 = new TPad("pad1","pad1",0,0.3,1.0,1.0);
	pad1->SetTopMargin(0.075);
	pad1->SetBottomMargin(0);
	pad1->SetLeftMargin(0.120);
	pad1->SetRightMargin(0.070);
	pad1->SetLogy();
	pad1->SetTickx();
	pad1->SetTicky();
	pad1->Draw();
	pad1->cd();
	pad1->SetLeftMargin(0.15);
//	pad1->SetTopMargin(0.1);
	pad1->SetBottomMargin(0.01);	

    hs->Draw("hist");
    hs->GetYaxis()->SetTitle(Form("Events/(%0.3f)",bin_width));
    hs->GetYaxis()->SetTitleOffset(0.9);
    hs->GetYaxis()->SetTitleSize(0.06);
    hs->GetYaxis()->SetLabelSize(0.04);
    totalMC->Draw("E2 SAME");
	if(BDT_NonHiggs){
    	 hs->SetMaximum(5*hist_Data->GetMaximum());
	}
	else{
		hs->SetMaximum(1000*hist_Data->GetMaximum());
		hs->SetMinimum(10e-4);
	}		
    hist_Data->Draw("E0 x0 SAME");
//	gr_Data->Draw("P");
	hist_Tprime1->Draw("hist SAME");
    hist_Tprime2->Draw("hist SAME");
    hist_HiggsBkg->Draw("hist SAME");
//        l->Draw("SAME");
    tex1->Draw();
	tex2->Draw();
//	box->Draw();
	leg1->Draw("SAME");
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
	pad2->SetTopMargin(0.1);
	pad2->SetLeftMargin(0.120);
	pad2->SetRightMargin(0.070);
	pad2->SetBottomMargin(0.35);
//	pad2->SetGridy();
//	pad2->SetGridx();
	pad2->Draw();
	pad2->cd();
	pad2->SetLeftMargin(0.15);

	g->GetXaxis()->SetRangeUser(0,1);
//    g->Draw("PZ[");
//    g->SetRangeUser(0,2);
//	gr_Ratio->Draw("AP");
//        ratioEr->Draw("E2");
//	gStyle->SetErrorX(1);
//	hRatio_stat_Err->Draw("SAME E2");
	hRatio_stat_Err->Draw("E2");
    g->Draw("SAME PZ[");
//	hRatio_stat_Err->Draw("E2");
//	g_stat_Err->Draw("a2");
//	gStyle->SetErrorX(0);
//	hRatio->Draw("SAME E0 x0");
//	gr_Ratio->Draw("P");
	l_ratio->Draw();

/*writeExtraText = true;       // if extra text
extraText  = "    Preliminary";
lumi_13TeV = "138 fb^{-1}";
CMS_lumi( c1, 4, 0);
*/

cout<<"[2]hist_data->GetBinError(9) "<<hist_Data->GetBinError(9)<<endl;

TString outfile_path="/eos/user/p/prsaha/www/Tprime_analysis/UL/";
c1->SaveAs(outfile_path + Form("/%s_Score_Run%i_unblinded.root",method.c_str(),year));
c1->SaveAs(outfile_path + Form("%s_Score_Run%i_unblinded.png",method.c_str(),year));
c1->SaveAs(outfile_path + Form("%s_Score_Run%i_unblinded.pdf",method.c_str(),year));

cout<<"[2]hist_data->GetBinError(9) "<<hist_Data->GetBinErrorLow(9)<<endl;

return 0;
}

int main(int argc, char** argv)
{
int year;
bool BDT_Higgs;
bool BDT_NonHiggs;
return MVA_distribution( year, BDT_Higgs, BDT_NonHiggs );
}


