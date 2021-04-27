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

lint gcd(lint a, lint b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    auto digitSum = [](lint x) {
        int s = 0;
        while (x > 0) {
            s += x % 10;
            x /= 10;
        }
        return s;
    };

    int t;
    for (cin >> t; t--;) {
        lint n;
        cin >> n;
        while (gcd(n, digitSum(n)) == 1)
            n++;
        cout << n << '\n';
    }

    return 0;
}
