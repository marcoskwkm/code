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
const int MOD = 998244353;
const int NTHREADS = 16;

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

struct TestCase {
    int id;
    int N;
    vector<string> S;

    lint ans;

    TestCase(int _id) : id(_id) {}

    void read_input() {
        cin >> N;
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            S.push_back(s);
        }
    }
};

vector<TestCase> cases;

inline lint calc(const bitset<100> &s, int len) {
    lint ret = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (s.test(i))
            ret = (26 * ret + 26) % MOD;
        else
            ret += 1;
    }
    return ret + 1;
}

void solve(int _id) {
    for (int id = _id; id < (int)cases.size(); id += NTHREADS) {
        debug("Solving %d\n", id);
        auto &tc = cases[id];
        lint ans = 0;
        vector<bitset<100>> inter(1 << tc.N); // 1 if ?
        vector<int> len(1 << tc.N, 100);
        vector<char> ref(1 << tc.N);

        for (int mask = 1; mask < (1 << tc.N); mask++) {
            int j = 31 - __builtin_clz(mask);
            if (__builtin_popcount(mask) == 1) {
                len[mask] = tc.S[j].size();
                continue;
            }
            int submask = mask ^ (1 << j);
            len[mask] = min<int>(tc.S[j].size(), len[submask]);
        }

        for (int i = 0; i < 100; i++) {
            bool keep = 0;
            for (int mask = 1; mask < (1 << tc.N); mask++) {
                if (i >= len[mask])
                    continue;

                int j = 31 - __builtin_clz(mask);

                if (__builtin_popcount(mask) == 1) {
                    ref[mask] = tc.S[j][i];
                    inter[mask].set(i, tc.S[j][i] == '?');
                    keep = 1;
                    continue;
                }

                int submask = mask ^ (1 << j);
                len[mask] = min(len[mask], len[submask]);
                if (i >= len[mask]) {
                    continue;
                }

                keep = 1;

                if (tc.S[j][i] == '?' && ref[submask] == '?') {
                    inter[mask].set(i, 1);
                    ref[mask] = '?';
                } else if (tc.S[j][i] == '?') {
                    inter[mask].set(i, 0);
                    ref[mask] = ref[submask];
                } else if (ref[submask] == '?') {
                    inter[mask].set(i, 0);
                    ref[mask] = tc.S[j][i];
                } else if (tc.S[j][i] == ref[submask]) {
                    inter[mask].set(i, 0);
                    ref[mask] = tc.S[j][i];
                } else {
                    len[mask] = i;
                }
            }
            if (!keep)
                break;
        }

        for (int mask = 1; mask < (1 << tc.N); mask++) {
            lint got = calc(inter[mask], len[mask]);
            if (__builtin_popcount(mask) % 2 == 1)
                ans = (ans + got) % MOD;
            else
                ans = (ans - got + MOD) % MOD;
        }
        tc.ans = ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        TestCase tc(t);
        tc.read_input();
        cases.push_back(tc);
    }

    vector<thread> threads;
    for (int i = 0; i < NTHREADS; i++)
        threads.emplace_back(solve, i);
    for (auto &thread: threads)
        thread.join();

    for (auto &tc: cases) {
        cout << "Case #" << tc.id << ": " << tc.ans << '\n';
    }

    return 0;
}
