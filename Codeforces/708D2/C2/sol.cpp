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
        int n, k;
        cin >> n >> k;

        vector<int> ans;
        auto solve = y_combinator([&](auto _solve, int _n, int _k) -> void {
            if (_k == 2) {
                ans.insert(ans.end(), {_n / 2, _n / 2});
                return;
            } else if (_k == 3) {
                if (_n & 1) {
                    ans.insert(ans.end(), {1, (_n - 1) / 2, (_n - 1) / 2});
                } else if (_n % 4 == 0) {
                    ans.insert(ans.end(), {_n / 2, _n / 4, _n / 4});
                } else {
                    ans.insert(ans.end(), {2, (_n - 2) / 2, (_n - 2) / 2});
                }
                return;
            }
            ans.push_back(1);
            _solve(_n - 1, _k - 1);
        });
        solve(n, k);
        printArray<int>(ans);
    }
    return 0;
}
