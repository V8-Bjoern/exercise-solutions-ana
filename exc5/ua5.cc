#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
//#include <random>
#include <cstdlib>

int N = 10;
int i = 1;
int dim = 1;
int IntN = 0;
int Vcube = 1;
double V;
int k = 2;
int j = 1;

double MCS(int N,int dim,int R){
	int i = 1;
	int j = 1;
	int IntN = 0;
	int Vcube = pow(R,dim);
	double quad = 0;
	//rand:0bis1
	while(i <= N){
	while(j <= dim){
	//srand(time(NULL));
    int r = (rand() % 1001)/1000;
	double quad = quad + pow(r,2);
	int j = j + 1;
	std::cout << j << " " << dim << std::endl;
	}
	if(quad <= 1){
	IntN = IntN + 1;
	}
	int i = i +1;
	double quad = 0;
	int j = 1;
	std::cout << "Sum" << std::endl;
	}
    double V = 2^dim * Vcube * IntN / N;
	return V;
	};

int main(){
  using namespace std;
  ofstream solu("solution5.txt",ios::out);
  solu << "Exercise 1:" << endl;
  dim = 1;
  N = 10;
  solu << "d Value, R = 1, R = 3" << endl;
  cout << "Start UA1" << endl;
  while(dim<=3){
	  solu << dim << ", " << MCS(N,dim,1) << ", " << MCS(N,dim,3) << endl;
	  dim = dim + 1;
	  cout << "durch" << endl;
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