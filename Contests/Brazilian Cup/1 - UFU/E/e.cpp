#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

template<class T> struct Matrix {
    vector< vector<T> > mat;
    int n, m;
    Matrix(int N, int M = -1) {
        if (M == -1) M = N;
        n = N, m = M;
        mat.resize(n);
        for (int i = 0; i < n; i++)
            mat[i] = vector<T>(m, 0);
    }
    vector<T>& operator[](int i) { return mat[i]; }
};

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {
            for (int k = 0; k < a.m; k++) {
                m[i][j] += a[i][k] * b[k][j];
                m[i][j] %= MOD;
            }
        }
    }
    return m;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        Matrix<lint> m(2, 2);
        m[0][0] = 1, m[0][1] = 1, m[1][0] = 1, m[1][1] = 0;
        Matrix<lint> p(2, 2);
        p[0][0] = p[1][1] = 1;
        while (n) {
            if (n & 1) p = p * m;
            m = m * m;
            n >>= 1;
        }
        cout << p[1][0] << endl;
    }                       
    return 0;
}
