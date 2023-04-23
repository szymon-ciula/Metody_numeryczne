#pragma once
inline double abso(double x) { return x>=0 ? x : -x; }
inline double max(double a, double b) { return a>=b ? a : b; }

void swap(double& a, double& b);
Vector solveEquations(const Matrix & A0, const Vector & b, double  eps);
Vector multiplyMatrixVector(const Matrix& M, const Vector& V, size_t n);
void reverseTriangularMatrix(Matrix& M, size_t n);