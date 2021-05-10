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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = read(); t--;) {
        int n, m;
        cin >> n >> m;
        vector<int> v(n);
        readArray(v, n);

        vector<int> cnt(m, 0);
        for_each(v.begin(), v.end(), [&](int x) { cnt[x % m]++; });

        int ans = 0;
        for (int i = 0; 2 * i <= m; i++) {
            if (i == 0 || 2 * i == m) {
                if (cnt[i] > 0) ans++;
                continue;
            }
            int x = cnt[i], y = cnt[m - i];
            int lo = min(x, y);
            if (x == 0 && y == 0) continue;
            ans++;
            ans += max(0, x + y - 2 * lo - 1);
        }

        printf("%d\n", ans);
    }
    return 0;
}
