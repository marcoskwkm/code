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
    vector<int> v(n);
    readArray(v, n);
    vector<pii> p;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int u = i, w = j;
            if (v[u] < v[w])
                swap(u, w);
            p.push_back(pii(u, w));
        }
    }
    sort(p.begin(), p.end(),
         [&](pii a, pii b) { return v[a.first] - v[a.second] > v[b.first] - v[b.second]; });

    for (auto [u, w] : p) {
        printf("? %d %d\n", u + 1, w + 1);
        fflush(stdout);
        string ans;
        cin >> ans;
        if (ans == "Yes") {
            printf("! %d %d\n", u + 1, w + 1);
            fflush(stdout);
            return 0;
        }
    }
    printf("! 0 0\n");
    fflush(stdout);

    return 0;
}
