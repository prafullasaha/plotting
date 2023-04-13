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

void kappa_Vs_Width(){
int n_pts=8;
Double_t T_mass[8] = {600, 650, 700, 800, 900, 1000, 1100, 1200};

/*
ifstream myfile;
string fString,line;
myfile.open("TotalWidth_x_coupling_SingleT_NWA.txt");
double MQ, kT, width, width_d1, width_d2;
string line1, line1_;
*/

TGraph* kTVsW_graph[n_pts];
TSpline3 * kTVsW_spline[n_pts];

TGraph* WVskT_graph[n_pts];
TSpline3 * WVskT_spline[n_pts];

TLegend *leg = new TLegend(0.15, 0.6, 0.3, 0.85, "");
leg->SetFillColor(0);

for(int i=0; i<n_pts; i++){
cout<<"i=  "<<i<<endl;
int j=0;
ifstream myfile;
string fString,line;
myfile.open("TotalWidth_x_coupling_SingleT_NWA.txt");
double MQ, kT, width, width_d1, width_d2;
string line1, line1_;

double x[5], y[5];

  while(getline(myfile,line))
	{
	if(line.find("MQ")!=std::string::npos) continue;
	line1=line;
	stringstream line1_(line1);
	line1_ >> MQ >> kT >> width >> width_d1 >> width_d2;
	if(MQ==T_mass[i]){
	cout<<"  test=   "<<MQ<<"   "<<kT<<"   "<<width<<endl;
	x[j]=kT;
	y[j]=width;
	j++;
	}
//	i++;
	}
	kTVsW_graph[i] = new TGraph(j,x,y);
	kTVsW_graph[i]->SetTitle("");
	kTVsW_graph[i]->SetLineColor(i);
	kTVsW_graph[i]->GetXaxis()->SetTitle("#kappa_{T}");
	kTVsW_graph[i]->GetYaxis()->SetTitle("#Gamma/M{T'} (%)");
	kTVsW_spline[i] = new TSpline3("grs", kTVsW_graph[i]);
	kTVsW_spline[i]->SetLineColor(1+i);
	kTVsW_spline[i]->SetLineWidth(2);

    WVskT_graph[i] = new TGraph(j,x,y);
    WVskT_graph[i]->SetTitle("");
    WVskT_graph[i]->SetLineColor(i);
    WVskT_graph[i]->GetXaxis()->SetTitle("#kappa_{T}");
    WVskT_graph[i]->GetYaxis()->SetTitle("#Gamma/M{T'} (%)");
    WVskT_spline[i] = new TSpline3("grs", WVskT_graph[i]);
    WVskT_spline[i]->SetLineColor(1+i);
    WVskT_spline[i]->SetLineWidth(2);

	leg->AddEntry(kTVsW_spline[i], Form("T' mass %.0f",T_mass[i]), "l");
myfile.close();
}

ifstream myfile1;
myfile1.open("/afs/cern.ch/work/p/prsaha/public/FinalFit_lite/CMSSW_10_2_13/src/flashggFinalFit/Combine/ExpObs_kappa.txt");
double MQ, kT_th, kT_exp, kT_Obs, kT_el, kT_eh, kT_e2l, kT_e2h;
string l, l1, l1_;

ofstream width_of;
width_of.open("ExpObs_width.txt");
width_of << "MQ" <<"\t"<< "width_th"<<"\t"<<"width_Exp"<<"\t"<< "width_obs"<<"\t"<<"sigma_1l"<<"\t"<<"sigma_1h"<<"\t"<<"sigma_2l"<<"\t"<<"sigma_2h"<<endl;

ofstream width_of;
width_Vs_kT_of.open("width_Vs_kT.txt");
width_of << "MQ" <<"\t\t"<< "width"<<"\t\t"<<"kappa"<<endl;

int m=0;
  while(getline(myfile1,l))
    {
    if(l.find("MQ")!=std::string::npos) continue;
    l1=l;
    stringstream l1_(l1);
	l1_>>MQ>>kT_th>>kT_exp>>kT_Obs>>kT_el>>kT_eh>>kT_e2l>>kT_e2h;
    cout<<"  test=   "<<MQ<<"   "<<kT_th<<"   "<<kT_exp<<"   "<<kTVsW_spline[m]->Eval(kT_th)<<endl;
	width_of << MQ <<"    "<< kTVsW_spline[m]->Eval(kT_th) <<"   "<< kTVsW_spline[m]->Eval(kT_exp)<<"   "<< kTVsW_spline[m]->Eval(kT_Obs)<<"   "<<kTVsW_spline[m]->Eval(kT_el)<<"   "<<kTVsW_spline[m]->Eval(kT_eh)<<"   "<<kTVsW_spline[m]->Eval(kT_e2l)<<"   "<<kTVsW_spline[m]->Eval(kT_e2h)<<endl;	
	width_Vs_kT_of<<MQ<<"\t\t"<<1<<"\t\t"<<WVskT_spline->Eval(1)<<endl;
	width_Vs_kT_of<<MQ<<"\t\t"<<5<<"\t\t"<<WVskT_spline->Eval(5)<<endl;
	m++;
    }
width_Vs_kT_of.close();
width_of.close();
myfile1.close();

TCanvas *c1= new TCanvas("c1", "c1",600,600);
c1->SetGridx();
c1->SetGridy();
c1->cd();
kTVsW_graph[n_pts-1]->Draw("AP");
kTVsW_spline[n_pts-1]->Draw("APL SAME");


for(int i=0; i<n_pts-1; i++){
kTVsW_spline[i]->Draw("CSAME");
kTVsW_spline[i]->Draw("CSAME");
}
leg->Draw("SAME");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_kT_vs_width.png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/UL/plot_kT_vs_width.pdf");
}
