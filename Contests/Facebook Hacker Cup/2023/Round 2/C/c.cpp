// Heavily inspired by ffao's solution

#include <algorithm>
#include <cstdio>
#include <string>
#ifdef CLANG
#include "stdcpp.h"
#else
#include <bits/stdc++.h>
#endif
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

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

template<class T> inline vector<T> read_vector(int n) {
    vector<T> v(n);
    read_array(v, n);
    return v;
}

template<class T> vector<T> make_vector(size_t size, T initialValue) {
    return vector<T>(size, initialValue);
}

template<class T, class... Args> auto make_vector(size_t head, Args &&...rem) {
    auto inner = make_vector<T>(rem...);
    return vector<decltype(inner)>(head, inner);
}

template<class T, class C = vector<T>> inline void print_array(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? "" : " ");
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = 1, T = read(); t <= T; t++) {
        debug("t = %d\n", t);
        int N;
        cin >> N;
        auto P = read_vector<int>(N - 1);
        for_each(P.begin(), P.end(), [](int &x) { x--; });
        P.insert(P.begin(), -1);

        vector<vector<string>> M(N);

        for (auto &m: M) {
            int len;
            cin >> len;
            m = read_vector<string>(len);
        }

        vector<vector<int>> adj(N);

        for (int i = 1; i < N; i++) {
            adj[P[i]].push_back(i);
        }

        vector<unordered_set<string>> needs0(N), needs1(N);
        vector<int> leaf_cnt(N);

        auto fuckthisproblem = y_combinator([&](auto f, int v) -> void {
            for (int nxt: adj[v]) {
                f(nxt);
            }

            sort(adj[v].begin(), adj[v].end(), [&](int a, int b) {
                return needs0[a].size() + needs1[a].size() > needs0[b].size() + needs1[b].size();
            });

            for (int nxt: adj[v]) {
                leaf_cnt[v] += leaf_cnt[nxt];

                if (leaf_cnt[v] == leaf_cnt[nxt]) {
                    swap(needs0[v], needs0[nxt]);
                    swap(needs1[v], needs1[nxt]);
                    continue;
                }

                vector<string> nxt_needs0, nxt_needs1;

                for (const auto &s: needs0[nxt]) {
                    if (needs0[v].count(s)) {
                        needs0[v].erase(s);
                        nxt_needs0.push_back(s);
                    } else if (needs1[v].count(s)) {
                        needs1[v].erase(s);
                        nxt_needs1.push_back(s);
                    } else if (leaf_cnt[v] - leaf_cnt[nxt] == 1) {
                        nxt_needs1.push_back(s);
                    }
                }

                for (const auto &s: needs1[nxt]) {
                    if (needs0[v].count(s)) {
                        needs0[v].erase(s);
                        nxt_needs1.push_back(s);
                    }
                }

                // Took me a while to figure out why this is fast
                if (leaf_cnt[nxt] == 1) {
                    for (const auto &s: needs0[v]) {
                        nxt_needs1.push_back(s);
                    }
                }

                needs0[v].clear();
                needs1[v].clear();
                needs0[v].insert(nxt_needs0.begin(), nxt_needs0.end());
                needs1[v].insert(nxt_needs1.begin(), nxt_needs1.end());
            }

            if (adj[v].size() == 0) {
                leaf_cnt[v] = 1;
            }

            for (const auto &s: M[v]) {
                if (needs1[v].count(s) || leaf_cnt[v] == 1) {
                    needs1[v].erase(s);
                    needs0[v].insert(s);
                }
            }
        });

        fuckthisproblem(0);

        printf("Case #%d: %d\n", t, (int)needs0[0].size());
    }

    return 0;
}
