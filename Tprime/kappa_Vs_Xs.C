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
#include "TGraph.h"

using namespace std;

void kappa_Vs_Xs(){

gROOT->SetBatch();

int n_pts=8;
Double_t T_mass[8] = {600, 650, 700, 800, 900, 1000, 1100, 1200};

/*
ifstream myfile;
string fString,line;
myfile.open("TotalWidth_x_coupling_SingleT_NWA.txt");
double MQ, kT, width, width_d1, width_d2;
string line1, line1_;
*/

TGraph* kTVsXs_graph[n_pts];
TSpline3 * kTVsXs_spline[n_pts];

TGraph* WidthVsXs_graph[n_pts];
TSpline3 * WidthVsXs_spline[n_pts];

TGraph* kTVsW_graph[n_pts];
TSpline3 * kTVsW_spline[n_pts];

TGraph* WidthVskT_graph[n_pts];
TSpline3 * WidthVskT_spline[n_pts];

TLegend *leg = new TLegend(0.15, 0.6, 0.3, 0.85, "");
leg->SetFillColor(0);

ofstream kT_Vs_Xs_of;
kT_Vs_Xs_of.open("kT_Vs_Xs.txt");
kT_Vs_Xs_of << "MQ" <<"\t\t"<< "kapppa"<<"\t\t"<<"sigma(fb)"<<endl;

ofstream Width_Vs_Xs_of;
Width_Vs_Xs_of.open("Width_Vs_Xs.txt");
Width_Vs_Xs_of << "MQ" <<"\t\t"<< "kapppa"<<"\t\t"<<"Width(%)"<<"\t\t"<<"sigma(fb)"<<endl;

ofstream Width_Vs_kT_of;
Width_Vs_kT_of.open("width_Vs_kT.txt");
Width_Vs_kT_of << "MQ" <<"\t\t"<< "width"<<"\t\t"<<"kappa"<<endl;

for(int i=0; i<n_pts; i++){
cout<<"i=  "<<i<<endl;
int j=0;
ifstream myfile;
string fString,line;
myfile.open("CrossSections_SingleT_tH_b_FW.txt");

double MQ, width, width_per, sigma_hat, QCDscaleUp_1, QCDscaleUp_2, xs, kT;
string line1, line1_;

double x[4], y[4], z[4];

  while(getline(myfile,line))
	{
	if(line.find("MQ")!=std::string::npos) continue;
	line1=line;
	stringstream line1_(line1);
	line1_ >> MQ >> width >> width_per >> sigma_hat >> QCDscaleUp_1 >> QCDscaleUp_2 >> xs >> kT;
	if(MQ==T_mass[i]){
	Width_Vs_Xs_of<<MQ<<"\t\t"<<kT<<"\t\t"<<width_per<<"\t\t"<<xs<<endl;
	cout<<"test=\t"<<MQ<<"\t"<<kT<<"\t"<<width<<"\t"<<xs<<endl;
	x[j]=kT;
	y[j]=xs;
	z[j]=width_per;
	j++;
	}
//	i++;
	}
	kTVsXs_graph[i] = new TGraph(j,x,y);
	kTVsXs_graph[i]->SetTitle("");
	kTVsXs_graph[i]->SetLineColor(i);
	kTVsXs_graph[i]->GetXaxis()->SetTitle("#kappa_{T}");
	kTVsXs_graph[i]->GetYaxis()->SetTitle("#sigma_{T'#rightarrow tH}");
	kTVsXs_spline[i] = new TSpline3("grs", kTVsXs_graph[i]);
	kTVsXs_spline[i]->SetLineColor(1+i);
	kTVsXs_spline[i]->SetLineWidth(2);

    WidthVsXs_graph[i] = new TGraph(j,z,y);
    WidthVsXs_graph[i]->SetTitle("");
    WidthVsXs_graph[i]->SetLineColor(i);
    WidthVsXs_graph[i]->GetXaxis()->SetTitle("#Gamma/M");
    WidthVsXs_graph[i]->GetYaxis()->SetTitle("#sigma_{T'#rightarrow tH}");
    WidthVsXs_spline[i] = new TSpline3("grs", WidthVsXs_graph[i]);
    WidthVsXs_spline[i]->SetLineColor(1+i);
    WidthVsXs_spline[i]->SetLineWidth(2);

    WidthVskT_graph[i] = new TGraph(j,z,x);
    WidthVskT_graph[i]->SetTitle("");
    WidthVskT_graph[i]->SetLineColor(i);
    WidthVskT_graph[i]->GetYaxis()->SetTitle("#kappa_{T}");
    WidthVskT_graph[i]->GetXaxis()->SetTitle("#Gamma/M{T'} (%)");
    WidthVskT_spline[i] = new TSpline3("grs", WidthVskT_graph[i]);
    WidthVskT_spline[i]->SetLineColor(1+i);
    WidthVskT_spline[i]->SetLineWidth(2);

	leg->AddEntry(kTVsXs_spline[i], Form("T' mass %.0f",T_mass[i]), "l");
	cout<<"i=  "<<i<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.05<<"\t\t"<<kTVsXs_spline[i]->Eval(0.05)<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.10<<"\t\t"<<kTVsXs_spline[i]->Eval(0.10)<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.15<<"\t\t"<<kTVsXs_spline[i]->Eval(0.15)<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.20<<"\t\t"<<kTVsXs_spline[i]->Eval(0.20)<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.25<<"\t\t"<<kTVsXs_spline[i]->Eval(0.25)<<endl;
    kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.3<<"\t\t"<<kTVsXs_spline[i]->Eval(0.3)<<endl;
	kT_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0.35<<"\t\t"<<kTVsXs_spline[i]->Eval(0.35)<<endl;
	
	Width_Vs_Xs_of<<T_mass[i]<<"\t\t"<<0<<"\t\t"<<5<<"\t\t"<<WidthVsXs_graph[i]->Eval(5)<<endl;

    Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<1<<"\t\t"<<WidthVskT_spline[i]->Eval(1)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<2<<"\t\t"<<WidthVskT_spline[i]->Eval(2)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<3<<"\t\t"<<WidthVskT_spline[i]->Eval(3)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<4<<"\t\t"<<WidthVskT_spline[i]->Eval(4)<<endl;
    Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<5<<"\t\t"<<WidthVskT_spline[i]->Eval(5)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<10<<"\t\t"<<WidthVskT_spline[i]->Eval(10)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<20<<"\t\t"<<WidthVskT_spline[i]->Eval(20)<<endl;
	Width_Vs_kT_of<<T_mass[i]<<"\t\t"<<30<<"\t\t"<<WidthVskT_spline[i]->Eval(30)<<endl;
myfile.close();
}

kT_Vs_Xs_of.close();
Width_Vs_Xs_of.close();
cout<<"Xs for kT 0.05\t"<<kTVsXs_spline[0]->Eval(0.05)<<endl;

TCanvas *c1= new TCanvas("c1", "c1",600,600);
c1->SetGridx();
c1->SetGridy();
c1->SetLogy();
//c1->SetLogx();
c1->cd();
kTVsXs_graph[0]->SetMinimum(1);
kTVsXs_graph[0]->Draw("AP");
kTVsXs_spline[0]->Draw("APL SAME");

for(int i=1; i<n_pts; i++){
kTVsXs_spline[i]->Draw("CSAME");
kTVsXs_spline[i]->Draw("CSAME");
}
leg->Draw("SAME");

TCanvas *c2= new TCanvas("c2", "c2",600,600);
c2->SetGridx();
c2->SetGridy();
c2->SetLogy();
c2->cd();
WidthVsXs_graph[0]->SetMinimum(1);
WidthVsXs_graph[0]->Draw("AP");
WidthVsXs_spline[0]->Draw("APL SAME");

for(int i=1; i<n_pts; i++){
WidthVsXs_spline[i]->Draw("CSAME");
WidthVsXs_spline[i]->Draw("CSAME");
}

leg->Draw("SAME");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_kT_vs_Xs_LogY.png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_kT_vs_Xs_LogY.pdf");

c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_Width_vs_Xs_LogY.png");
c2->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_Width_vs_Xs_LogY.pdf");
}
