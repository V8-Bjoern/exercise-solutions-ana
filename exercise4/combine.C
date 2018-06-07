#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>


double background(double* x, double* pars);
double signal(double* x, double* pars);
double back_and_signal(double* x, double* pars);
std::vector<double> residual(TH1D *exp1, TH1D *exp2);

void combine()
{
  // open file with data from experiment A
  TFile* fexpA = new TFile("exp_A.root", "READ");

  // open file with data from experiment B
  TFile* fexpB = new TFile("exp_B.root", "READ");
  TFile* fexpC = new TFile("exp_C.root", "READ");
  TFile* fexpD = new TFile("exp_D.root", "READ");


  //New file with the results
  TFile* results = new TFile("results.root","RECREATE");
  if ( results->IsOpen() ) printf("File opened successfully\n");
  // list the file content
  fexpA->ls();
  fexpB->ls();

  // get the histogram containing the data
  TH1D *expA = (TH1D*)fexpA->Get("exp_A");
  TH1D *expB = (TH1D*)fexpB->Get("exp_B");
  TH1D *expC = (TH1D*)fexpC->Get("exp_C");
  TH1D *expD = (TH1D*)fexpD->Get("exp_D");
  /*
  Probelem 1
  */
  std::vector<double> residualAB=residual(expA, expB);
  std::vector<double> residualAC=residual(expA, expC);
  std::vector<double> residualAD=residual(expA, expD);
  std::vector<double> residualBC=residual(expB, expC);
  std::vector<double> residualBD=residual(expB, expD);
  std::vector<double> residualCD=residual(expC, expD);

 //std::vector<std::vector<double>> residuals = {residualAB,residualAC,residualAD,residualBC,residualBD,residualCD};

  TH1D* HResidualAB= new TH1D("HResidualAB", "HResidualAB", 10, -1000, 1000);
  TH1D* HResidualAC= new TH1D("HResidualAC", "HResidualAC", 10, -1000, 1000);
  TH1D* HResidualAD= new TH1D("HResidualAD", "HResidualAD", 10, -1000, 1000);
  TH1D* HResidualBC= new TH1D("HResidualBC", "HResidualBC", 10, -1000, 1000);
  TH1D* HResidualBD= new TH1D("HResidualBD", "HResidualBD", 10, -1000, 1000);
  TH1D* HResidualCD= new TH1D("HResidualCD", "HResidualCD", 10, -1000, 1000);

  //std:vector<TH1D*> ResidualHistos = {HResidualAB,HResidualAC,HResidualAD,HResidualAD,HResidualBC,HResidualBD,HResidualCD};

  for(int i = 0;i<residualAB.size();i++) {
      HResidualAB->Fill(residualAB[i]);
      HResidualAC->Fill(residualAC[i]);
      HResidualAD->Fill(residualAD[i]);
      HResidualBC->Fill(residualBC[i]);
      HResidualBD->Fill(residualBD[i]);
      HResidualCD->Fill(residualCD[i]);
  }
  std::ofstream fout1("solutionOfProblem1.txt");

  fout1 << "Name    Mean    RMS" << endl;
  fout1 << "AB    " <<  HResidualAB->GetMean() << "   "<< HResidualAB->GetRMS() << endl;
  fout1 << "AC    " <<  HResidualAC->GetMean() << "   "<< HResidualAC->GetRMS() << endl;
  fout1 << "AD    " <<  HResidualAD->GetMean() << "   "<< HResidualAD->GetRMS() << endl;
  fout1 << "BC    " <<  HResidualBC->GetMean() << "   "<< HResidualBC->GetRMS() << endl;
  fout1 << "BD    " <<  HResidualBD->GetMean() << "   "<< HResidualBD->GetRMS() << endl;
  fout1 << "CD    " <<  HResidualCD->GetMean() << "   "<< HResidualCD->GetRMS() << endl;
  fout1.close();



  /*
  Probelem 2
  */
  std::ofstream fout2("solutionOfProblem2.txt");
  HResidualAB->Fit("gaus");
  TF1 *fit1 = HResidualAB->GetFunction("gaus");
  fout2 <<"GetChisquareAB: " << fit1->GetChisquare() << endl;
  HResidualAC->Fit("gaus");
  TF1 *fit2 = HResidualAC->GetFunction("gaus");
  fout2 <<"GetChisquareAC: " << fit2->GetChisquare() << endl;
  HResidualAD->Fit("gaus");
  TF1 *fit3 = HResidualAD->GetFunction("gaus");
  fout2 <<"GetChisquareAD: " << fit3->GetChisquare() << endl;
  HResidualBC->Fit("gaus");
  TF1 *fit4 = HResidualBC->GetFunction("gaus");
  fout2 <<"GetChisquareBC: " << fit4->GetChisquare() << endl;
  HResidualBD->Fit("gaus");
  TF1 *fit5 = HResidualBD->GetFunction("gaus");
  fout2 <<"GetChisquareBD: " << fit5->GetChisquare() << endl;
  HResidualCD->Fit("gaus");
  TF1 *fit6 = HResidualCD->GetFunction("gaus");
  fout2 <<"GetChisquareCD: " << fit6->GetChisquare() << endl;
  fout2 << "The Value of AB is very close to one, that means the fit is good." << endl;
  fout2 << "AC, AD, BC and CD are not so good but ok." << endl;
  fout2 << "The Value of BC is lower than one that means the fit is too,
  normaly means that, the uncertainties are overestimate but we have no uncertainties." << endl;


  fout2.close();

  // draw it
  expA->Draw("E1");


  // this is how you can get the number of bins:
  cout << "number of bins = " << expA->GetNbinsX() << endl;

  // here is the measurement in some bin with error:
  cout << "measurement in bin 27: " << expA->GetBinContent(27) << " +- " << expA->GetBinError(27) << endl;

  // now define the fit functions
  // backgrond function
  double bpars[4];
  bpars[0] = 0.005;
  bpars[1] =  -0.00001;
  bpars[2] = 0.08;
  bpars[3] = -0.015;

  // parameters of the signal function
  double pars[4+3]; // background: 4, signal: 3 parameters
  pars[0] = bpars[0];
  pars[1] = bpars[1];
  pars[2] = bpars[2];
  pars[3] = bpars[3];
  pars[4] = 0.001;
  pars[5] = 160;
  pars[6] = 20;

  TF1* bf = new TF1("background", background, 20, 300, 4);
  bf->SetParameters(bpars);
  bf->SetLineColor(kBlue+1);
  bf->SetLineStyle(kDashed);

  bf->Draw("same");


  results->WriteTObject(HResidualAB);
  results->WriteTObject(HResidualAC);
  results->WriteTObject(HResidualAD);
  results->WriteTObject(HResidualBC);
  results->WriteTObject(HResidualBD);
  results->WriteTObject(HResidualCD);

  results->Close();
}

// define functions
double background(double* x, double* pars)
{
  double y;
  double alpha = pars[0];
  double beta =  pars[1];
  double gamma = pars[2];
  double delta = pars[3];

  y = alpha + beta*x[0] + gamma*exp(delta*x[0]);

  return y;
}

double signal(double* x, double* pars)
{
  double y;
  double n = pars[0];
  double m = pars[1];
  double sigma = pars[2];
  double arg = -0.5*(pow( (x[0]-m)/sigma , 2) );
  y = n * exp(arg);

  return y;
}

double back_and_signal(double* x, double* pars)
{
  return background(x,pars) + signal(x,pars+4);
}

std::vector<double> residual(TH1D *exp1, TH1D *exp2)
{
	std::vector<double> result;
	double chi;
	double NaNb;
	double sigma;
	for(int i=0; i < exp1->GetNbinsX(); i++)
	{
		NaNb = (exp1->GetBinContent(i)-exp2->GetBinContent(i));
		sigma = pow(exp1->GetBinError(i),2.)+pow(exp2->GetBinError(i),2.);
		chi = NaNb/sigma;
		result.push_back(chi);
	}
	return result;

}
