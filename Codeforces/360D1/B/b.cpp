#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

lint gcd(lint a, lint b) { return b ? gcd(b, a%b) : a; }
int c[MAXN];

int getq(int n, int f) {
    int ret = 0;
    while (n % f == 0) {
        n /= f;
        ret++;
    }
    return ret;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> factors;
    int kk = k;
    for (int d = 2; d * d <= kk; d++) {
        if (kk % d == 0) {
            factors.push_back(d);
            do {
                kk /= d;
            } while (kk % d == 0);
        }
    }
    if (kk > 1) factors.push_back(kk);
    
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    bool ok = 1;
    for (int f: factors) {
        int needs = getq(k, f);
        bool found = 0;
        for (int i = 0; i < n; i++) {
            if (getq(c[i], f) >= needs) {
                found = 1;
                break;
            }
        }
        if (!found) {
            ok = 0;
            break;
        }
    }
        
    printf("%s\n", ok ? "Yes" : "No");
    return 0;
}
