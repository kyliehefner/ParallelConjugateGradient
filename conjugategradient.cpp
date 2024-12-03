#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Matrix-Vector Multiplication
void MatrixVectorMultiply(const vector<vector<double>> &A, 
                          const vector<double> &vec, 
                          vector<double> &result);

// Dot Product
double DotProduct(const vector<double> &vec1, const vector<double> &vec2);

// Vector Update
void VectorUpdate(vector<double> &vec1, const vector<double> &vec2, 
                  double scalar, bool add = true);

// Main CG Algorithm
void ConjugateGradientSolver(const vector<vector<double>> &A,
                             const vector<double> &b,
                             vector<double> &x);

int main() {


}