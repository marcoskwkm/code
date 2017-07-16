#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e5 + 10;
const long double EPS = 1e-18;

vector<int> divisors[MAXN];

inline int count_coprimes(int n, long double k) {
    // int n_div = lower_bound(divisors[n].begin(), divisors[n].end(), k) -
    //     divisors[n].begin();
    int len = divisors[n].size();
    int l = -1, r = len - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (divisors[n][mid] < k * n) l = mid;
        else r = mid - 1;
    }
    int n_div = l + 1;        
    int total = min<int>(n, floor(k * n));
    if (n == 1 && k > 0) total++;
    // printf("count_coprimes(%d, %.2f) = %d\n", n, k, total - n_div);
    return total - n_div;
}

lint gcd(lint a, lint b) { return b ? gcd(b, a % b) : a; }

lint count_all(int n, long double lim) {
    lint cnt = 1;
    for (int base = 1; base <= n; base++)
        cnt += count_coprimes(base, lim);
    return cnt;
}    

int main() {
    for (int n = 1; n < MAXN; n++) {
        for (int d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                if (d != 1 || n == 1) divisors[n].push_back(d);
                if (d * d < n) divisors[n].push_back(n / d);
            }
        }
        sort(divisors[n].begin(), divisors[n].end());
    }

    while (1) {
        int op, n;
        scanf("%d", &op);
        if (op == 1) {
            lint a, b;
            scanf("%d%lld%lld", &n, &a, &b);
            lint d = gcd(a, b);
            a /= d, b /= d;
            if (b > n || a > b) {
                printf("fail\n");
                continue;
            }
            printf("%lld\n", count_all(n, (long double)(a) / b - EPS));
        }
        else if (op == 0) {
            lint x;
            scanf("%d%lld", &n, &x);
            long double l = 0, r = 1;
            for (int s = 0; s < 1000; s++) {
                long double mid = (l + r) / 2;
                lint got = count_all(n, mid - EPS);
                // printf("[%.6Lf, %.6Lf]: %lld\n", l, r, got);
                if (got <= x) l = mid;
                else r = mid;
            }
            printf("count_all(%d, %.6Lf) = %lld\n", n, l - EPS, count_all(n, l - EPS));
            int a = 1, b = 0;
            long double best = INF;
            for (int base = 1; base <= n; base++) {
                int aa = round(l * base);
                int dd = gcd(aa, base);
                int ca = aa / dd, cb = base / dd;
                long double dist = fabs(l - (long double)(ca) / cb);
                if (dist < best) {
                    best = dist;
                    a = ca, b = cb;
                }
            }
            lint got = count_all(n, (long double)(a) / b - EPS);
            // printf("candidate: %d / %d, got %lld\n", a, b, got);
            if (got != x) printf("fail\n");
            else printf("%d/%d\n", a, b);                
        }
        else break;
    }        
    return 0;
}

