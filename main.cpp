/* Author: Francisco Chima Sanchez
   Created: 2016-04-05
   Last Modified: 2017-04-05 */

/* This short program determines, for a finite set of numbers in the interval [0,1],
the Lagrange interpolating polynomial P(x) for a given set of nodes (x, f(x)) defined over
this interval. A formatted table of these polynomial values is printed. */

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Declaration of global variables 
const int N = 100; // number of discrete values over which the polynomial is defined
const int SIZE = 10; // number of nodes

// Function prototypes for calculations involved for interpolating polynomial
double interpolant(double, double[10][2]);
double multiplier(double, double[10][2], int);

int main()
{
  // Declaration of arrays to hold polynomial values
  double sampled_x[N]; // Discrete domain x
  double sampled_y[N]; // Discrete range P(x)
  
  // List of nodes for which we wish to interpolate, given as 2D array with rows (x, f(x))
  double NODES[10][2] = { {0.0, 2.3}, {0.1, 4.5}, {0.2, 4.3}, {0.3, 4.1}, {0.4, 6.7}, {0.5, 6.5}, {0.6, 6.2}, {0.7, 10.5}, {0.8, 10.2}, {0.9, 9.8} };
  
  // Generates discrete domain of 100 equidistant values in the interval [0,1]
  for (int i = 0; i < N; i++)
  {
    sampled_x[i] = i * 0.01;
  }
  
  // Prints table header
  cout << "x" << '\t' << "P(x)" << endl;
  cout << "-------------" << endl;
  
  // Generates discrete range for 100 values for the Lagrange interpolating polynomial
  for (int k = 0; k < N; k++)
  {
    sampled_y[k] = interpolant(sampled_x[k], NODES); 
    
    // Prints table of domain and range values
    cout << fixed << setprecision(2) << sampled_x[k] << '\t';
    cout << internal << setprecision(3) <<sampled_y[k] << endl;
  }
  return 0;
}

/* This function returns the Lagrange polynomial evaluated at a given x value, labelled sample, using the nodes given. */
double interpolant(double sample, double NODES[10][2])
{
  // Declaration of array to hold Lagrange coefficients and polynomial value
  double coefficients[SIZE];
  double polynomial = 0;
  
  // Generates coefficients and puts polynomial together in a sum P(x)
  for (int j = 0; j < SIZE; j++)
  {
    coefficients[j] = multiplier(sample, NODES, j);
    polynomial += coefficients[j] * NODES[j][1];
  }
  
  // Returns P(x)
  return polynomial;
}

/* This function generates the coefficients for the k-th Lagrange interpolant evaluated at the point x, labelled sample, using the nodes. */
double multiplier(double sample, double NODES[10][2], int k)
{
  // Declaration of variable storing the multiplier value
  double ell = 1;
  
  // Generates the product of binomials for L_{n,k}
  for (int i = 0; i < SIZE; i++)
  {
    // Skip the i-th term in the loop to avoid division by zero
    if (i == k)
    {
      continue;
    }
    // Multiply on the k-th rational expression in L_{n,k}
    else
    {
      ell *= (sample - NODES[i][0])/(NODES[k][0] - NODES[i][0]);
    }
  }
  // Returns L_{n,k}(x)
  return ell;
}
