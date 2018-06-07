#include <cmath>
#include <iostream>
#include <vector>
#include <TMath.h>

#ifndef __DV__
#define __DV__

//
// The Jakobian determinant for a N-dimensional sphere
//
// dim: number of dimensions
// vector x: polar coordinates: x[0] = r, x[n] = phi[n]

inline double dV(const int dim, std::vector<double> x)
{
  // sanity check
  if (dim != x.size()){ 
    std::cout << "Error: dimension D != size of vector x!" << std::endl;
    return 0.;
  }

  // sanity check 2
  if (dim<1) return 0.;

  // factor of r
  double fr = TMath::Power(x[0], dim-1);

  // factors of sin(phi)
  double fp = 1.;
  for (int ip=2; ip<dim; ++ip){
    fp *= TMath::Power(TMath::Sin(x[ip-1]), dim-ip);
  }

  return fr*fp;

}

#endif
