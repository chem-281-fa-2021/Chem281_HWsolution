#include <hw2.1.h>
#include <MyPotential.h>
#include <MyCosine.h>

std::complex<double> MyPotential::eval(const std::complex<double> r)
{
  std::complex<double> r2 = r*r;
  std::complex<double> r4 = r2*r2;
  std::complex<double> r6 = r4*r2;
  std::complex<double> one = 1;
  std::complex<double> y = (r4-one)/r6;
  return y;
}

std::complex<double> MyCosine::eval(const std::complex<double> r)
{
  return cos(r);
}


/********************************/
#include <stdio.h>
#include <float.h>
#include <hw2.1.h>

double firstDerivative(Derivable& d, const double r)
{
  const double sep = r != 0.e+00 ? nextafter(r, r+1)-r : 1.e-12;
  const double step = sqrt(sep/2.e+00)/2.e+00;
  std::complex<double> rinc = r+1i*step;
  double retval = d.eval(rinc).imag()/step;
  return retval;
}
