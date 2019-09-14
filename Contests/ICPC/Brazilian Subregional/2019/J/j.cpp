#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

template<class T> struct Matrix {
    static const int MAXS = 4;
    
    T mat[MAXS][MAXS];
    int n, m;
    Matrix(int N, int M = -1) {
        if (M == -1) M = N;
        n = N, m = M;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                mat[i][j] = 0;
    }
    T* operator[](int i) { return mat[i]; }
};

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {
            for (int k = 0; k < a.m; k++) {
                m[i][j] += (a[i][k] * b[k][j]) % MOD;
                m[i][j] %= MOD;
            }
        }
    }
    return m;
}

Matrix<lint> B(4), I(4);

Matrix<lint> go(int e) {
    if (e == 0) return I;
    Matrix<lint> M = go(e / 2);
    if (e & 1) return M * M * B;
    return M * M;
}

lint pow2(int e) {
    if (e == 0) return 1;
    lint m = pow2(e / 2);
    if (e & 1) return m * m % MOD * 2 % MOD;
    return m * m % MOD;
}

int main() {
    B[0][0] = 2;
    B[0][2] = -1;
    B[0][3] = 1;
    B[1][0] = 1;
    B[2][1] = 1;
    B[3][3] = 1;
    I[0][0] = I[1][1] = I[2][2] = I[3][3] = 1;

    lint n;
    cin >> n;

    if (n <= 3) {
        int ans;
        if (n == 1) ans = 2;
        else if (n == 2) ans = 24;
        else ans = 96;        
        cout << ans << endl;
        return 0;
    }

    Matrix<lint> M = go(n - 3);
    lint F = (M[0][0] * 9 + M[0][1] * 4 + M[0][2] + M[0][3]) % MOD;
    lint F_1 = (M[1][0] * 9 + M[1][1] * 4 + M[1][2] + M[1][3]) % MOD;
    lint F_2 = (M[2][0] * 9 + M[2][1] * 4 + M[2][2] + M[2][3]) % MOD;
    lint ans = ((F - F_1 + F_2) % MOD * pow2(n + 1)) % MOD;

    cout << (ans % MOD + MOD) % MOD << endl;    
    return 0;
}
