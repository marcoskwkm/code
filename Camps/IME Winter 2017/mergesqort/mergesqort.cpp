#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

map<int, lint> mp;

lint f(int n) {
    if (n == 1) return 0;
    lint ret = n;
    if (mp.find(n) != mp.end()) return mp[n];
    lint l = 0, r = n;
    while (l < r) {
        lint m = (l + r + 1) / 2;
        if (m * m <= n) l = m;
        else r = m - 1;
    }
    return mp[n] = ret + f(l) + f(n - l);
}

int main() {
    int n;
    cin >> n;
    printf("%lld\n", f(n));
    return 0;
}
