#include <iostream>
#include <vector>
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
    for (int i = 0; i < MAX; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}
vector<double> add(vector<double> v1, vector<double> v2) {
    vector<double> tmp;
    for (int i = 0; i < MAX; i++) {
        tmp.push_back(v1[i] + v2[i]);
    }
    return tmp;
}

vector<double> scalarMultiple(double scalar, vector<double> v2) {
    vector<double> tmp;
    for (int i = 0; i < MAX; i++) {
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
    vector<double> V[MAX];
    vector<double> U[MAX];
    vector<double> E[MAX];
    for (int i = 0; i < MAX; i++) {
        cout << "Enter #" << i << " vector of V: " << endl;
        for (int j = 0; j < N; j++) {
            double tmp;
            cin >> tmp;
            V[i].push_back(tmp);
        }
    }

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < i; j++) {
            U[i] = add(V[i], scalarMultiple(-1, projection(U[j], V[i])));    
        }
    }

    for (int i = 0; i < MAX; i++) {
        cout << "Elements of U #" << i << endl;
        cout << E[i][0] << " " << E[i][1] << endl;
    }

    for (int i = 0; i < MAX; i++) {
        E[i] = scalarMultiple(1/norm(U[i]), U[i]);
    }
    
    for (int i = 0; i < MAX; i++) {
        cout << "Elements of E #" << i << endl;
        cout << E[i][0] << " " << E[i][1] << endl;
    }



    return 0;
}