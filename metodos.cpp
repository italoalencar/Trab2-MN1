#include <cmath>
#include "metodos.h"
#include <iomanip>
#include <tuple>
#include <iostream>

vector<double> multiplicarMatriz(vector<vector<double>>& A, vector<double>& b) {
	int linhasMatriz = static_cast<int>(A.size());
	int colunasMatriz = static_cast<int>(A[0].size());

	int tamanhoVetor = static_cast<int>(b.size());

	if (colunasMatriz != tamanhoVetor) {
		cerr << "Erro: Dimensões incompatíveis para multiplicação de matriz por vetor." << std::endl;
		return vector<double>();
	}

	vector<double> resultado(linhasMatriz, 0.0);
	for (int i = 0; i < linhasMatriz; i++) {
		for (int j = 0; j < colunasMatriz; j++) {
			resultado[i] += A[i][j] * b[j];
		}
	}

	return resultado;
}

void printMatrix(const vector<vector<double>>& mat) {
	for (const auto& row : mat) {
		for (double val : row) {
			//cout << val << " ";
			cout << fixed << setprecision(3) << setw(8) << val;
		}
		cout << endl;
	}
}

void printVector(const vector<double>& vec) {
	cout << "d = [ ";
	for (double val : vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}


tuple<vector<double>,int> GaussJacobi(vector<vector<double>> A, vector<double> b, double ε, int iterMax) {
	int n = static_cast<int>(A.size());
	vector<double> x(n, 0);

	// Construcao da Matriz e vetor de iteracoes
	for (int i = 0; i < n; i++) {
        double r =  1 / A[i][i];
		for (int j = 0; j < n; j++) {
			if (i != j) 
				A[i][j] = A[i][j] * r;	
		}
		b[i] = b[i] * r;
		//x[i] = b[i];
	}

	cout << "\nX inicial:" << endl;
	printVector(x);

    // Iterações de Jacobi
	int k = 0;
	vector<double> v(n, 0);
	while (true) {
		k++;
		for (int i = 0; i < n;  i++) {
            double soma = 0;
			for (int j = 0; j < n;  j++) {
				if (i != j) {
					soma = soma + A[i][j] * x[j];
				}
			}
			v[i] = b[i] - soma;
		}
		double erroRelativo = CalculaErro(n, x, v);
		cout << "iteracao: " << k << endl;
		printVector(x);
		if (erroRelativo <= ε || k >= iterMax)
			break;
	}
	
	return make_tuple(x, k);

}

vector<vector<double>> InversaGaussJacobi(vector<vector<double>> A, double ε, int iterMax) {
	// Criar matriz identidade
	int n = static_cast<int>(A.size());
	vector<vector<double>> I(n, vector<double>(n, 0.0));
	for (int i = 0; i < n; i++)
		I[i][i] = 1.0;

	//A*(A^-1)i = Ii
	vector<vector<double>> inversa(n, vector<double>(n, 0.0));
	for (int j = 0; j < n; j++) {

		vector<double> colunaInversa = get<0>(GaussJacobi(A, I[j], ε, iterMax));
		for (int k = 0; k < n; k++) {
			inversa[k][j] = colunaInversa[k];
		}
		cout << "\nColuna " << j + 1 << " da Matriz Inversa adicionada:" << endl;
		printMatrix(inversa);
	}
	
	return inversa;
}

vector<double> acharDJacobi(vector<vector<double>> A, vector<double> b, double ε, int iterMax) {
	vector<vector<double>> inversa = InversaGaussJacobi(A, ε, iterMax);
	cout << "\nAqui esta a matriz Inversa de A por Jacobi:" << endl;
	printMatrix(inversa);
	vector<double> d = multiplicarMatriz(inversa, b);
	return d;
}



tuple<vector<double>, int> GaussSeidel(vector<vector<double>> A, vector<double> b, double ε, int iterMax) {
	int n = static_cast<int>(A.size());
	vector<double> x(n, 0);

	// Construcao da Matriz e vetor de iteracoes
	for (int i = 0; i < n; i++) {
		double r = 1 / A[i][i];
		for (int j = 0; j < n; j++) {
			if (i != j)
				A[i][j] = A[i][j] * r;
		}
		b[i] = b[i] * r;
		//x[i] = b[i];
	}

	cout << "\nX inicial:" << endl;
	printVector(x);

	// Iterações de Seidel
	int k = 0;
	vector<double> v(n, 0);
	while (true) {
		k++;
		for (int i = 0; i < n; i++) {
			double soma = 0;
			for (int j = 0; j < n; j++) {
				if (i != j) {
					soma = soma + A[i][j] * x[j];
				}
			}
			v[i] = x[i];
			x[i] = b[i] - soma;
		}
		double erroRelativo = CalculaErro(n, v, x);
		cout << "iteracao: " << k << endl;
		printVector(x);
		if (erroRelativo <= ε || k >= iterMax)
			break;
	}

	return make_tuple(x, k);

};

vector<vector<double>> InversaGaussSeidel(vector<vector<double>> A, double ε, int iterMax) {
	// Criar matriz identidade
	int n = static_cast<int>(A.size());
	vector<vector<double>> I(n, vector<double>(n, 0.0));
	for (int i = 0; i < n; i++)
		I[i][i] = 1.0;

	//A*(A^-1)i = Ii
	vector<vector<double>> inversa(n, vector<double>(n, 0.0));
	for (int j = 0; j < n; j++) {
		vector<double> colunaInversa = get<0>(GaussSeidel(A, I[j], ε, iterMax));

		for (int k = 0; k < n; k++) {
			inversa[k][j] = colunaInversa[k];
		}
		cout << "\nColuna " << j << " da Matriz Inversa adicionada:" << endl;
		printMatrix(inversa);
	}
	return inversa;
}

vector<double> acharDSeidel(vector<vector<double>> A, vector<double> b, double ε, int iterMax) {
	vector<vector<double>> inversa = InversaGaussSeidel(A, ε, iterMax);
	cout << "\nAqui esta a matriz Inversa de A por Seidel:" << endl;
	printMatrix(inversa);
	vector<double> d = multiplicarMatriz(inversa, b);
	return d;
}


double CalculaErro(int n, vector<double>& x, vector<double>& v) {
	double normaNum = 0;
	double normaDen = 0;

	double t;
	for (int i = 0; i < n; i++) {
		
		t = abs(v[i] - x[i]);
		if (t > normaNum) normaNum = t;
		if (abs(v[i]) > normaDen) normaDen = abs(v[i]);

		x[i] = v[i];
	};
   double erro = normaNum / normaDen;
   return erro;
};
