#include <hw2.1.h>
#include <MyPotential.h>
#include <MyCosine.h>


std::complex<double> MyPotential::eval(const std::complex<double> r)
{
  std::complex<double> r2 = r*r;
  std::complex<double> r4 = r2*r2;
  std::complex<double> r6 = r4*r2;
  std::complex<double> one = 1;
  std::complex<double> y = (r6-one)/r6/r6;
  return y*y;
}

complex<double> MyCosine::eval(const complex<double> coord) {
    return cos(coord);
}

double firstDerivative(Derivable& Func, const double where){
    double h = 1e-9;
    complex<double> x1(where, h);
    complex<double> diff = Func.eval(x1);
    return diff.imag() / h;
}
