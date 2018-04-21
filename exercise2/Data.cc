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
double Data::DeltaY (Data dat2, int bin){ return std::abs(dat2.measurement(bin)-m_data[bin]); }
double Data::DeltaYError (Data dat2, int bin) { return std::abs(dat2.error(bin)-m_error[bin]); }
int Data::checkCompatibility(Data dat2, int n) {
    int NumberOfDataPoints = 0;
    for (int i=0; i < m_data.size(); i++){
        if (DeltaY (dat2, i) < n*DeltaYError(dat2, i)) {NumberOfDataPoints += 1;}
    }
    return NumberOfDataPoints;
}
Data Data::operator+(Data dat1){
	Data result(dat1);
	double addData;
	double addError;
	if (checkCompatibility(dat1,1)< 37 && checkCompatibility(dat1,1)> 33 ){
		for (int i = 0; i < size(); i++){
			addData  = (measurement(i)*error(i)+ dat1.measurement(i)*dat1.error(i))/(error(i)+dat1.error(i));
			addError = sqrt(1./(error(i)+dat1.error(i)));
			result.ChangeMmeasurement(i,addData);
			result.ChangeError(i,addError);
		}
	}
	else{
		cout << "Can't add the data sets " << checkCompatibility(dat1,1) << endl; 
	}
	return result;
}