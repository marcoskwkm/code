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
        int n;
        cin >> n;
        vector<int> u(n), s(n);
        readArray(u, n);
        readArray(s, n);
        vector<vector<int>> uni(n, vector<int>(0));
        for (int i = 0; i < n; i++) {
            uni[u[i] - 1].push_back(s[i]);
        }
        vector<lint> ans(n, 0);

        for (vector<int> &v : uni) {
            sort(v.begin(), v.end(), greater<int>());
            vector<lint> acc(v.size());
            for (size_t i = 0; i < v.size(); i++) {
                if (i == 0)
                    acc[i] = v[i];
                else
                    acc[i] = acc[i - 1] + v[i];
            }
            for (size_t k = 1; k <= v.size(); k++) {
                ans[k - 1] += acc[v.size() - (v.size() % k) - 1];
            }
        }

        printArray<lint>(ans);
    }
    return 0;
}
