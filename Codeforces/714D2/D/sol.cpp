#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

class UnionFind {
  private:
    int pai[MAXN], rank[MAXN];
    int cnt;

  public:
    UnionFind(int size) {
        for (int a = 0; a < size; ++a) {
            pai[a] = a;
            rank[a] = 0;
        }
        cnt = size;
    }
    int find(int v) { return pai[v] = (pai[v] == v) ? v : find(pai[v]); }
    void join(int i, int j) {
        int pi = find(i), pj = find(j);
        if (pi == pj)
            return;
        --cnt;
        if (rank[pi] > rank[pj])
            pai[pj] = pi;
        else if (rank[pi] < rank[pj])
            pai[pi] = pj;
        else {
            pai[pj] = pi;
            rank[pi]++;
        }
    }
    bool isConnected(int i, int j) { return find(i) == find(j); }
    int count() { return cnt; }
};

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, p;
        scanf("%d%d", &n, &p);
        vector<int> v(n);
        readIntArray(v, n);
        UnionFind uf(n);

        vector<pii> ord(n);
        for (int i = 0; i < n; i++) {
            ord[i] = pii(v[i], i);
        }
        sort(ord.begin(), ord.end());

        lint ans = 0;
        int n_edges = 0;
        for (auto [_, idx] : ord) {
            if (v[idx] >= p) {
                break;
            }
            int div = v[idx];
            for (int l = idx - 1; l >= 0; l--) {
                if (v[l] < v[idx]) {
                    break;
                }
                div = __gcd(div, v[l]);
                if (div < v[idx]) {
                    break;
                }
                if (uf.isConnected(l, idx)) {
                    break;
                }
                uf.join(l, idx);
                ans += v[idx];
                n_edges++;
            }
            div = v[idx];
            for (int r = idx + 1; r < n; r++) {
                if (v[r] < v[idx]) {
                    break;
                }
                div = __gcd(div, v[r]);
                if (div < v[idx]) {
                    break;
                }
                if (uf.isConnected(idx, r)) {
                    break;
                }
                uf.join(idx, r);
                ans += v[idx];
                n_edges++;
            }
        }

        printf("%lld\n", ans + lint(n - 1 - n_edges) * p);
    }
    return 0;
}
