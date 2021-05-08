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

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = read(); t--;) {
        int n;
        cin >> n;
        vector<int> v(n);
        readArray(v, n);

        vector<tuple<int, int, int, int>> ops;
        int low_idx = min_element(v.begin(), v.end()) - v.begin();
        for (int i = low_idx - 1; i >= 0; i--) {
            ops.push_back({i + 1, low_idx + 1, v[low_idx] + low_idx - i, v[low_idx]});
        }
        for (int i = low_idx + 1; i < n; i++) {
            ops.push_back({i + 1, low_idx + 1, v[low_idx] + i - low_idx, v[low_idx]});
        }
        cout << ops.size() << endl;
        for (auto [i, j, x, y] : ops) {
            printArray<int>({i, j, x, y});
            cout.flush();
        }
    }
    return 0;
}
