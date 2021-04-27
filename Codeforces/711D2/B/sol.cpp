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
        int n, w;
        cin >> n >> w;
        vector<int> freq(20, 0);
        vector<int> rect(n);
        readArray(rect, n);
        for_each(rect.begin(), rect.end(), [&](int x) { freq[__builtin_ctz(x)]++; });

        int ans = 0;
        int cnt = 0;
        while (cnt < n) {
            ans++;
            int rem = w;
            for (int i = 19; i >= 0; i--) {
                while (freq[i] > 0 && (1 << i) <= rem) {
                    rem -= (1 << i);
                    freq[i]--;
                    cnt++;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
