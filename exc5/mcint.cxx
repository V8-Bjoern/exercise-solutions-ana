#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <TMath.h>
#include <TRandom3.h>
#include "dV.cxx"

int main()
{
  using namespace std;
  TRandom3 rand(0);

  const int dim=3;  // dimensions
  double R=3;       // radius of N-dimensional sphere
  int N=10;         // number of integration points

  double u[dim];           // array with random numbers
  std::vector<double> x;   // vector with integration 

  int i=1;
  int j=1;
  int task = 1;
  double sum = 0;
  double sum2 = 0;
  double summa;

  //int dim = 1
  //int R = 1

  10;
    while (i<N+1){

    // get an array of random numbers with n dimensions
    rand.RndmArray(dim, u);

    // here is dV(r, phi_1, phi_2, phi_3..., phi_n-1)
    double fi = dV(dim, x);

    // don't forget to clean up
    x.clear();
    ++i;
  }

  //if (task = 1){
  //d
  i = 1;
  while (i<N+1){
  summa += rand[i];
  }

  //now doin stuff
  //double MC = (V/n)*carlo;
  //double (V / n)* ( V / n ) * sum(rand * rand - MC * MC);

  // here is the exact solution (for dim>1):
  double rn = TMath::Power(R, dim);
  double sn = 2*TMath::Power(TMath::Pi(), dim/2.);
  sn /= std::tgamma(dim/2.);
  double sol = sn*rn/dim;

  cout << "exact solution: " << sol << endl;
  cout << "MC solution: " << summa << endl;
  ofstream solu("solution5.txt",ios::out);
  solu << "Exercise 1:" << endl;
  solu << "d Value, R = 1, d= 3" << endl;
  solu << "1, " << " " << endl;
  solu << "2, " << " " << endl;
  solu << "3, " << " " << endl;
  solu << " " << endl;
  solu << "Exercise 2:" << endl;
  solu << "d, n, sigma/I" << endl;
//while
  solu << "1, " << " " << endl;
  solu << "2, " << " " << endl;
  solu << "3, " << " " << endl;
  solu << " " << endl;

  solu << " " << endl;
  solu << "Exercise 3:" << endl;
  solu << "n, I, sigma/I" << endl;
  solu << " " << endl;

}
