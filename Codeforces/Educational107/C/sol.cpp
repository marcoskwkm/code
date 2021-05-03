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

    int n, q;
    cin >> n >> q;
    vector<int> pos(51);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (!pos[x])
            pos[x] = i;
    }

    vector<int> queries(q);
    readArray(queries, q);
    for_each(queries.begin(), queries.end(), [&](int &t) {
        int c = t;
        t = pos[c];
        for (int i = 1; i <= 50; i++) {
            if (i == c) {
                pos[i] = 1;
            } else {
                if (pos[i] < t) {
                    pos[i]++;
                }
            }
        }
    });
    printArray<int>(queries);

    return 0;
}
