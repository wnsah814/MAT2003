#include <iostream>
#include <vector>
#include <cmath>
#define zeroBound 10e-10`
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

bool checkSmall(double val) {
    if (val > -1 * zeroBound && val < zeroBound) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int N;
    cout << "Enter N(dimension of vector): ";
    cin >> N;
    int MAX = N;
    vector<double> V[MAX];
    vector<double> U[MAX];
    vector<double> E[MAX];
    
    //Get N by N Matrix(N-D vectors N times) from user. 
    for (int i = 0; i < MAX; i++) {
        cout << "Enter elements of #" << i << " vector: " << endl;
        for (int j = 0; j < N; j++) {
            double tmp;
            cin >> tmp;
            V[i].push_back(tmp);
        }
    }

    //V to U
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
            cout << "#" << i << " is not independent! Enter another vector.\n";
            return 0;
        }
    }

    cout << "Orthonormal Basis Vectors by GramSchmidt Method:" << endl;
    for (int i = 0, n = -1; i < N; i++) {
        n++;
        for (int j = 0; j < MAX; j++) {
            // if (E[j][n] < 10e-10) E[j][n] = 0;
            cout << E[j][n] << " ";
        }
        cout << endl;
    }
    
    cout << "Numerical verification that E is an orthonormal set\n";
    for (int i = 0; i < MAX; i++) {
        for (int j = i; j < MAX; j++) {
            double value = innerProduct(E[i], E[j]);
            if (checkSmall(value)) value = 0;
            cout << "q" << i << " * q" << j << " = " << value << endl;
        }
    }

    return 0;
}