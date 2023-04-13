#include <iostream>

void eff_plot(){
//string fString,line;
//ifstream myfile;
int n_file=3;
string training[]={"600_700", "800_1000", "1100_1200"};
Double_t mass[]={600, 625, 650, 675, 700, 800, 900, 1000, 1100, 1200};
TGraph *yield_graph[n_file];
TMultiGraph *mg = new TMultiGraph();
TLegend *leg1 = new TLegend(0.7, 0.3, 0.9, 0.6, "");
leg1->SetFillColor(0);

for(int file_i=0; file_i<n_file; file_i++)
{
	ifstream myfile;
	string fString,line;
	myfile.open(Form("/afs/cern.ch/work/p/prsaha/public/plotting_macro/CMSSW_9_4_9/src/Tprime/MVA_evaluation/Yield_MVA%s.txt",training[file_i].c_str()));
	double Yield_BCut, Yield_ACut, Fraction;
	string S_name, line1, line1_;
	double eff[10];
	int i=0;
/*	while(myfile.fail())
		{
		cout <<  " failed to open" << endl;
		}
*/
	while(getline(myfile,line))
		{
			if(line.find("Sample")!=std::string::npos) continue;
			if(line.find("Tprime")!=std::string::npos)
			{
			line1=line;
			stringstream line1_(line1);
			line1_ >> S_name >> Yield_BCut >> Yield_ACut >> Fraction;
			cout<<i<<"  test=	"<<S_name<<"   "<<Fraction<<endl;
			eff[i]=Fraction;
			i++;
			}
		}
	yield_graph[file_i] = new TGraph(10, mass, eff);
	yield_graph[file_i]->SetLineWidth(3);
	yield_graph[file_i]->SetLineColor((file_i*10)+6);
	yield_graph[file_i]->SetMarkerStyle(20+file_i);
	yield_graph[file_i]->SetMarkerSize(1.5);
	yield_graph[file_i]->SetMarkerColor((file_i*10)+6);
	//yield_graph[0]->SetPoint(9, mass, eff);
	mg->Add(yield_graph[file_i]);
	leg1->AddEntry( yield_graph[file_i], Form("MVA%s", training[file_i].c_str()), "pl" );
}

mg->GetXaxis()->SetTitle("T' mass");
mg->GetYaxis()->SetTitle("Eff.");

TCanvas *c1 = new TCanvas("c1", "c1", 700, 600);
c1->SetGridy();
c1->SetGridx();
mg->Draw("APL");
leg1->Draw();
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/effInDiffTrnRegime.png");
c1->SaveAs("/eos/user/p/prsaha/www/Tprime_analysis/effInDiffTrnRegime.pdf");
}
