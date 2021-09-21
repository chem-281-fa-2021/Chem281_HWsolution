#if !defined MyPotential_H
#define MyPotential_H
#include <hw2.1.h>

class MyPotential: public Derivable
{
    public:
    MyPotential(){}
    ~MyPotential(){}
    complex<double> eval(const complex<double> coord);
};

#endif //MyPotential_H
