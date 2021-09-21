#if !defined MYPOTENTIAL__H
#define MYPOTENTIAL_H
#include <hw2.1.h>

class MyPotential: public Derivable
{
public:
  MyPotential()  { }
  ~MyPotential() { }
  virtual complex<double> eval(const complex<double> coord);
};

#endif
