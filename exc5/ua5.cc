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

//time_t seconds;

//time(&seconds);

//srand((unsigned)seconds);

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

int main(){
  using namespace std;
  ofstream solu("solution5.txt",ios::out);
  solu << "Exercise 1:" << endl;
  dim = 1;
  N = 10000;
  solu << "d R=1 R=3" << endl;
  cout << "Start UA1" << endl;
  for (int dim = 1; dim <= 3; dim++ ){
	  solu << dim << " " << MCS(N,dim,1) << " " << MCS(N,dim,3) << endl;
  }
  solu << " " << endl;
  solu << "Exercise 2:" << endl;
  solu << "d, n, sigma/I" << endl;
  k = 2;
  cout << "Start UA2" << endl;
  //while(dim<=3){
	 // N = 10^k
	 // solu << dim << ", " << MCS(N,dim,3) << ", "
	  //k += 1
	 // N = 10^k
	  //solu << MCS(N,dim,3) << "ERROR" << endl;
	  //k += 1
	  
  cout << "Start UA3" << endl;
  solu << " " << endl;
  solu << "Exercise 3:" << endl;
  //int Vtest = MCS(10000,12,3)
  solu << "sigma_g= " << " " << endl;
  solu << "n, I, sigma/I" << endl;
  solu << " " << endl;
  solu.close();
}