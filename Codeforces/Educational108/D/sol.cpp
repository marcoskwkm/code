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

    int n;
    cin >> n;
    vector<lint> a(n), b(n);
    readArray(a, n);
    readArray(b, n);

    lint start = 0;
    for (int i = 0; i < n; i++)
        start += a[i] * b[i];

    lint ans = start;
    for (int i = 0; i < n; i++) {
        lint cur = start;
        for (int l = i - 1, r = i + 1; l >= 0 && r < n; l--, r++) {
            cur -= a[l] * b[l] + a[r] * b[r];
            cur += a[l] * b[r] + a[r] * b[l];
            ans = max(ans, cur);
        }

        cur = start;
        for (int l = i, r = i + 1; l >= 0 && r < n; l--, r++) {
            cur -= a[l] * b[l] + a[r] * b[r];
            cur += a[l] * b[r] + a[r] * b[l];
            ans = max(ans, cur);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
