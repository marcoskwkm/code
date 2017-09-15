#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 9;

template<class T> struct Matrix {
    vector<vector<T>> mat;
    int n, m;
    Matrix(int N, int M = -1) {
        if (M == -1) M = N;
        n = N, m = M;
        mat = vector<vector<T>>(n, vector<T>(m, 0));
    }
    vector<T>& operator[](int i) { return mat[i]; }
};

template<class T> Matrix<T> operator+ (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] += b[i][j];
    return m;
}

template<class T> Matrix<T> operator- (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] -= b[i][j];
    return m;
}

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {            
            if (a[i][j] == 0) continue;
            for (int k = 0; k < a.m; k++) {
                // if (a[i][k] == 0 || b[k][j] == 0) continue;
                // m[i][j] += a[i][k] * b[k][j];
                // m[i][j] %= MOD;
                if (b[j][k] == 0) continue;
                m[i][k] += a[i][j] * b[j][k];
                m[i][k] %= MOD;
            }
        }
    }
    return m;
}
    
int main() {
    int t;
    for (cin >> t; t--;) {
        int n, m;
        scanf("%d%d", &n, &m);
        Matrix<lint> adj(1 << (2 * n));
        for (int c0 = 0; c0 < (1 << n); c0++) {
            for (int c1 = 0; c1 < (1 << n); c1++) {
                int mask_from = (c0 << n) | c1;
                for (int mask = 0; mask < (1 << n); mask++) {
                    if (mask & c0) continue;
                    int nxt0 = c1, nxt1 = 0;
                    for (int r = 0; r < n; r++) {
                        if (mask & (1 << r)) {
                            if (r - 2 >= 0) nxt0 |= (1 << (r - 2));
                            if (r + 2 < n) nxt0 |= (1 << (r + 2));
                            if (r - 1 >= 0) nxt1 |= (1 << (r - 1));
                            if (r + 1 < n) nxt1 |= (1 << (r + 1));
                        }
                    }
                    int mask_to = (nxt0 << n) | nxt1;
                    adj[mask_from][mask_to] += 1;
                }
            }
        }

        Matrix<lint> pow = adj, sol(1 << (2 * n));
        for (int i = 0; i < (1 << (2 * n)); i++)
            sol[i][i] = 1;

        while (m) {
            if (m & 1) sol = sol * pow;
            pow = pow * pow;
            m >>= 1;
        }

        lint ans = 0;
        for (int i = 0; i < (1 << (2 * n)); i++)
            ans = (ans + sol[0][i]) % MOD;
        cout << ans << endl;
    }            
    return 0;
}
