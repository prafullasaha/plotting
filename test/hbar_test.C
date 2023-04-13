#include "TH1.h"
#include "TProfile.h"
#include <string.h>
using namespace std;

void hbar_test()
{
	gStyle->SetOptStat(0);
	gROOT->SetBatch(1);
	TLatex latex;
//	TH1F* h_bar =new TH1F("h_bar","Survey;Percentage;Count",9,0,50);
	TH1F* h_bar =new TH1F("h_bar","Survey;;",9,0,50);
	const int nbins = 9;
	double per[nbins] = {5, 10, 15, 20, 25, 30, 35, 40, 50};
// 	double count[nbins]= {1, 6, 1, 1, 4, 1, 1, 1, 1, 2, 1}; 
 	double count[nbins]= {1, 6, 2, 4, 1, 2, 2, 2, 1}; 
	string labels[9] = {"0-5 %", "6-10%", "11-15%", "16-20%", "21-25%", "26-30%", "31-35%", "36-40%", "41-50%"};
	for (int i=0;i<nbins;i++)
	{
	h_bar->SetBinContent(i+1, count[i]);
	h_bar->GetXaxis()->SetBinLabel(i+1, labels[i].c_str());
	}
   // If file is not found try to generate it using the macro tree/cernbuild.C
   TCanvas *c1 = new TCanvas("c1","histograms with bars",800,400);
//   c1->SetFillColor(42);
//   c1->Divide(1,2);
   // Horizontal bar chart
   c1->cd(1);
   gPad->SetGrid();
//   gPad->SetLogx();
//   gPad->SetFrameFillColor(33);
   h_bar->Draw("hbar");

   h_bar->SetBarWidth(0.8);
   h_bar->SetBarOffset(0.1);
   h_bar->SetFillColor(kOrange+3);
   h_bar->SetLabelSize(0.07);
   h_bar->GetYaxis()->SetLabelSize(0.06);
   h_bar->GetXaxis()->SetLabelSize(0.06);
   h_bar->SetMaximum(1.2*(h_bar->GetMaximum()));	
   // Vertical bar chart
/*   c1->cd(2);
   gPad->SetGrid();
   gPad->SetFrameFillColor(33);
   T->Draw("Division>>hDiv","","goff");
   TH1F *hDiv = (TH1F*)gDirectory->Get("hDiv");
   hDiv->SetStats(0);
   TH1F *hDivFR = (TH1F*)hDiv->Clone("hDivFR");
   T->Draw("Division>>hDivFR","Nation==\"FR\"","goff");
   hDiv->SetBarWidth(0.45);
   hDiv->SetBarOffset(0.1);
   hDiv->SetFillColor(49);
   TH1 *h1 = hDiv->DrawCopy("bar2");
   hDivFR->SetBarWidth(0.4);
   hDivFR->SetBarOffset(0.55);
   hDivFR->SetFillColor(50);
   TH1 *h2 = hDivFR->DrawCopy("bar2,same");
 
   TLegend *legend = new TLegend(0.55,0.65,0.76,0.82);
   legend->AddEntry(h1,"All nations","f");
   legend->AddEntry(h2,"French only","f");
   legend->Draw();
*/ 
//   c1->cd();
//   delete f;
//   return c1;
    for(int i=0;i<nbins;i++)
    {
    latex.DrawLatex(count[i]+0.05, h_bar->GetBinCenter(i+1)-1, Form("#scale[0.8]{%0.0f (%0.1f%)}",count[i], (count[i]/21)*100));
    }

//	latex.DrawLatex(1,6*i,Form("%0.0f (%0.1f%)",count[i], (count[i]/21)*100));

   c1->SaveAs("/eos/user/p/prsaha/www/tmp/survey.pdf");
}
