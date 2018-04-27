#include "Data.hh"

#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

using namespace std;

Data::Data(const std::string& filename) {
  ifstream file(filename);

  // check if file opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Error could not open file with name: " +
                             filename);
  }

  int size = -1;
  file >> size;


  // read in data from file: m_siz+1 bin edges
  for (int i = 0; i < size + 1; ++i) {
    double edge;
    file >> edge;
    m_bins.push_back(edge);
  }
  // read in data from file: m_siz bin contents
  for (int i = 0; i < size; ++i) {
    double entries;
    file >> entries;
    m_data.push_back(entries);
  }
  for (int i = 0; i < size; ++i){
   double error;
   file >> error;
   m_error.push_back(error);
  }
  // done! close the file
  file.close();

  assertSizes();
};

void Data::assertSizes() { assert(m_data.size() + 1 == m_bins.size()); }
double Data::DeltaY (Data dat2, int bin){ return std::abs(dat2.measurement(bin)-measurement(bin)); }
double Data::DeltaYError (Data dat2, int bin){
    return sqrt(pow(dat2.error(bin),2.)+pow(error(bin),2.));
}
int Data::checkCompatibility(Data dat2, int n) {
    int NumberOfDataPoints = 0;
    for (int i=0; i < size(); i++){
        if (DeltaY (dat2, i) > n*DeltaYError(dat2, i)) {NumberOfDataPoints += 1;}
    }
    return NumberOfDataPoints;
}
Data Data::operator+(Data dat1){
	Data result(dat1);
	double addData;
	double addError;
    double w1;
    double w2;
    double y1w1;
    double y2w2;
    /*
    The accepted intervall is the expected number of bins which,
    differ by more than one sigma (18) plus minus sigma/2
    */
    if (checkCompatibility(dat1,1)< 24  && checkCompatibility(dat1,1)> 11 ){
		for (int i = 0; i < size(); i++){
            w1 = 1./pow(error(i),2.);
            w2 = 1./pow(dat1.error(i),2.);
            y1w1 = measurement(i)*w1;
            y2w2 = dat1.measurement(i)*w2;

			addData  = (y1w1 + y2w2 )/(w1 + w2);
			addError = sqrt(1./(w1+w2));
            result.ChangeMmeasurement(i, addData);
            result.ChangeError(i, addError);
            //cout << "measurement(dat1):" << measurement(i) << " ,measurement(dat2):" << dat1.measurement(i) << ", beide:" << addData << endl;
            //cout << "error 1: " << error(i) << " ,error 2: " << dat1.error(i) << " ,beide: " << addError << endl;
	       }
    }
	else{
		cout << "Can't add the data sets " << checkCompatibility(dat1,1) << endl;
	}
	return result;
}

double Data::fit(int bin){
        double bin_center = binCenter(bin);
        double alpha = 0.005;
        double beta = -0.00001;
        double gamma = 0.08;
        double delta = 0.015;
        return alpha+beta*bin_center+gamma*exp(-delta*bin_center);
}
double Data::ChiSquare(){
    double chi = 0.;
    for (int i = 0; i < size(); i++) {
        chi += pow((measurement(i)-fit(i)) ,2.)/pow(error(i),2.);
        //cout << "measurement " << measurement(i) <<" ,error" << error(i) << endl;
    }
    return chi/52;
}
