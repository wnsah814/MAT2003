#include <iostream>
#include <vector>
#include <array>
#include <cmath>
using namespace std;
const int MAX = 3;

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
vector<double> add(vector<double> v1, vector<double> v2) {
    vector<double> tmp;
    for (int i = 0; i < v1.size(); i++) {
        tmp.push_back(v1[i] + v2[i]);
    }
    return tmp;
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

void printV(array<vector<double>, MAX> v) {
    for (int i = 0; i < v[i].size(); i++) {
        for (int j = 0; j < MAX; j++) {
            cout << v[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Enter N(dimension): ";
    cin >> N;
    array<vector<double>, MAX> V;
    array<vector<double>, MAX> U;
    array<vector<double>, MAX> E;
    for (int i = 0; i < MAX; i++) {
        cout << "Enter #" << i << " vector of V: " << endl;
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
    cout << "Matrix [V]:" << endl;
    printV(V);
    
    cout << "Matrix [U]:" << endl;
    printV(U);

    for (int i = 0; i < MAX; i++) {
        E[i] = scalarMultiple(1/norm(U[i]), U[i]);
    }
    cout << "Matrix [E]:" << endl;
    printV(E);

    return 0;
}