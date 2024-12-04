#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Matrix-Vector Multiplication
// computes the result of A * vec and store in result
void MatrixVectorMultiply(const vector<vector<double>> &A, 
                          const vector<double> &vec, 
                          vector<double> &result) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    result.assign(rows, 0.0); // initialize result vector
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += A[i][j] * vec[j];
        }
    }
};

// Dot Product
// computes the dot product of two vectors
double DotProduct(const vector<double> &vec1, const vector<double> &vec2) {
    double result = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
};

// Vector Update
// updates vec1 with vec1 +/- scalar * vec2
void VectorUpdate(vector<double> &vec1, const vector<double> &vec2, 
                  double scalar, bool add = true) {
    for (size_t i = 0; i < vec1.size(); ++i) {
        vec1[i] += (add ? scalar * vec2[i] : -scalar * vec2[i]);
    }
};

// Vector Norm
// computes the Euclidean norm of a vector
double Norm(const vector<double> &vec) {
    return sqrt(DotProduct(vec, vec));
}

// Main Conjugate Gradient Solver
// solves Ax = b using the Conjugate Graduent method
void ConjugateGradientSolver(const vector<vector<double>> &A,
                             const vector<double> &b,
                             vector<double> &x,
                             double tol = 1e-10) {
    size_t n = b.size(); // size of the system

    // initialize residual vector: r_0 = b - A * x
    std::vector<double> residual(n), search_direction(n), temp(n);
    MatrixVectorMultiply(A, x, temp); // temp = A * x
    for (size_t i = 0; i < n; ++i) {
        residual[i] = b[i] - temp[i];
    }

    // initialize search direction: p_0 = r_0
    search_direction = residual;

    // compute initial residual norm
    double old_resid_norm = Norm(residual);
    double new_resid_norm;

    // iterate until convergence
    while (old_resid_norm > tol) {
        // compute A * search_direction
        MatrixVectorMultiply(A, search_direction, temp);

        // compute step size: alpha = (r_k^T r_k) / (p_k^T A p_k)
        double step_size = old_resid_norm * old_resid_norm / DotProduct(search_direction, temp);

        // update solution: x_{k+1} = x_k + alpha * p_k
        VectorUpdate(x, search_direction, step_size, true);

        // update residual: r_{k+1} = r_k - alpha * A * p_k
        VectorUpdate(residual, temp, step_size, false);

        // compute new residual norm
        new_resid_norm = Norm(residual);

        // update search direction: p_{k+1} = r_{k+1} + beta * p_k
        double beta = (new_resid_norm / old_resid_norm) * (new_resid_norm / old_resid_norm);
        for (size_t i = 0; i < n; ++i) {
            search_direction[i] = residual[i] + beta * search_direction[i];
        }

        // update old residual norm for the next iteration
        old_resid_norm = new_resid_norm;
    }
};

int main() {
    // example usage: solving Ax = b
    vector<vector<double>> A = {{4, 1}, {1, 3}}; // symmetric positive-definite matrix
    vector<double> b = {1, 2}; // right-hand side vector
    vector<double> x = {0, 0}; // initial guess for solution

    // solve Ax = b using Conjugate Gradient
    ConjugateGradientSolver(A, b, x);

    // print the solution vector
    cout << "Solution: ";
    for (const auto &xi : x) {
        cout << xi << " ";
    }
    cout << endl;

    return 0;

}