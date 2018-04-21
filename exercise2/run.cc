#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "Data.hh"

// generic function comparing two values of some type T used later for int and
// double
template <class T>
bool testEqual(const std::string& name, T expected, T real) {
  if (expected != real) {
    std::cout << "(" << name << ": <" << expected << ">"
              << ", " << real << ") ";
    return false;
  }
  return true;
}

bool testReadingSize() {
  std::cout << "testReadingSize...";
  Data datA("testA");
  return testEqual<int>("size", 1, datA.size());
}

bool testReadingMeasurement() {
  std::cout << "testReadingMeasurement...";
  Data datA("testA");
  return testEqual("measurement", 10., datA.measurement(0));
}

bool testReadingBinEdges() {
  std::cout << "testReadingBinEdges...";
  Data datA("testA");
  return testEqual("bin low", 0., datA.binLow(0)) &&
         testEqual("bin high", 1., datA.binHigh(0));
}

bool testReadingErrors() {
  std::cout << "testReadingErrors...";
  Data datA("testA");
  return testEqual("error", 2., datA.error(0));
}

bool testCopyConstructor() {
  std::cout << "testCopyConstructor...";
  Data a("testA");
  Data b(a);
  Data c = a;  // equivalent to Data c(a)
  return testEqual("measurement", 10., b.measurement(0)) &&
         testEqual("measurement", 10., c.measurement(0));
}

void runTests() {
  std::cout << "running tests...\n";
  std::vector<std::function<bool()> > tests(
      {testReadingSize, testReadingMeasurement, testReadingBinEdges,
       testReadingErrors, testCopyConstructor});
  for (auto test : tests)
    std::cout << (test() ? " ok" : " FAILED!") << std::endl;
}

int main() {
  using namespace std;

  cout << "******************************************************" << endl;
  runTests();
  cout << "******************************************************" << endl;
  // create an object which holds data of experiments
  Data datA("exp_A");
  Data datB("exp_B");
  Data datC("exp_C");
  Data datD("exp_D");
  Data datAundB = datC+datD;
  // Alle Experimente in ein Vektor
  std::vector<Data> alle_daten;
  alle_daten  ={datA,datB, datC, datD};
  // here is the data from experiment A=0 , B=1, C=2, D=3
  for(int i = 0; i < alle_daten.size(); ++i){
   cout << "bin 27: from " << alle_daten[i].binLow(27) << " to " << alle_daten[i].binHigh(27)
        << endl;
   cout << "measurement of experiment " << i << " in bin 27: " << alle_daten[i].measurement(27)
        << endl;
  }
  cout << "DeltaY of Bin 27 =" << datA.DeltaY(datB, 27) << "+/- " << datA.DeltaYError(datB, 27) << endl;
int NumberOfDataPoints = 0;
int SigmaFaktor = 1;
for (int i = 0; i  < alle_daten.size(); ++i){
    for(int n = i+1; n  < alle_daten.size(); ++n){
        NumberOfDataPoints += alle_daten[i].checkCompatibility(alle_daten[n], SigmaFaktor);
    }
}
cout << "Number of Data Points with that differ by more than " << SigmaFaktor << " Sigma: " << NumberOfDataPoints << endl;
  return 0;
}
