#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define read_array(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int N_THREADS = 100;

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

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

struct KMP {
    vector<int> pattern;
    int len;
    // f[i] = the size of longest preffix that is a suffix of p[0..i-1]
    vector<int> f;

    KMP(const vector<int> &p) {
        pattern = p;
        len = p.size();
        f.resize(len + 2);
        f[0] = f[1] = 0;
        for (int i = 2; i <= len; i++) {
            int now = f[i - 1];
            while (1) {
                if (p[now] == p[i - 1]) {
                    f[i] = now + 1;
                    break;
                }
                if (now == 0) {
                    f[i] = 0;
                    break;
                }
                now = f[now];
            }
        }
    }

    // returns a vector of indices with the beginning of each match
    vector<int> match(const vector<int> &text) {
        vector<int> ret;
        int size = text.size();
        int i = 0, j = 0;
        while (j < size) {
            if (text[j] == pattern[i]) {
                i++;
                j++;
                if (i == len) {
                    ret.push_back(j - len);
                    i = f[i];
                }
            } else if (i > 0)
                i = f[i];
            else
                j++;
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<tuple<int, int, vector<int>, vector<int>>> cases;
    int T = read();

    for (int t = 0; t < T; t++) {
        int n = read(), k = read();
        vector<int> a(n), b(n);
        read_array(a, n);
        read_array(b, n);
        cases.push_back({n, k, a, b});
    }

    vector<bool> ans(T);

    auto solve = [&](int start_idx) {
        for (int i = start_idx; i < T; i += N_THREADS) {
            debug("Case %d/%d...\n", i + 1, T);
            auto [N, K, A, B] = cases[i];
            vector<int> B2 = B;
            B2.insert(B2.end(), B.begin(), B.end());
            KMP kmp(A);
            vector<int> matches = kmp.match(B2);

            bool ok = 0;

            for (int idx: matches) {
                if (N == 2) {
                    if (idx % 2 == K % 2) {
                        ok = 1;
                        break;
                    }
                } else {
                    if (K > 1) {
                        ok = 1;
                        break;
                    } else if (K == 1 && idx % N > 0) {
                        ok = 1;
                        break;
                    } else if (K == 0 && idx == 0) {
                        ok = 1;
                        break;
                    }
                }
            }

            ans[i] = ok;
        }
    };

    vector<thread> threads;
    for (int i = 0; i < N_THREADS; i++) {
        threads.emplace_back(solve, i);
    }
    for (int i = 0; i < N_THREADS; i++) {
        threads[i].join();
    }

    for (int t = 0; t < T; t++) {
        printf("Case #%d: %s\n", t + 1, ans[t] ? "YES" : "NO");
    }

    return 0;
}
