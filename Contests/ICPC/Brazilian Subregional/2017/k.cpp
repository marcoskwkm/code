#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 10000;

template<class T> struct Matrix {
    static const int MAXS = 2;
    
    vector<T> mat[MAXS];
    int n, m;
    Matrix(int N, int M = -1) {
        if (M == -1) M = N;
        n = N, m = M;
        for (int i = 0; i < n; i++) {
            mat[i].resize(m);
            for (int j = 0; j < m; j++)
                mat[i][j] = 0;
        }
    }
    vector<T>& operator[](int i) { return mat[i]; }
};

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {
            for (int k = 0; k < a.m; k++)
                m[i][j] += a[i][k] * b[k][j];
            m[i][j] %= MOD;
        }
    }
    return m;
}

int main() {
    lint a, b, n, k;
    cin >> a >> b >> n >> k;
    Matrix<lint> M(2), P(2);
    M.mat[0] = {2*a % MOD, (b - a*a) % MOD};
    M.mat[1] = {1, 0};
    P.mat[0] = {1, 0};
    P.mat[1] = {0, 1};

    lint on = n;
    while (n > 0) {
        if (n & 1) P = P * M;
        M = M * M;
        n >>= 1;
    }

    lint ans = (2*a*P[1][0] + 2*P[1][1]) % MOD + MOD;
    if (a * a > b  || (a * a < b && on % 2 == 0))
        ans--;
    
    string foo = to_string(ans);
    cout << foo[foo.size() - k] << endl;
    return 0;
}
