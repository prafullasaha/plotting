#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <TLatex.h>
#include <THStack.h>
#include <TTree.h>

#include <TROOT.h>

//#include "tdrstyle.C"

using namespace std;
//setTDRStyle();

//----------------------------------------------------------------------

/** information about one type of process */
class ProcInfo
{
public:

  /** label of process */
  TString label;

  /** input file (within global inputDir) */  
  TString inputFname;

  /** first part of tree name within the tagsDumper/trees
      directory inside the ROOT input file */
  TString treePrefix;

  int lineColor;

  int fillColor;

  bool isData;

};

//----------------------------------------------------------------------

/** class representing the event yields for a plot (by category or combined) */
struct EventYieldTable
{
  /** first index is the category name,
      second index is the process name,
      value is the number of normalized events */
  map<string, map<string, double> > normalizedEvents;

  /** same as normalizedEvents but for number of MC events */
  map<string, map<string, unsigned> > mcEvents;
};

//----------------------------------------------------------------------

/** for keeping plots and number of events for a plot to be
    written out later */
struct PlotResult
{
  EventYieldTable eventYield;

  /** maps from category to plot (in SVG or PNG format) */
  map<string, vector<char> > plots;
};

//----------------------------------------------------------------------

/** possible encoded characters */
static const char *base64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64encodeHelper(unsigned char *inbuf, unsigned char *outbuf, unsigned length)
{
  outbuf[0] = (unsigned char) base64chars[ (int)(inbuf[0] >> 2) ];
  outbuf[1] = (unsigned char) base64chars[ (int)(((inbuf[0] & 0x03) << 4) | ((inbuf[1] & 0xf0) >> 4)) ];

  if (length > 1)
    outbuf[2] = (unsigned char) base64chars[ (int)(((inbuf[1] & 0x0f) << 2) | ((inbuf[2] & 0xc0) >> 6)) ];
  else
    outbuf[2] = (unsigned char) '=';

  if (length > 2)
    outbuf[3] = (unsigned char) base64chars[ (int)(inbuf[2] & 0x3f) ];
  else
    outbuf[3] = '=';
}

//----------------------------------------

string base64encode(const vector<char> &input)
{
  char inbuf[3], outbuf[5];
  outbuf[4] = 0;

  string retval;

  for (unsigned start = 0; start < input.size(); start += 3)
    {
      unsigned j;
      for (j = 0; j < 3 && start + j < input.size(); ++j)
	inbuf[j] = input[start + j];
      
      // clear the rest of the buffer
      for (unsigned k = j; k < 3; ++k)
	inbuf[k] = 0;
      
      base64encodeHelper((unsigned char *)inbuf, (unsigned char *)outbuf, j);

      retval += outbuf;

    }

  return retval;
}



//--------------------remove negative weight
TH1F *removeNegativeBins(TH1F* h){
  for(int i=0;i<h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i) < 0.0) {
	h->SetBinContent(i,0.0);
      }
    }
  return h;
}



//----------------------------------------------------------------------

class Plotter
{
  std::vector<std::string> allCategories;

  /** directory where the input ntuple files are */
  const TString inputDir;

  /** information about the processes to plot */
  std::vector<ProcInfo> processes;

  /** integrated luminosity in /fb, assuming the MC
      weights were normalized to 1/fb */
  double lumi;

  /** maps from category name to canvas. We keep only
      one canvas per category open. Not sure what happens
      though when the user closes the canvas with the mouse... */
  std::map<TString, TCanvas *> canvases;

  /** add over- and underflow to last/first bin */
  bool underOverflowBin = false;

  /** if true, the plots are stored for later writing them
      out in HTML format */
  bool recordForHTML = false;

  /** name of temporary working directory for saving plots for the HTML report */
  string tmpWorkingDir;

  /** for keeping plots to be written to a HTML file */
  vector<PlotResult> plotResultsForHTML;

  /** cuts to be applied for data */
  vector<string> dataOnlyCuts;

public:
  /** @param lumi is the luminosity in /fb */
  Plotter(const std::string &inputDir_,
	  double lumi_) : 
    inputDir(inputDir_),
    lumi(lumi_)
  {
//    allCategories.push_back("WHLeptonicTag");
//    allCategories.push_back("ZHLeptonicTag");
//    allCategories.push_back("VHLeptonicLooseTag");
//    allCategories.push_back("VHMetTag");
//    allCategories.push_back("VHHadronicTag");
//    allCategories.push_back("UntaggedTag_0");
//    allCategories.push_back("UntaggedTag_1");
//    allCategories.push_back("UntaggedTag_2");
//    allCategories.push_back("UntaggedTag_3");
    allCategories.push_back("THQLeptonicTag");
    
  }

  //----------------------------------------

  /** @param label is the label used for the legend
      @param inputFname is the name of the input file relative
             to the inputDir given in the constructor
      @param treePrefix is first part of the tree name
             tagsDumper/trees directory within the input ROOT file 
  */
  void addMC(const std::string &label, 
	     const std::string &inputFname,
	     const std::string &treePrefix,
	     int lineColor = -1,
	     int fillColor = -1
	     )
  {
    ProcInfo proc;
    proc.isData = false;
    proc.label = label;
    proc.inputFname = inputFname;
    proc.lineColor = lineColor;
    proc.fillColor = fillColor;
    proc.treePrefix = treePrefix;
    
    processes.push_back(proc);
  }

  //----------------------------------------

  /** @param label is the label used for the legend
      @param inputFname is the name of the input file relative
             to the inputDir given in the constructor
      @param treePrefix is first part of the tree name
             tagsDumper/trees directory within the input ROOT file 
  */
  void addData(const std::string &label, 
	       const std::string &inputFname,
	       const std::string &treePrefix
	       )
  {
    ProcInfo proc;
    proc.isData = true;
    proc.label = label;
    proc.inputFname = inputFname;
    proc.lineColor = -1;
    proc.fillColor = -1;

    proc.treePrefix = treePrefix;

    processes.push_back(proc);
  }

  //----------------------------------------
protected:
  TString makeCut(bool isData)
  {
    vector<string> parts;
    // apply to MC as well
    //if (isData)
    //{
    for (unsigned i = 0; i < dataOnlyCuts.size(); ++i)
      parts.push_back(dataOnlyCuts[i]);
    //}
    
    // combine the expressions
    string result = "";

    for (unsigned i = 0; i < parts.size(); ++i)
      {
	if (i > 0)
	  result += " && ";
	
	result += "(" + parts[i] + ")";
      }

    // apply MC weight
    if (! isData)
      {
	if (result.size() > 0)
	  result = "weight*(" + result + ")"; // added puweight in the "weigth" in flashgg
	else
	  result = "weight"; // added puweight in the "weight" in flashgg
      }

    return result.c_str();
  }
  //----------------------------------------

public:
  void plotSingleCat(TString mode,
		     TString observable, 
			 TString observable_title,
		     int     nBins, 
		     double  observableMin, 
		     double  observableMax, 
		     bool    drawdata, 
		     bool    log = false, 
		     bool    ratio = false,
		     PlotResult *plotResult = NULL
		     )
  {
    //  gROOT->ProcessLine(".L tdrstyle.C");
    //setTDRStyle();
    gStyle->SetOptStat(0);
    
    
    /*
      c1 = new TCanvas();
      const float xpad[2] = {0.,1};
      const float ypad[4] = {0.,0.3,0.3,1.0};
      if(ratio){
      c1->Divide(1,2);
      c1->cd(1);
      gPad->SetPad(xpad[0],ypad[2],xpad[1],ypad[3]);
      gPad->SetLogy(log);
      }
    */

    TString mcCut = makeCut(false);
    TString dataCut = makeCut(true);

    cout << "prepare mcCut: " << mcCut << endl;
    cout << "prepare dataCut: " << dataCut << endl;
    
    cout.precision(3);

    THStack *hs1 = new THStack("hs1","VH distribution");
    THStack *hs2 = new THStack("hs2","");
   	TH1F *hSignal; 
    double totalMCYield = 0.0;
    double dataYield = 0.0;
    bool normalized = true; // false

//    TH1F *dataHisto = NULL;
	TH1F *dataHisto;
//    TH1F *ratioPlot= NULL;
    vector<TH1F*> histos;

    for (unsigned procIndex = 0; procIndex < processes.size(); ++procIndex)
    {
      ProcInfo &process = processes[procIndex];

      if (! drawdata && process.isData)
	{
	  // skip plotting data
	  histos.push_back(NULL);
	  continue;
	}

      TString inputFname = inputDir + "/" + process.inputFname;
      TFile* f1 = TFile::Open(inputFname);

      if(f1 == NULL)
	{
	  cerr << "error opening file " << (inputDir + process.inputFname) << endl;
	  return;
	}

      if(f1->IsZombie())
	{
	  cerr << "file " << (inputDir + process.inputFname) << " is a zombie" << endl;
	  f1->Close(); 
	  return;
	}

      gROOT->cd();

      TH1F *histo = new TH1F(process.label,process.label,nBins,observableMin,observableMax);
      histos.push_back(histo);
/*
      if (process.isData)
	{
	  // there should only be one data process
	  assert(dataHisto == NULL);

	  dataHisto = histo;
	}
*/
     //----------

      TString treeName = "tagsDumper/trees/" + process.treePrefix + "_13TeV_"+mode;
      
      TTree *tree = ((TTree*)f1->Get(treeName));

      if (tree == NULL)
	{
	  cout << "WARNING: could not find tree " << treeName << " in file " << inputFname << endl;
	  return;
	}



      //---------
      // debug1 gkole
      //---------

//      cout << "dataCut before thisCut decided:  " << dataCut << endl;
//      cout << "mcCut   before thisCut decided:  " << mcCut << endl;
/*ps      if (observable.Contains("mass")){
	dataCut = "((diphoMVA > -0.5) && (mass < 115 || mass > 135))";

        if (process.label == "QCD" || process.label == "GJet"){
          mcCut = "weight*((diphoMVA > -0.5) && (mass < 115 || mass > 135) && (genmatch1 == 1 && hasGenmatch1)*(genmatch2 == 1 && hasGenmatch2)==0 )";
        }else{
          mcCut = "weight*((diphoMVA > -0.5) && (mass < 115 || mass > 135))";
        }

      } // if mass present
      else
        {*/
//		dataCut = "(dipho_leadIDMVA > -0.9 && (dipho_mass < 115 || dipho_mass > 135))";
		dataCut = "(dipho_leadIDMVA > -0.9 )";
/*          if (process.label == "QCD" || process.label == "GJet"){
            //mcCut = "weight*((diphoMVA > -0.5) && (genmatch1 == 1 && hasGenmatch1)*(genmatch2 == 1 && hasGenmatch2)==0 )";
          }else{
cout<<"Hello, I am here"<<endl;
*/  
		if(process.label == "TprimeM700"){
		mcCut = "weight*((dipho_leadIDMVA > -0.9) && weight>0)"; // for thq
		}
//		else mcCut = "weight*((dipho_leadIDMVA > -0.9) && (dipho_mass < 115 || dipho_mass > 135) && weight>0)";
		else mcCut = "weight*((dipho_leadIDMVA > -0.9) && weight>0)";
/*          }

        } // else of mass else loop 
*/

	TString *thisCut;
	if (process.isData)
//		thisCut = &dataCut;
		thisCut = &dataCut;
	else
		thisCut = &mcCut; // changed to datacut gkole
      

      cout << "dataCut after thisCut decided:  " << dataCut << endl;
      cout << "mcCut   after thisCut decided:  " << mcCut << endl;
      
      //----------
      // modify expression to add under/overflow bins if requested
      //----------
	TString expr;
	if (underOverflowBin)
	{
	// find center of first and last bins
	double binWidth = (observableMax - observableMin) / nBins;
	
	double firstBinCenter = observableMin + 0.5 * binWidth;
	double lastBinCenter  = observableMax - 0.5 * binWidth;

	expr = Form("TMath::Min(%f, TMath::Max(%f, %s))",
		    lastBinCenter,
		    firstBinCenter,
		    observable.Data());
	}
	else
	expr = observable;

      //----------

    tree->Project(process.label,expr,*thisCut);

      // assume the input weights were normalized to 1/fb
//      if (! process.isData)
//        histo->Scale(lumi);

    double yield = histo->GetSumOfWeights();
    if (process.isData)
    {
    // there should only be one data process
    assert(dataHisto == NULL);
    dataHisto = histo;
cout<<"dataHisto---------------->"<<dataHisto->Integral()<<endl;
	dataYield=dataHisto->Integral();
	dataHisto->SetBinErrorOption(TH1::kPoisson);
    }     
      
    cout << process.label << " yield: " << yield << endl;

	if(process.label == "TprimeM700"){
	hSignal = histo;
	cout<<"Inside the loop------------------------------------------------------------------"<<hSignal->Integral()<<endl;
	//hSignal->Scale(200);
	hSignal->Draw();
	}

      // keep event yield if HTML report enabled
	if (plotResult != NULL)
	{
	  plotResult->eventYield.normalizedEvents[(const char*)mode][(const char *)process.label] = yield;
	  plotResult->eventYield.mcEvents[(const char *)mode][(const char *)process.label] = histo->GetEntries();
	}

      // ---------
      // normalized to data integral
      // ---------
      
      //      bool normalized = true;

	if (! process.isData && normalized)
	{
	  totalMCYield = totalMCYield + yield;
	  cout << "totalMCYield:  " << totalMCYield << endl;
	}
      //----------
      // apply histogram style
      //----------

	if (process.isData)
	{
	  histo->SetLineColor(kBlack);
	  histo->SetMarkerStyle(20);
	  histo->GetYaxis()->SetTitleOffset(1);
      histo->GetYaxis()->SetTitleSize(0.05);
      histo->GetYaxis()->SetLabelSize(0.05);
	  histo->GetYaxis()->SetTitle("Events");
	}
	else
	{
	if (process.lineColor != -1)
	  if (process.lineColor != -1)
	    histo->SetLineColor(process.lineColor);
	    histo->GetYaxis()->SetTitleOffset(1);
        histo->GetYaxis()->SetTitleSize(0.05);
        histo->GetYaxis()->SetLabelSize(0.05);
        histo->GetYaxis()->SetTitle("Events");


	  if (process.fillColor != -1)
	    histo->SetFillColor(process.fillColor);
	    histo->SetLineColor(process.lineColor);
        histo->GetYaxis()->SetTitleOffset(1);
        histo->GetYaxis()->SetTitleSize(0.05);
        histo->GetYaxis()->SetLabelSize(0.05);
        histo->GetYaxis()->SetTitle("Events");

	}

      // add to THStack
	if (! process.isData && process.label != "TprimeM700")
		hs1->Add(histo);

    } // loop over processes
    


    // define totalMC histogram
    TH1F *totalMC = (TH1F*)dataHisto->Clone("totalMC");
    totalMC->Reset();
    //----------
    // change stack
    //----------
    hs1->Print();
    
    TList *hists = hs1->GetHists();
    //    TH1F *sum = new TH1F("sum","sum of histograms",100,-4,4);
    TIter next(hists);
    TH1F *tmphist;
    while ((tmphist =(TH1F*)next())) {
    if(normalized){
	cout << "Scaling " << tmphist->GetName() << endl;
	cout << "dataYield:  " << dataYield << endl;
	cout << "Scale fector" << dataYield/totalMCYield<<endl;

	tmphist->Scale(dataYield/totalMCYield);
    }

    // avoid negative weight
      
    TH1F *tmphist_2 = (TH1F*) removeNegativeBins(tmphist);
      
    hs2->Add(tmphist_2);

    for(int bin=1; bin < tmphist_2->GetNbinsX()+1; bin++){
        cout<<"Hist with bin content"<<tmphist_2->GetBinContent(bin)<<endl;
        if(tmphist_2->GetBinContent(bin)==0) {
            cout<<"Hist with bin"<<tmphist_2->GetBinError(bin)<<endl;
            tmphist_2->SetBinError( bin, (tmphist_2->GetBinError(bin)+1.0 ));
        }
    }

    totalMC->Add(tmphist_2); //  get totalMC histogram  
    //sum->Add(hist);
    }
    totalMC->SetBinErrorOption(TH1::kPoisson);
    cout << "hs2 print:  " << endl;
    hs2->Print();
    
    //--end

    //----------
    // find canvas corresponding to this category
    //----------
    
    TCanvas *canvas = NULL;

    if (canvases.find(mode) == canvases.end())
      {
	canvas = new TCanvas;
	canvases[mode] = canvas;
      }
    else
      canvas = canvases[mode];


    // new canvas to work on
    canvas->SetCanvasSize(600, 700);
    canvas->cd();

    canvas->SetRightMargin(0.04);
    canvas->SetLeftMargin(1);
    canvas->SetRightMargin(0.2);

    // define TPad
   if(ratio){
      cout << "ratio is open" << endl;
      //TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1.0);
      TPad *pad1 = new TPad("pad1","pad1",0,0.3,1.0,1.0);
      pad1->SetLogy();
      pad1->SetTickx();
      pad1->SetTicky();
      pad1->SetBottomMargin(0);
      pad1->Draw();
      pad1->cd();

      // first draw the data
   if(dataHisto != NULL)
	{
//	  dataHisto->Scale(1/dataHisto->Integral());
//	  double dataMax = dataHisto->GetMaximum() + sqrt(dataHisto->GetMaximum());
	  double dataMax = dataHisto->GetMaximum();
	  double theMax = 100 * max(dataMax, hs2->GetMaximum()); // new stack
//	  dataHisto->SetMaximum(1.2*dataMax);
	  hs2->SetMaximum(theMax); // new stack
	  hs2->SetMinimum(10e-4);
	  dataHisto->Draw("E1");
	}

      // draw MC(care full about hs2)***
      hs2->Draw("hist");
      hs2->Draw("axissame");
	  totalMC->Draw("E2 SAME");
      //hs2->SetTitle(observable + " " + mode);
      hs2->GetYaxis()->SetTitle("Events");
      hs2->GetYaxis()->SetTitleOffset(1);
        hs2->GetYaxis()->SetTitleSize(0.05);
        hs2->GetYaxis()->SetLabelSize(0.05);
      hs2->GetXaxis()->SetTitle(observable_title);
      hs2->GetXaxis()->SetNdivisions(5, "X");

    totalMC->SetLineColor(0);
	totalMC->SetFillStyle(3244);
    totalMC->SetFillColorAlpha(kRed, 0.25);
	totalMC->SetMarkerSize(0);

//Signal MC Histogram
	hSignal->Draw("hist same");     
	hSignal->SetLineWidth(3);
	hSignal->SetLineColor(kRed);
	hSignal->SetFillColor(0);
	hSignal->SetTitle("");
//----
    if(dataHisto != NULL) 
	{
	  //dataHisto->GetXaxis()->SetTitle(observable + " " + mode);
	  dataHisto->GetYaxis()->SetTitleFont(42);
	  dataHisto->GetYaxis()->SetTitleOffset(1.);
	  dataHisto->GetXaxis()->SetTitleFont(42);
      dataHisto->GetXaxis()->SetTitleSize(0.12);
      dataHisto->GetXaxis()->SetLabelSize(0.11);
	  dataHisto->GetXaxis()->SetTitleOffset(0.8);
	  dataHisto->SetLineWidth(3);
	  dataHisto->SetLineStyle(1);
	  dataHisto->Draw("E1 x0 same"); 
	  dataHisto->Draw("axissame");
	  
	}                         


      canvas->cd(); // go back to main canvas

      TPad *pad2 = new TPad("pad2","pad2",0,0.0,1.0,0.3);
      pad2->SetTopMargin(0.1);
      pad2->SetBottomMargin(0.3);
      pad2->SetGridy();
      pad2->SetGridx();
      pad2->Draw();
      pad2->cd(); //pad2 becomes the current pad

      // define ratio plots
//      TH1F *ratioPlot= new TH1F("ratioPlot","ratioPlot",nBins,observableMin,observableMax);
//      ratioPlot->GetYaxis()->SetRange(-5,5); 
      TH1F *hRatio = (TH1F*)dataHisto->Clone("hRatio");
      hRatio->Reset();
      hRatio->Add(dataHisto);
      if(totalMC->Integral() > 0)
	  hRatio->Divide(totalMC);
	  hRatio->SetBinErrorOption(TH1::kPoisson);

	TH1F *hRatio_stat_Err = (TH1F*)totalMC->Clone("hRatio_stat_Err");
    hRatio_stat_Err->SetStats(0);
    hRatio_stat_Err->SetTitle(""); // remove the ratio title
    hRatio_stat_Err->GetYaxis()->SetRangeUser(0.,2.);
    hRatio_stat_Err->GetYaxis()->SetTitleOffset(0.4);
    hRatio_stat_Err->GetYaxis()->SetTitleSize(0.12);
    hRatio_stat_Err->GetXaxis()->SetTitleSize(0.12);
    hRatio_stat_Err->GetXaxis()->SetLabelSize(0.11);
    hRatio_stat_Err->GetYaxis()->SetLabelSize(0.09);
    hRatio_stat_Err->GetYaxis()->SetTitle("Data/MC");
//	hRatio_stat_Err->GetXaxis()->SetLabelOffset(0.035);
//    hRatio_stat_Err->GetYaxis()->SetLabelOffset(0.01);
	hRatio_stat_Err->GetXaxis()->SetTitleOffset(0.8);
	hRatio_stat_Err->GetYaxis()->SetNdivisions(6);
	hRatio_stat_Err->GetXaxis()->SetTitle(observable_title);
	hRatio_stat_Err->SetMarkerSize(0);
	for (int ibin=1; ibin<hRatio_stat_Err->GetNbinsX()+1; ibin++)
    {
    	hRatio_stat_Err->SetBinContent(ibin, 1);
    	double err = hRatio->GetBinContent(ibin)*sqrt(pow((totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)),2)+pow((dataHisto->GetBinError(ibin)/dataHisto->GetBinContent(ibin)),2));
    	double err_MC = sqrt(pow((totalMC->GetBinError(ibin)/totalMC->GetBinContent(ibin)),2));
		if(! TMath::IsNaN(err_MC) && ! isinf(err_MC) && !(totalMC->GetBinContent(ibin)==0)){ 
    	hRatio_stat_Err->SetBinError(ibin, err_MC);
		}
		else hRatio_stat_Err->SetBinError(ibin, 0);
    }

    hRatio_stat_Err->SetLineColor(kRed);
    hRatio_stat_Err->SetFillColorAlpha(kRed, 0.25);

      hRatio->SetStats(0);
      hRatio->SetMarkerStyle(20);
      hRatio->SetMarkerSize(1);
/*      hRatio->SetTitle(""); // remove the ratio title
      hRatio->GetYaxis()->SetRangeUser(0,2);
      hRatio->GetYaxis()->SetTitleOffset(0.4);
      hRatio->GetYaxis()->SetTitleSize(0.12);
      hRatio->GetXaxis()->SetTitleSize(0.12);
      hRatio->GetXaxis()->SetLabelSize(0.11);
      hRatio->GetYaxis()->SetLabelSize(0.09);
      hRatio->GetYaxis()->SetTitle("Data/Bkg");
      hRatio->GetXaxis()->SetTitle(observable_title);
      hRatio->GetXaxis()->SetTitleOffset(0.8);
      hRatio->GetYaxis()->SetNdivisions(6);
*/
	  hRatio_stat_Err->Draw("E2");
      hRatio->Draw("SAME E1 x0");

    }

    
    canvas->cd();

    
//    TLegend * leg = new TLegend(0.81,0.27,0.93,0.90);
//    leg = new TLegend(0.81,0.27,0.93,0.90);
    TLegend *leg = new TLegend(0.2, 0.8, 0.91, 0.91, "");
    leg->SetNColumns(4);
    leg->SetTextSize(0.037);
    leg->SetBorderSize(0);
    leg->SetLineStyle(0);
    leg->SetTextSize(0.027);
    leg->SetFillStyle(0);
    leg->SetFillColor(0);

    if (dataHisto != NULL)
      leg->AddEntry(dataHisto,TString("Data")/* + Form(" (%d)", int(dataHisto->GetEntries() + 0.5))*/,"ep");

    for (unsigned procIndex = 0; procIndex < processes.size(); ++procIndex)
    {
      ProcInfo &process = processes[procIndex];
      if (process.isData)
	continue;

      if (histos[procIndex] != NULL)
	leg->AddEntry(histos[procIndex], process.label/* + Form(" (%.1f)", histos[procIndex]->GetSum()) ,"f"*/);
    }
	leg->AddEntry(totalMC, "Stat. Unc." ,"f");
    leg->Draw();

    // header
    if (true)
      {
/*	TLatex * tex = new TLatex(0.10, 0.97,TString("CMS Preliminary    ") + 
				  Form("%.1f", lumi) + " fb^{-1} (13 TeV)");
	
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(42);
	tex->SetTextSize(0.045);
	tex->SetLineWidth(2);

	tex->Draw();
*/
        TLatex * tex1 = new TLatex(0.10, 0.97, TString("#bf{CMS} #it{Preliminary}"));
//        TLatex * tex1 = new TLatex(0.10, 0.97,TString("#bf{CMS} #it{work in progress}"));
        tex1->SetNDC();
        tex1->SetTextAlign(13);
        tex1->SetTextFont(42);
        tex1->SetTextSize(0.04);
        tex1->SetLineWidth(2);

        TLatex * tex2 = new TLatex(0.70, 0.97,TString(Form("%.0f fb^{-1} (13 TeV)",lumi)));
        tex2->SetNDC();
        tex2->SetTextAlign(13);
        tex2->SetTextFont(42);
        tex2->SetTextSize(0.03);
        tex2->SetLineWidth(2);

	tex1->Draw();
	tex2->Draw();
      }
TString output_dir= "/eos/user/p/prsaha/www/Tprime_analysis/DataVsMC/UL/RunII_unblinded/";   
    canvas->SaveAs(output_dir + mode + "_" + observable_title + ".pdf");
    canvas->SaveAs(output_dir + mode + "_" + observable_title + ".png");
//    canvas->SaveAs(mode + "_" + observable + ".gif");
    //----------
    // keep information for HTML report if enabled
    //----------

    if (plotResult != NULL)
    {
      // save plot in .png format

      string fname = tmpWorkingDir + "/plot.png";
      gPad->SaveAs(fname.c_str());

      // read the data 
      ifstream infile(fname, std::ios::binary);

      // copy the entire file into memory
      std::vector<char> buffer((
				istreambuf_iterator<char>(infile)), 
			       (istreambuf_iterator<char>()));
      
      // copy again...
      plotResult->plots[(const char *)mode] = buffer;
      
      unlink(fname.c_str());
      
    } // if (plotResult != NULL)

  }

  //----------------------------------------

  /** makes plots for all categories

      @param observable the expression to draw
  */
  void plot(const std::string &observable,
		const std::string &observable_title,
	    int nbins,
	    double observableMin,
	    double observableMax,
	    bool drawdata = true,
	    bool log = false
	    )
  {
    PlotResult plotRes, *plotResPointer;

    if (recordForHTML)
      {
	plotResultsForHTML.push_back(PlotResult());
	plotResPointer = &(plotResultsForHTML.back());
      }
    else
      plotResPointer = NULL;

    for (unsigned cat = 0; cat < allCategories.size(); ++cat)
      {
	plotSingleCat(allCategories[cat],
		      observable,
			  observable_title,
		      nbins,
		      observableMin,
		      observableMax,
		      drawdata,
		      log,
		      true, // ratio
		      plotResPointer
		      );
      }

  }

  //----------------------------------------

  void startHTML()
  {
    recordForHTML = true;

    // create a temporary working directory for saving plots
    char buf[1000];

    // note must copy this every time this function is called
    strcpy(buf, "/tmp/plotter.XXXXXX");
    tmpWorkingDir = mkdtemp(buf);
    
  }

  //----------------------------------------

  /** write a report with the plots to a file in HTML format.
      After writing, clears the data in memory and disables
      HTML mode. */
  void writeHTML(const string &fname)
  {
    ofstream out(fname);

    out << "<html>" << endl;

    // CSS styles
    out << "<style>" << endl;
    out << "table {" << endl;
    out << "    border-collapse: collapse;" << endl;
    out << "}" << endl;
    out << "table, th, td {" << endl;
    out << "   border: 1px solid black;" << endl;
    out << "}" << endl;
    out << "th, td {" << endl;
    out << "    padding: 4px;" << endl;
    out << "}" << endl;
    out << "tr:nth-child(even){background-color: #f2f2f2}" << endl;

    out << ".mc-events {" << endl;
    out << "  font-size: 75%;" << endl;
    out << "  color: #AAAAAA;" << endl;
    out << "}" << endl;

    out << "</style>" << endl;

    out << "<body>" << endl;

    // TODO: add TOC
    for (unsigned resultIndex = 0; resultIndex < plotResultsForHTML.size(); ++resultIndex)
      {
	if (resultIndex > 0)
	  out << "<hr/>" << endl;

	const PlotResult &result = plotResultsForHTML[resultIndex];

	// write plots out
	for (unsigned catIndex = 0; catIndex < allCategories.size(); ++catIndex)
	  {
	    const string &catname = allCategories[catIndex];

	    // out << "<h2>cat " << catname << "<h2><br/>" << endl;
	    out << "<img src=\"data:image/png;base64," << base64encode(result.plots.at(catname)) << "\"/>" << endl;
	    // out << "</br>" << endl;
	    
	  } // loop over categories

	// out << "</br>" << endl;

	//----------
	// print event yields table
	//----------


	out << "<table>" << endl;
	out << "<caption>expected/observed events</caption>" << endl;
	out << "<tr><th>process</th>";
	for (unsigned catIndex = 0; catIndex < allCategories.size(); ++catIndex)
	  {
	    const string &catname = allCategories[catIndex];
	    
	    out << "<th>" << catname << "</th>";
	  }

	out << "</tr>" << endl;

	// loop over physics processes
	// note that e.g. we may have disabled data 
	for (unsigned procIndex = 0; procIndex < processes.size(); ++procIndex)
	{
	  const ProcInfo &proc = processes[procIndex];
	  out << "<tr><td>" << proc.label << "</td>";

	  for (unsigned catIndex = 0; catIndex < allCategories.size(); ++catIndex)
	  {
	    const string &catname = allCategories[catIndex];

	    out << "<td>";

	    const map<string, double> &thisCatYields = result.eventYield.normalizedEvents.at(catname);

	    map<string, double>::const_iterator it = thisCatYields.find((const char *)proc.label);

	    // check if we have event yields for this process
	    if (it != thisCatYields.end())
	    {
	      out << it->second;

	      // assume that we also have number of MC events
	      if (! proc.isData)
		{
		  out << "<br/>";
		  out << "<div class=\"mc-events\">";
		  out << "(" << result.eventYield.mcEvents.at(catname).at((const char *)proc.label)
		      << ")";
		  out << "</div>";
		}
	    }
	    else
	      out << "-";
	    out << "</td>" << endl;
	  }
	  
	  out << "</tr>" << endl;

	}

	out << "</table>" << endl;

      } // loop over plot results

    out << "</body>" << endl;
    out << "</html>" << endl;

    //----------
    // clear the results
    //----------
    plotResultsForHTML.clear();
    
    // remove the temporary working directory
    rmdir(tmpWorkingDir.c_str());

    recordForHTML = false;
  }

  //----------------------------------------

  /** add a cut to be applied to data only */
  void addDataOnlyCut(const string &cut)
  {
    dataOnlyCuts.push_back(cut);
  }

  //----------------------------------------

  /** removes the latest cut for data only */
  void removeLastDataOnlyCut()
  {
    if (dataOnlyCuts.empty())
      cerr << "WARNING: no data only cut present, can not remove it" << endl;
    else
      dataOnlyCuts.pop_back();
  }

};

//----------------------------------------------------------------------
