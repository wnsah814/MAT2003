#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

double norm(vector<double>& v) {
    double sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

double innerProduct(vector<double> v1, vector<double> v2) {
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

vector<double> subtract(vector<double> v1, vector<double> v2) {
    vector<double> tmp;
    for (int i = 0; i < v1.size(); i++) {
        tmp.push_back(v1[i] - v2[i]);
    }
    return tmp;
}

vector<double> scalarMultiple(double scalar, vector<double> v2) {
    vector<double> tmp;
    for (int i = 0; i < v2.size(); i++) {
        tmp.push_back(scalar * v2[i]);
    }
    return tmp;
}

vector<double> projection(vector<double> v1, vector<double> v2) {
    return scalarMultiple(innerProduct(v1, v2) / innerProduct(v1,v1), v1);
}

int main() {
    int N;
    cout << "Enter N(dimension): ";
    cin >> N;
    int MAX;
    cout << "Enter M: ";
    cin >> MAX;
    vector<double> V[MAX];
    vector<double> U[MAX];
    vector<double> E[MAX];
    // array<vector<double>, MAX> V;
    // array<vector<double>, MAX> U;
    // array<vector<double>, MAX> E;
    
    for (int i = 0; i < MAX; i++) {
        cout << "Enter elements of #" << i << " vector: " << endl;
        for (int j = 0; j < N; j++) {
            double tmp;
            cin >> tmp;
            V[i].push_back(tmp);
        }
    }

    for (int i = 0; i < MAX; i++) {
        U[i] = V[i];
        for (int j = 0; j < i; j++) {
            U[i] = subtract(U[i], projection(U[j], V[i]));    
        }
    }

    //Normalize
    for (int i = 0; i < MAX; i++) {
        E[i] = scalarMultiple(1/norm(U[i]), U[i]);
    }

    //Check Linearly Independent
    for (int i = 0; i < MAX; i++) {
        if (norm(U[i]) == 0) {
            cout << i << "th is not independent! Enter another vector.\n";
            return 0;
        }
    }

    cout << "Orthonormal Basis Vectors by GramSchmidt Method:" << endl;
    for (int i = 0, n = -1; i < N; i++) {
        n++;
        for (int j = 0; j < MAX; j++) {
            cout << E[j][n] << " ";
        }
        cout << endl;
    }
    
    cout << "Numerical verification that E is an orthonormal set\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = i; j < MAX; j++) {
            cout << "q" << i << " * q" << j << " = " << innerProduct(E[i], E[j]) << endl;
        }
    }

    return 0;
}