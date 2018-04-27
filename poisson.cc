#include <iostream>
#include <cmath>

double p(double n, double my);
int fak(double n);
double Cov(double my);
double a(double n);
double b(double n);
double sig1(double n);
double sig2(double n);
double mym(double n);
double n;
double my;


int main(){
// testing purpose
//std::cin << n << my << std::endl;
std::cout << p(1,1) << std::endl;
return 0;
}
//Coverege
//

//a,b def
double b(double n)
{
return mym(n) + sig2(n);
}
double a(double n)
{
return mym(n) - sig1(n);
}

//sig1,2 def
//not set jet
double sig2(double n)
{
return 1;
}
double sig1(double n)
{
return 1;
}
double mym(double n)
{
return 1;
}

// Poisson def
double p(double n, double my)
{
return pow(my,n) * exp (-my) / fak(n);
}

//Fakultäts def
int fak(double n)
{
    if(n==0)      
        return 1;  
    else
        return n * fak(n-1);
} 
