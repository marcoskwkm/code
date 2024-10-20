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

    int n, k;
    cin >> n >> k;
    string rep = "";
    for (int i = 0; i < k; i++) {
        for (int j = k - 1; j > i; j--) {
            rep += 'a' + i;
            rep += 'a' + j;
        }
    }
    for (int i = k - 1; i >= 0; i--)
        rep += 'a' + i;

    while (n > (int)rep.size()) {
        cout << rep;
        n -= rep.size();
    }
    cout << rep.substr(0, n) << endl;
    return 0;
}
