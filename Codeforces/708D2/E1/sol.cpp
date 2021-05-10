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
const int MAXV = (int)1e7 + 10;

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

    auto getSqFree = [](int x) {
        int sq_free = 1;
        for (int d = 2; d * d <= x; d++) {
            if (x % d == 0) {
                int cnt = 0;
                do {
                    x /= d;
                    cnt++;
                } while (x % d == 0);
                if (cnt & 1) sq_free *= d;
            }
        }
        if (x > 1) sq_free *= x;
        return sq_free;
    };

    for (int t = read(); t--;) {
        int n, k;
        cin >> n >> k;
        vector<int> v(n);
        readArray(v, n);

        set<int> s;
        int ans = 1;
        for (auto x: v) {
            int sq_free = getSqFree(x);
            if (s.find(sq_free) != s.end()) {
                ans++;
                s.clear();
            }
            s.insert(sq_free);
        }

        printf("%d\n", ans);
    }

    return 0;
}
