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
const int MAXN = 1010;
const int MOD = (int)1e9 + 7;

template <class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    for (cin >> t; t--;) {
        int n, k;
        cin >> n >> k;
        if (k == 1) {
            cout << 1 << endl;
            continue;
        }

        vector<lint> q(n, 1);
        lint ans = n + 1;
        for (int i = k - 2; i > 0; i--) {
            lint acc = 0;
            for (int j = 0; j < n; j++) {
                lint tmp = q[j];
                q[j] = acc;
                ans = (ans + acc) % MOD;
                acc = (acc + tmp) % MOD;
            }
            reverse(q.begin(), q.end());
        }
        cout << ans << endl;
    }
    return 0;
}
