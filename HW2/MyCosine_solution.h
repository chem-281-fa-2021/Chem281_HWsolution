#if !defined MYCOSINE__H
#define MYCOSINE_H
#include <hw2.1.h>

class MyCosine: public Derivable
{
public:
  MyCosine()  { }
  ~MyCosine() { }
  virtual complex<double> eval(const complex<double> coord);
};

#endif
