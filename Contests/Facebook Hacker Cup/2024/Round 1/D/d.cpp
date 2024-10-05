// I hate this contest format

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

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        string S;
        int K;
        cin >> S >> K;
        int n = S.size();
        vector<lint> dp(n + 1, 0);
        vector<int> maxd(n + 1, 9);
        dp[n] = 1;

        for (int i = n - 1; i >= 0; i--) {
            if (S[i] == '0') continue;

            // single digit
            dp[i] += dp[i + 1];

            // two digits
            if (i + 1 >= n || (isdigit(S[i]) && S[i] >= '3')) continue;
            if (S[i] == '2') {
                if (isdigit(S[i + 1]) && S[i + 1] >= '7') continue;
                dp[i] += dp[i + 2];
            } else if (S[i] == '1') {
                dp[i] += dp[i + 2];
            } else {
                dp[i] += dp[i + 2];
            }
        }

        auto dp2 = make_vector<lint>(n + 1, 10, 0LL);
        for (int i = n; i >= 0; i--) {
            for (int hi = 1; hi <= 9; hi++) {
                if (i == n) {
                    dp2[i][hi] = 1;
                    continue;
                }

                if (isdigit(S[i])) {
                    if (S[i] >= '3') {
                        dp2[i][hi] += dp2[i + 1][9];
                    } else if (S[i] == '2') {
                        dp2[i][hi] += dp2[i + 1][6];
                    } else if (S[i] == '1') {
                        dp2[i][hi] += dp2[i + 1][9];
                    } else if (S[i] == '0') {
                        dp2[i][hi] += dp2[i + 1][9];
                    }

                    dp2[i][hi] = min<lint>(dp2[i][hi], 1e9);
                    continue;
                } 

                if (i + 1 == n) {
                    dp2[i][hi] = hi;
                    continue;
                }

                if (isdigit(S[i + 1])) {
                    if (S[i + 1] >= '7') {
                        dp2[i][hi] += dp2[i + 2][9];
                    } else if (S[i + 1] == '2') {
                        dp2[i][hi] += min(hi, 2) * dp2[i + 2][6];
                    } else {
                        dp2[i][hi] += min(hi, 2) * dp2[i + 2][9];
                    }
                    
                    dp2[i][hi] = min<lint>(dp2[i][hi], 1e9);
                    continue;
                }

                for (int l = 1; l <= min(hi, 2); l++) {
                    for (int r = 1; r <= 9; r++) {
                        if (i + 2 < n && r >= 3) continue;
                        if (l == 2 && r >= 7) continue;
                        if (r == 2) dp2[i][hi] += dp2[i + 2][6];
                        else dp2[i][hi] += dp2[i + 2][9];
                    }
                }

                dp2[i][hi] = min<lint>(dp2[i][hi], 1e9);
            }
        }

        string sol = S;
        lint passed = 0;
        int hi = 9;

        for (int i = 0; i < n; i++) {
            if (isdigit(sol[i])) {
                if (sol[i] == '2') hi = 6;
                else hi = 9;
                continue;
            }
            for (int d = hi; d >= 0; d--) {
                if (i + 1 < n && dp[i + 2] > 0 && d >= 3) continue;

                lint cnt = 0;
                if (d == 2) {
                    if (i + 1 == n || S[i + 1] == '?' || S[i + 1] < '7') {
                        cnt = dp2[i + 1][6];
                    } else cnt = 0;
                }
                else {
                    cnt = dp2[i + 1][9];
                }

                if (passed + cnt >= K) {
                    sol[i] = d + '0';
                    if (d == 2) hi = 6;
                    else hi = 9;
                    break;
                } else {
                    passed += cnt;
                }
            }
        }

        printf("Case #%d: %s %lld\n", t, sol.c_str(), dp[0]);
    }

    return 0;
}
