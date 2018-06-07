#include <cmath>
#include <iostream>
#include <vector>
#include <TMath.h>
#include <TRandom3.h>
#include "dV.cxx"
#include <fstream>
using namespace std;

vector<double> mc_int( const int dim, double R, int N)
{
    vector<double> results;

    TRandom3 rand(0);
    double u[dim];           // array with random numbers
    std::vector<double> x;   // vector with integration

    int i=1;
    double sum = 0;
    double sum2 = 0;
    double V;

    while (i<N+1){

      // get an array of random numbers with n dimensions
      rand.RndmArray(dim, u);

      x.push_back(u[0]*R);
      if(dim > 1)
      {
        for(int n=1; n < dim-1; n++)
        {
        x.push_back(u[n]*TMath::Pi());
        }
      V= R*TMath::Power(TMath::Pi(), dim-2)*TMath::Pi()*2;
      x.push_back(u[dim-1]*TMath::Pi()*2);
      }
      else{V= R;}
      // here is dV(r, phi_1, phi_2, phi_3..., phi_n-1)
      double fi = dV(dim, x);
      sum +=fi;
      sum2 +=TMath::Power(fi, 2);
      // don't forget to clean up
      x.clear();
      ++i;
    }

    double imc = sum*V/N;
    double vimc = (1.0/N)*(pow(V,2)/N*sum2-pow(imc,2));
    //cout << "imc=" << imc << endl;
    //cout << "sum2=" << sum2 << endl;
    results.push_back(imc);
    results.push_back(vimc);
    return results;
}


int main()
{


  const int dim=3;  // dimensions
  double R=3;       // radius of N-dimensional sphere
  int N=TMath::Power(10, 5);         // number of integration points






  // here is the exact solution (for dim>1):
  double rn = TMath::Power(R, dim);
  double sn = 2*TMath::Power(TMath::Pi(), dim/2.);
  sn /= std::tgamma(dim/2.);
  double sol = sn*rn/dim;

  cout << "MC result: " << mc_int(dim,R,N)[0] <<" +/- " << mc_int(dim,R,N)[1] << endl;
  cout << "exact solution: " << sol << endl;


  ofstream solu("solution5.txt",ios::out);
  solu << "Exercise 1:" << endl;
  solu << "R = 1, d= 1, IMC= "<< mc_int(1,1,N)[0] << endl;
  solu << "R = 3, d= 1, IMC= "<< mc_int(1,3,N)[0] << endl;
  solu << "R = 1, d= 2, IMC= "<< mc_int(2,1,N)[0] << endl;
  solu << "R = 3, d= 2, IMC= "<< mc_int(2,3,N)[0] << endl;
  solu << "R = 1, d= 3, IMC= "<< mc_int(3,1,N)[0] << endl;
  solu << "R = 3, d= 3, IMC= "<< mc_int(3,3,N)[0] << endl;
  solu << "Exercise 2:" << endl;
  solu << "d= 1, R=3, N=100, Sigmma/IMC= "<< sqrt(mc_int(1,3,100)[1])/mc_int(1,3,100)[0] << endl;
  solu << "d= 1, R=3, N=1000, Sigmma/IMC= "<< sqrt(mc_int(1,3,1000)[1])/mc_int(1,3,1000)[0] << endl;
  solu << "d= 2, R=3, N=10,000, Sigmma/IMC= "<< sqrt(mc_int(2,3,10000)[1])/mc_int(2,3,10000)[0] << endl;
  solu << "d= 2, R=3, N=100,000, Sigmma/IMC= "<< sqrt(mc_int(2,3,100000)[1])/mc_int(2,3,100000)[0] << endl;
  solu << "d= 3, R=3, N=1,000,000, Sigmma/IMC= "<< sqrt(mc_int(3,3,1000000)[1])/mc_int(3,3,1000000)[0] << endl;
  solu << "d= 3, R=3, N=10,000,000, Sigmma/IMC= "<< sqrt(mc_int(3,3,10000000)[1])/mc_int(3,3,10000000)[0] << endl;
  solu << "Exercise 3:" << endl;
  N=TMath::Power(10, 5);
  solu << "d= 12, R=3, N=10,000 Sigmma/IMC= "<< sqrt(mc_int(12,3,N)[1])/(mc_int(12,3,N)[0]*sqrt(N)) << endl;
  N=10000;
  solu << "d= 12, R=3, N=10000, IMC="<< mc_int(12,3,N)[0] << " Sigmma/IMC= "<< sqrt(mc_int(12,3,N)[1])/(mc_int(12,3,N)[0]*sqrt(N)) << endl;
  solu.close();

}
