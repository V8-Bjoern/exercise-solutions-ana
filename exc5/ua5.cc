#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdlib>
//#include <time.h>
#include <ctime>
//#include <TMath.h>
//#include <TRandom3.h>

int N = 10;
int i = 1;
int dim = 1;
int IntN = 0;
int Vcube = 1;
double V;
int k = 2;
int j = 1;
double rr;
int Nobs;
double sigG;

//Funktion zur Volumenberechnung
double MCS(int N,int dim,int R){
	//srand (time(NULL));
	std::srand(std::time(0));
	int IntN = 0;
	int Vcube = pow(R,dim);
	double quad = 0;
	double r;
	//rand:0bis1
	for (int i = 1; i <= N; i++ ){ 
	for (int j = 1; j <= dim; j++ ){      
	r = std::rand() % 1000;
	quad = quad + pow((r + 1)/1000,2);
	}
	if(quad <= 1){
	IntN += 1;
	}
	quad = 0;
	}
    double V = pow(2,dim) * Vcube * IntN / N;
	return V;
	};

//Funktion zur Varianzberechnung (etc)
double MCV(int N,int dim,int R){
	std::srand(std::time(0));
	int IntN = 0;
	int Vcube = pow(R,dim) * pow(2,dim);
	double quad = 0;
	double r;
	double Va;
	double V;
	double VaI;
	for (int i = 1; i <= N; i++ ){ 
	for (int j = 1; j <= dim; j++ ){      
	r = std::rand() % 1000;
	quad = quad + pow((r + 1)/1000,2);
	}
	if(quad <= 1){
	IntN += 1;
	}
	quad = 0;
	};
    V = Vcube * IntN / N;
	Va = ((pow((Vcube),2) * pow(IntN,2) / N) - pow(V,2)) / N;
	VaI = pow(Va, 0.5) / V;
	return VaI;
	};
	
//1% Genauigkeit Calculation
//double sig(
	double sig = 0,01 * pow(N,0.5)
	double 
	if (
	

//Hauptprogramm
int main(){
  using namespace std;
  ofstream solu("solution5.txt",ios::out);
  solu << "Exercise 1:" << endl;
  dim = 1;
  N = 10000;
  solu << "d R=1 R=3" << endl;
  cout << "Work on UA1.." << endl;
  for (int dim = 1; dim <= 3; dim++ ){
	  solu << dim << " " << MCS(N,dim,1) << " " << MCS(N,dim,3) << endl;
  }
  solu << " " << endl;
  solu << "Exercise 2:" << endl;
  solu << "d n sigma/I" << endl;
  cout << "Work on UA2.." << endl;
  dim = 0;
  for (int k = 2; k <= 7; k++ ){
		N = pow(10,k);
		if (k%2 == 0){
		dim += 1;
		};
		if (dim <= 2){
		solu << 3 << " " << N << " " <<MCV(N,3,3) << endl;
		};
		solu << dim << " " << N << " " <<MCV(N,dim,3) << endl;
  }
  cout << "Work on UA3.." << endl;
  solu << " " << endl;
  solu << "Exercise 3:" << endl;
  sigG = sig();
  Nobs = sigG * xx;
  solu << "sigma_g = " << sigG << endl;
  solu << "n = " << Nobs << endl;
  solu << "I = " << MCS(Nobs,12,3) << endl;
  solu << "sigma/I = " << MCV(Nobs,12,3) << endl;
  solu.close();
}