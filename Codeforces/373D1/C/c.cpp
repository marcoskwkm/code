#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;
const int MAXN = (int)1e5 + 10;

template<class T> struct Matrix {
    static const int MAXS = 2;
    
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

    static Matrix<T> I(int n) {
        Matrix<T> Id(n);
        for (int i = 0; i < n; i++)
            Id[i][i] = 1;
        return Id;
    }
};

template<class T> Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
    Matrix<T> m(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {
            for (int k = 0; k < a.m; k++)
                m[i][j] += (a[i][k] * b[k][j]) % MOD;
            m[i][j] %= MOD;
        }
    }
    return m;
}

Matrix<lint> get_fib_matrix(int n) {
    Matrix<lint> F(2), M(2);
    F[0][0] = 1; F[0][1] = 1;
    F[1][0] = 1; F[1][1] = 0;
    M = Matrix<lint>::I(2);
    while (n) {
        if (n & 1) M = F * M;
        n >>= 1;
        F = F * F;
    }
    return M;
}

pll get_fib(int n) {
    Matrix<lint> M = get_fib_matrix(n - 1);
    return pll(M[0][0], M[1][0]);
}

pll operator+ (pll a, pll b) {
    return pll((a.first + b.first) % MOD, (a.second + b.second) % MOD);
}

int n, m;
int a[MAXN];
pll tree[4 * MAXN];
Matrix<lint> lazy[4 * MAXN](2);

void build(int i, int l, int r) {
    lazy[i] = Matrix<lint>::I(2);
    if (l == r) {
        tree[i] = get_fib(a[l]);
    }
    else {
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        build(L, l, mid);
        build(R, mid + 1, r);
        tree[i] = tree[L] + tree[R];
    }
}

void refresh(int i) {
    Matrix<lint> &M = lazy[i];
    tree[i] = pll((M[0][0] * tree[i].first + M[0][1] * tree[i].second) % MOD,
                  (M[1][0] * tree[i].first + M[1][1] * tree[i].second) % MOD);
    int L = 2 * i + 1, R = 2 * i + 2;
    if (L < 4 * n) {
        lazy[L] = lazy[L] * M;
        lazy[R] = lazy[R] * M;
    }
    M = Matrix<lint>::I(2);
}    

void update(int i, int l, int r, int ql, int qr, Matrix<lint> &M) {
    refresh(i);
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        lazy[i] = lazy[i] * M;
        refresh(i);
        return;
    }
    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    update(L, l, mid, ql, qr, M);
    update(R, mid + 1, r, ql, qr, M);
    tree[i] = tree[L] + tree[R];
}

lint query(int i, int l, int r, int ql, int qr) {
    refresh(i);
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return tree[i].first;
    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    return (query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr)) % MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    build(0, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int k, l, r, x;
        scanf("%d%d%d", &k, &l, &r);
        if (k == 1) {
            scanf("%d", &x);
            Matrix<lint> M = get_fib_matrix(x);
            update(0, 0, n - 1, l - 1 , r - 1, M);
        }
        else {
            printf("%d\n", (int)query(0, 0, n - 1, l - 1, r - 1));
        }
    }    
    return 0;
}
