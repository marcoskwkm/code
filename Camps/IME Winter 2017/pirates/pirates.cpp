#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef unsigned long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = -1;
const double EPS = 1e-12;

vector<int> primes;

bool safe_prod(lint a, lint b) {
    return (log(a) + log(b) < 19*log(10) + EPS) && a * b > 0;
}                             

lint n;
lint hi;
lint ans;

void go(int i, int lim, lint cur, lint nd) {
    // printf("%lld: %lld\n", cur, nd);
    if (cur > n) return;
    hi = max(hi, nd);
    int take = 0;
    while (safe_prod(cur, primes[i]) && take < lim) {
        cur *= primes[i];
        take++;
        go(i + 1, take, cur, nd * (take + 1));
    }
}

void go2(int i, int lim, lint cur, lint nd) {
    if (nd > hi) {
        ans = min(ans, cur);
        return;
    }
    int take = 0;
    while (safe_prod(cur, primes[i]) && take < lim) {
        cur *= primes[i];
        take++;
        go2(i + 1, take, cur, nd * (take + 1));
    }
}

int main() {
    for (int p = 2; p < 100; p++) {
        bool ok = 1;
        for (int d = 2; d * d <= p; d++)
            if (p % d == 0)
                ok = 0;
        if (ok) primes.push_back(p);
    }
    cin >> n;
    hi = 0;
    go(0, INF, 1, 1);
    ans = LINF;
    go2(0, INF, 1, 1);
    cout << ans << endl;
    return 0;
}
