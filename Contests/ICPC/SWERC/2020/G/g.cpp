#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;
const int LOG = 20;

template<class Fun> class y_combinator_result {
    Fun fun_;

  public:
    template<class T> explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}

    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun> decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

int ndiv[MAXN];
int nxt[LOG][MAXN];
lint cst[LOG][MAXN];
bool seen[MAXN];
bool in_st[MAXN];
int st[MAXN];
int st_len = 0;
int cycle_len[MAXN];

void getCycle(int v) {
    int len = 1;
    int cur = nxt[0][v];
    while (cur != v) {
        len++;
        cur = nxt[0][cur];
    }
    cycle_len[v] = len;
    cur = nxt[0][v];
    while (cur != v) {
        cycle_len[cur] = len;
        cur = nxt[0][cur];
    }
}

void walk(int v) {
    st[st_len++] = v;
    in_st[v] = 1;
    seen[v] = 1;

    int to = nxt[0][v];
    if (seen[to] && in_st[to]) {
        getCycle(to);
    } else if (!seen[to]) {
        walk(to);
    }

    in_st[v] = 0;
    st_len--;
}

pll get(int v, int d) {
    lint cost = 0;
    int cur = v;
    for (int i = LOG - 1; i >= 0; i--) {
        if ((1 << i) <= d) {
            d -= (1 << i);
            cost += cst[i][cur];
            cur = nxt[i][cur];
        }
    }
    return pll(cur, cost);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ndiv[0] = 0;
    for (int d = 1; d < MAXN; d++)
        for (int m = d; m < MAXN; m += d)
            ndiv[m]++;

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        nxt[0][i] = (i + ndiv[i]) % n;
        cst[0][i] = nxt[0][i];
    }
    for (int i = 1; i < LOG; i++) {
        for (int v = 0; v < n; v++) {
            nxt[i][v] = nxt[i - 1][nxt[i - 1][v]];
            cst[i][v] = cst[i - 1][v] + cst[i - 1][nxt[i - 1][v]];
        }
    }

    memset(cycle_len, -1, sizeof(cycle_len));
    for (int v = 0; v < n; v++) {
        if (!seen[v]) {
            walk(v);
        }
    }

    // for (int v = 0; v < n; v++) {
    //     auto end = get(v, k - 1);
    //     printf("%d (%d): %d (%lld)\n", v, nxt[0][v], cycle_len[v], end.second);
    // }

    lint ans = LINF;
    int at = -1;
    for (int v = 0; v < n; v++) {
        auto end = get(v, k - 1);
        // printf("%d: %d\n", v, end.first);
        if (cycle_len[end.first] != -1 && cycle_len[end.first] <= k - 1) {
            auto end2 = get(v, k - 1 - cycle_len[end.first]);
            if (cycle_len[end2.first] != -1) {
                continue;
            }
        }
        if (v + end.second < ans) {
            ans = v + end.second;
            at = v;
        }
    }

    if (at == -1) {
        printf("-1\n");
        // for (int v = 0; v < n; v++) {
        //     bool ok = 1;
        //     memset(seen, 0, sizeof(seen));
        //     int cur = v;
        //     for (int u = 0; u < k; u++) {
        //         if (seen[cur]) {
        //             ok = 0;
        //             break;
        //         }
        //         seen[cur] = 1;
        //         cur = nxt[0][cur];
        //     }
        //     if (ok) {
        //         printf("found start %d\n", v);
        //         return 0;
        //     }
        // }
    } else {
        lint sum = 0;
        for (int i = 0; i < k; i++) {
            printf("%d ", at);
            sum += at;
            at = nxt[0][at];
        }
        assert(sum == ans);
        printf("\n");
    }
    return 0;
}
