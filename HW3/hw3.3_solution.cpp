#include <cstdlib>
#include <iostream>

using namespace std;

void matvec(const double* matrix, const double* vector, double* result,
	    const unsigned int mrows, const unsigned int mcols)
{
  for (unsigned int i=0; i<mcols; i++)
    {
    double accum = 0;
    for (unsigned int j=0; j<mrows; j++)
      accum += matrix[mrows*i+j]*vector[i];
    result[i] = accum;
    }
}

double norm(const double* matrix, const double* vector,
	    const unsigned int mrows, const unsigned int mcols)
{
  const unsigned int dim = mcols;
  double buffer[dim];
  double total = 0;
  matvec(matrix, vector, buffer, mrows, mcols);
  for (unsigned int k=0; k<dim; k++)
    total += buffer[k]*buffer[k];
  return total;
}


void fillmatrices(double* matrix, double* vector,
		  const unsigned int mrows, const unsigned int mcols)
{
  const char* cp = "chem281";
  unsigned int* uip = (unsigned int*) cp;
  srand(*uip);

  for (unsigned int i=0; i<mcols; i++)
  {
    for (unsigned int j=0; j<mrows; j++)
      matrix[mrows*i+j] = (double) (rand()%10000);
    vector[i] = (double) (rand()%10000);
  }
}

void printmatrices(double* matrix, 
		  const unsigned int mrows, const unsigned int mcols)
{
  for (unsigned int i=0; i<mrows; i++)
  {
    for (unsigned int j=0; j<mcols; j++)
      cout << matrix[mrows*j + i] << " ";
    cout << endl;
  }
}

int main(int argc, char* argv[])
{
  const unsigned int mrows = 20;
  const unsigned int mcols = 10;
  double* matrix = new double[mrows*mcols];
  double* rhs = new double[mcols];
  fillmatrices(matrix, rhs, mrows, mcols);
  const double res = norm(matrix, rhs, mrows, mcols);
  cout << "matrix:" <<endl;
  printmatrices(matrix, mrows, mcols);
  cout << "vector:" <<endl;
  printmatrices(rhs, 1, mcols);
  cout<<"hw3.3 result: "<<res<<endl;
  return EXIT_SUCCESS;
}

