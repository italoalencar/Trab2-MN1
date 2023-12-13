#include <iostream>
#include <vector>
#include "metodos.h"

using namespace std;

tuple<vector<vector<double>>, vector<double>> entrada() {
    int op;
    cout << "(1) Sistema de equacao padrao." << endl;
    cout << "(2) Inserir sistema." << endl;
    cout << "Digite a opcao: ";
    cin >> op;

    if (op == 1) {
        vector<vector<double>> A = { {5, 3, 1}, {5, 6, 1}, {1, 6, 7} };
        vector<double> b = { 1, 2, 3 };
        return make_tuple(A, b);
    }
    else if (op == 2) {
        int n;
        cout << "Digite o numero de deslocamentos: ";
        cin >> n;

        vector<vector<double>> A(n, vector<double>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << "Digite o valor do elemento a" << i + 1 << j + 1 << ": ";
                cin >> A[i][j];
            }
        }
        cout << "\n";

        vector<double> b(n, 0);
        for (int k = 0; k < n; k++) {
            cout << "Digite o valor constante b" << k + 1 << ": ";
            cin >> b[k];
        }

        return make_tuple(A, b);
    }
    else {
        cout << "Voce inseriu um valor invalido, tente novamente." << endl;
        return entrada();
    }
}

int main() { 
    tuple<vector<vector<double>>, vector<double>> sistema = entrada();
    vector<vector<double>> A = get<0>(sistema);
    vector<double> b = get<1>(sistema);

    double e;
    int iterMax;

    cout << "Aqui esta a Matriz A:" << endl;
    printMatrix(A);

    cout << "Digite o valor da precisao com ponto flutuante (ex: 0.05): ";
    cin >> e;

    cout << "Digite o numero maximo de iteracoes: ";
    cin >> iterMax;

    vector<double> d = acharDJacobi(A, b, e, iterMax);
    cout << "\nAqui esta a solucao de D por Jacobi" << endl;
    printVector(d);

    d = acharDSeidel(A, b, e, iterMax);
    cout << "\nAqui esta a solucao de D por Seidel" << endl;
    printVector(d);

    return 0;
}
