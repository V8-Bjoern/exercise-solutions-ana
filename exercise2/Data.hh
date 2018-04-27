#ifndef DATA_HH
#define DATA_HH

#include <vector>
#include <string>

class Data {
 public:
  Data(const std::string& filename);

  unsigned int size() const { return m_data.size(); }
  double measurement(int i) const { return m_data[i]; }
  double binCenter(int i) const { return (binLow(i)+(binHigh(i)-binLow(i))/2); }
  double binLow(int i) const { return m_bins[i]; }
  double binHigh(int i) const { return m_bins[i+1]; }
  double error(int i) const { return m_error[i]; }
  double DeltaY (Data dat2, int bin);
  double DeltaYError (Data dat2, int bin);
  void ChangeMmeasurement (int i, double x) {m_data[i]=x;}
  void ChangeError (int i, double x) {m_error[i]=x; }
  int checkCompatibility(Data dat2, int n);
  Data operator+(Data dat1);
  double fit(int bin);
  double ChiSquare();
 private:
  Data() {}  // disallow empty data set
  void assertSizes();
  std::vector<double> m_data;
  std::vector<double> m_bins;
  std::vector<double> m_error;
};

#endif
