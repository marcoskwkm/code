#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;

template<class T> struct StaticRMQ {
    static const int LOG = 20;
    vector<T> rmq[LOG];
    int n;

    StaticRMQ(const vector<T> &v) : n(v.size()) {
        for (int i = 0; i < LOG; i++)
            rmq[i].resize(n);
        for (int i = 0; i < n; i++)
            rmq[0][i] = v[i];
        for (int k = 1; k < LOG; k++)
            for (int i = 0; i < n; i++)
                rmq[k][i] = min(rmq[k - 1][i], rmq[k - 1][min(n - 1, i + (1 << (k - 1)))]);
    }

    T get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }
};

int n;
vector<int> label;

int get_rmq(StaticRMQ<int> &rmq, int l, int r) {
    if (l <= r) return rmq.get(l, r);
    return min(rmq.get(l, n - 1), rmq.get(0, r));
}

inline int prv(int i) { return i == 0 ? n - 1 : i - 1; }
inline int nxt(int i) { return i + 1 == n ? 0 : i + 1; }

void solve(int l, int r, vector<tiii> &sol, StaticRMQ<int> &rmq) {
    // debug("solve %d %d\n", l, r);
    int length = r - l + 1;
    if (l > r) length = n - (l - r - 1);
    if (length < 3) return;
    int low = get_rmq(rmq, nxt(l), prv(r));
    int ll = nxt(l), rr = prv(r);
    while (ll != rr) {
        int len = rr - ll;
        if (ll > rr) len = n - (ll - rr);
        int m;
        if (label[l] < label[r]) m = rr - len / 2;
        else m = ll + len / 2;
        m = (m + n) % n;
        // debug("bs %d %d %d %d\n", ll, rr, label[l] < label[r], m);
        if (label[l] < label[r]) {
            if (get_rmq(rmq, m, rr) == low) ll = m;
            else rr = prv(m);
        }
        else {
            if (get_rmq(rmq, ll, m) == low) rr = m;
            else ll = nxt(m);
        }
    }
    if (label[l] < label[r])
        sol.push_back(tiii(l, r, ll));
    else
        sol.push_back(tiii(r, l, ll));
    solve(l, ll, sol, rmq);
    solve(ll, r, sol, rmq);
}    

int main() {
    cin >> n;
    label.resize(n);
    pii low0(INF, INF), low1(INF, INF);
    for (int i = 0; i < n; i++) {
        scanf("%d", &label[i]);
        pii p(label[i], i);
        if (p < low0) {
            low1 = low0;
            low0 = p;
        }
        else if (p < low1) low1 = p;
    }
    StaticRMQ<int> rmq(label);
    vector<tiii> sol;
    solve(low0.second, low1.second, sol, rmq);
    solve(low1.second, low0.second, sol, rmq);
    sort(sol.begin(), sol.end(), [](tiii a, tiii b) {
        int a0, a1, a2, b0, b1, b2;
        tie(a0, a1, a2) = a, tie(b0, b1, b2) = b;
        return tiii(label[a0], label[a1], label[a2]) < tiii(label[b0], label[b1], label[b2]);
    });

    for (tiii t: sol) {
        int a, b, c;
        tie(a, b, c) = t;
        printf("%d %d %d\n", a + 1, b + 1, c + 1);
    }    
    return 0;
}
