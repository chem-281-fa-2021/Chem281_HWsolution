#if !defined HW_2_1_func_H
#define HW_2_1_func_H
#include <hw2.1.h>

class MyCosine: public Derivable
{
    public:
    MyCosine(){}
    ~MyCosine(){}
    complex<double> eval(const complex<double> coord);
};

#endif 
