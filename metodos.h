#pragma once
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
tuple<vector<double>, int> GaussJacobi(vector<vector<double>> A, vector<double> b, double ε, int iterMax);
tuple<vector<double>, int> GaussSeidel(vector<vector<double>> A, vector<double> b, double ε, int iterMax);
vector<vector<double>> InversaGaussJacobi(vector<vector<double>> A, double ε, int iterMax);
vector<double> acharDJacobi(vector<vector<double>> A, vector<double> b, double ε, int iterMax);
vector<vector<double>> InversaGaussSeidel(vector<vector<double>> A, double ε, int iterMax);
vector<double> acharDSeidel(vector<vector<double>> A, vector<double> b, double ε, int iterMax);
double CalculaErro(int n, vector<double>& x, vector<double>& v);
vector<double> multiplicarMatriz(vector<vector<double>>& A, vector<double>& b);
void printMatrix(const vector<vector<double>>& mat);
void printVector(const vector<double>& vec);
