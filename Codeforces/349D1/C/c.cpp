#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int) 1e5 + 10;
const int SQRT = 1000;
const int MOD = (int) 1e9 + 7;

lint modexp(lint a, lint b, lint mod) {
    if (b == 0) return 1;
    lint aux = modexp(a, b/2, mod);
    if (b&1) return (((aux*aux)%mod)*a)%mod;
    return (aux*aux)%mod;
}

lint inv[2*MAXN];
char buff[MAXN];
vector<int> mem[MAXN];

int main() {
    inv[1] = 1;
    for (int i = 2; i < 2*MAXN; i++) {
        inv[i] = modexp(i, MOD - 2, MOD);
        assert(i * inv[i] % MOD == 1);
    }
    
    int m;
    scanf("%d", &m);
    scanf(" %s", buff);
    int len = strlen(buff);
    while (m--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            scanf(" %s", buff);
            len = strlen(buff);
        }
        else {
            int n;
            scanf("%d", &n);
            if (mem[len].empty()) {
                lint bin = 1;
                lint p25 = 1;
                lint cur = 0;
                for (int k = len - 1; k < MAXN; k++) {
                    cur = (26*cur + bin*p25) % MOD;
                    mem[len].push_back(cur);
                    p25 = (25 * p25) % MOD;
                    bin = bin * (k + 1) % MOD * inv[k - len + 2] % MOD;
                }
            }
            cout << (len > n ? 0 : mem[len][n - len]) << endl;
        }
    }        
    return 0;
}
