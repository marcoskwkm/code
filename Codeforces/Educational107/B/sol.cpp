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

    vector<lint> len(10);
    len[1] = 1;
    for (int i = 2; i < 10; i++)
        len[i] = 10 * len[i - 1];

    int t;
    for (cin >> t; t--;) {
        lint a, b, c;
        cin >> a >> b >> c;
        lint p1 = 2, p2 = 3, p3 = 5;
        lint g = p3;
        while (g < len[c])
            g *= p3;
        lint x = g, y = g;
        while (x < len[a])
            x *= p1;
        while (y < len[b])
            y *= p2;
        printArray<lint>({x, y});
    }

    return 0;
}
