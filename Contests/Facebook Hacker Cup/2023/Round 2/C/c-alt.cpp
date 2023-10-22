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
        unordered_map<string, int> freq;
        unordered_set<string> all;

        for (auto &m: M) {
            int len;
            cin >> len;
            m = read_vector<string>(len);
            for_each(m.begin(), m.end(), [&](auto &w) { freq[w]++; });
            all.insert(m.begin(), m.end());
        }

        vector<vector<int>> adj(N);

        for (int i = 1; i < N; i++) {
            adj[P[i]].push_back(i);
        }

        int leaf_cnt = count_if(adj.begin(), adj.end(), [](auto &v) { return v.empty(); });

        unordered_map<string, int> id;

        for (const auto &w: all) {
            id[w] = id.size();
        }

        vector<vector<int>> intM;

        for (const auto &sv: M) {
            vector<int> iv;
            for (const auto &w: sv) {
                iv.push_back(id[w]);
            }
            intM.push_back(iv);
        }

        vector<int> last(id.size(), -1);
        vector<vector<int>> cnt(id.size());
        vector<int> cands;

        for (const auto &[w, f]: freq) {
            if (f >= leaf_cnt) {
                cands.push_back(id[w]);
            }
        }

        auto fuckthisproblem = y_combinator([&](auto f, int v) -> void {
            vector<pii> prv;

            for (int w: intM[v]) {
                prv.push_back({w, last[w]});
                last[w] = v;
            }

            for (int nxt: adj[v]) {
                f(nxt);
            }

            if (adj[v].empty()) {
                for (int w: cands) {
                    if (last[w] != -1) {
                        cnt[w].push_back(last[w]);
                    }
                }
            }

            for (auto &[w, l]: prv) {
                last[w] = l;
            }
        });

        fuckthisproblem(0);

        int ans = count_if(cnt.begin(), cnt.end(), [&](auto &v) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            return (int)v.size() == leaf_cnt;
        });

        printf("Case #%d: %d\n", t, ans);
    }

    return 0;
}
