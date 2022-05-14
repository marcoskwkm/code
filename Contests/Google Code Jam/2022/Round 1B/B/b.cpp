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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        printf("Case #%d:", t);
        int N, P;
        cin >> N >> P;
        vector<vector<lint>> custs;

        for (int n = 0; n < N; n++) {
            vector<lint> cust(P);
            read_array(cust, P);
            sort(cust.begin(), cust.end());
            custs.push_back(cust);
        }

        auto dp = make_vector<lint>(N, 2, LINF);
        dp[0][1] = custs[0][P - 1];
        for (int n = 1; n < N; n++) {
            dp[n][0] = min(dp[n - 1][0] + llabs(custs[n][P - 1] - custs[n - 1][0]),
                           dp[n - 1][1] + llabs(custs[n][P - 1] - custs[n - 1][P - 1])) +
                       custs[n][P - 1] - custs[n][0];
            dp[n][1] = min(dp[n - 1][0] + llabs(custs[n][0] - custs[n - 1][0]),
                           dp[n - 1][1] + llabs(custs[n][0] - custs[n - 1][P - 1])) +
                       custs[n][P - 1] - custs[n][0];
        }

        printf(" %lld\n", min(dp[N - 1][0], dp[N - 1][1]));
    }

    return 0;
}
