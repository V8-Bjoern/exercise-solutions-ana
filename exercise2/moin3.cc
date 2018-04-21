#include <iostream> // fuer Ein- und Ausgabe
#include <cmath> // fuer exp und M_E
//Expo-Funktion
double expo(double x, int nmax) {//Beginn der Expo-Funktion
  double expox = 1;//definiert Variable expox
  double summand = 1;//definiert Variable summand
  for(int n = 1 ; n  < nmax ; ++n) {//Schleife
    summand *= x / n;//summand = summand * x / n
    expox += summand;//expox = expox + summand
  }//Ende der Schleife
  return expox;//gebe expox zurueck
}//Ende der expo-Funktion
//Hauptfunktion
int main() {//Beginn der Hauptfunktion
  const int N = 20;//definiert Konstante N
  for(double x = 0 ; x < M_E ; x+= 0.01) {//Schleife
    std::cout << "x = " << x << " expo = " << expo(x,N)  << std::endl;
    if(expo(x,N) > M_E) break;//Wenn-Bedingung; breche Schleife ab
  }//Ende der Schleife
}//Ende der Hauptfunktion

