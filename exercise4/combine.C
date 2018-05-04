#include <cmath>

double background(double* x, double* pars);
double signal(double* x, double* pars);
double back_and_signal(double* x, double* pars);

void combine()
{
  // open file with data from experiment A
  TFile* fexpA = new TFile("exp_A.root", "READ");
   
  // open file with data from experiment B
  TFile* fexpB = new TFile("exp_B.root", "READ");
  
  // list the file content
  fexpA->ls();
  fexpB->ls();

  // get the histogram containing the data
  TH1D *expA = (TH1D*)fexpA->Get("exp_A");
  TH1D *expB = (TH1D*)fexpB->Get("exp_B");

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
	std::vector *result = new std::vector();
	double chi;
	double NaNb;
	double sigma;
	for(int i=0; i < expA->GetNbins1(); i++)
	{
		NaNb = exp1->GetBinContent(i)-exp2->GetBinContent(i)); 
		sigma = pow(exp1->GetBinError(i),2.)+pow(exp2->GetBinError(i),2.)
		chi = NaNb/sigma;
		result->push_back(chi);
	}
	return result;
	
}
