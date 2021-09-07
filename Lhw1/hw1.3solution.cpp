#include <stdexcept>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

double Combination(int n, int k)
{
  double n_d = (double)n;
  double result = 1.0;
  int k_small = min(k, n - k);
  for(double j = (double)k_small; j > 0; j--){
    result /= j;
    result *= n_d;
    n_d --;
  }
  return result;
}

int main(int argc, char* argv[])
{
  int n, k; 
  if (argc !=3) {
    printf("You need to input 2 numbers at least\n");
    return EXIT_FAILURE;
  }

  try
  {
    n = stoi(argv[1]);
    k = stoi(argv[2]);
  }
  catch (invalid_argument &e)
  {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }
  if(n < k || k < 0){
    printf("You need to input the number of elements first and it should be bigger than selection numbers.\nThe two numbers should be positive\n");
    return EXIT_FAILURE;
  }
  double result = 1e308;
  if (pow(result, 1.0/k) < n) {
    printf("The result may be bigger than the maxium of double precision\n");
    return EXIT_FAILURE;
  }
  result = Combination(n, k);
  printf("(n k) = %f\n ", result);
  return EXIT_SUCCESS;
}
