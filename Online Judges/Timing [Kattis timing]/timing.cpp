#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

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
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < b.m; j++)
            for (int k = 0; k < a.m; k++)
                m[i][j] += a[i][k] * b[k][j];
    return m;
}
    
template<class T> Matrix<T> operator* (T k, Matrix<T> a) {
    Matrix<T> m = a;
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.m; j++)
            m[i][j] *= k;
    return m;
}
    
vector<int> adj[MAXN];
double rem[MAXN];

int main() {
    int tt;
    for (scanf("%d", &tt); tt--;) {
        int n, m, t;
        scanf("%d%d%d", &n, &m, &t);
        Matrix<double> str(1, n);
        for (int i = 0; i < n; i++) {
            scanf("%lf", &str[0][i]);
            adj[i].clear();
            rem[i] = 1;
        }
        Matrix<double> mat(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            double p;
            scanf("%d%d%lf", &u, &v, &p);
            adj[u].push_back(v);
            adj[v].push_back(u);
            rem[u] -= p;
            mat[u][v] = p;
        }
        for (int i = 0; i < n; i++)
            mat[i][i] = rem[i];

        Matrix<double> mat2(n);
        for (int i = 0; i < n; i++)
            mat2[i][i] = 1;

        while (t) {
            if (t & 1) mat2 = mat2 * mat;
            mat = mat * mat;
            t >>= 1;
        }

        str = str * mat2;

        double ans = LINF;
        for (int i = 0; i < n; i++) {
            double got = str[0][i];
            bool foi[MAXN];
            memset(foi, 0, sizeof(foi));
            for (int nxt: adj[i]) {
                if (foi[nxt]) continue;
                got += str[0][nxt];
                foi[nxt] = 1;
            }
            ans = min(ans, got);
        }
        printf("%.9f\n", ans);
    }        
    return 0;
}
