#include <math.h>
#include <float.h>
#include <hw1.2.h>


double mssesqrt(const double squared)
{
  union
  {
    double d;
    unsigned long u;
  } leqiv = { .d=squared };
  unsigned long exponent = leqiv.u&0x7FF0000000000000;
  leqiv.u = exponent;  const double tol = DBL_EPSILON * leqiv.d;
  double root = sqrtguess(squared);
  do
    {
    root += 0.5e+00*(squared-root*root)/root;
    } while (fabs(squared - root*root) > tol);
  return root;
}
