#include <math.h>
#include <float.h>
#include <hw1.2.h>


double mssesqrt(const double squared)
{
  double root = sqrtguess(squared);
  root = rootiter(squared, root);
  return root;
}
