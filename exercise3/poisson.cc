#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

//Poisson probability:
double prob(double n, double mu){
    double p = pow(mu,n)*exp(-mu)/tgamma(n+1);
    return p;
}

double Cmu(double mu){
    double c = 0;
    for (int n= 0; n < 1000 ; n++){
        double a = n-sqrt(n);
        double b = n+sqrt(n);
        if (mu > a && mu < b){
            c += prob(n+=0.0,mu);
        }
     }
     return c;
}
void WriteSolutionOfProblem2(){
    std::vector<double> tab = {0.,0.5,1.,1.5,2.,3.,5.,10.,20.};
    std::ofstream fout("solutionOfProblem2.txt");
    fout << "mu  Cmu" << endl;
    for (int i=0; i < tab.size(); i++){
        fout << tab[i] << "  ";
        fout << Cmu(tab[i]) << " " << std::endl;
    }
    fout << "the coverage C(mu) rises with mu, " << endl;
    fout << "that means the probability rieses that the interval includes the true value of mu." <<  endl;
    fout.close();
}
void WriteCmu(){
    std::ofstream fout("cmu.txt");
    double mu;
    for (int i=0; i < 1000; i++){
        mu = 0.02*i;
        fout << mu << "  ";
        fout << Cmu(mu) << " " << endl;
    }
    fout.close();
}
int main(){
    cout <<"Should be 0.22404 and it is: " << prob(2,3) << endl;
    WriteSolutionOfProblem2();
    WriteCmu();
    return 0;
}
