#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint f[MAXN];
lint q[MAXN];

int main() {
    for (int n = 1; n < MAXN; n++) {
        f[n] = 1;
        q[n] = 1;
        int nn = n;
        for (int d = 2; d * d <= nn; d++) {
            if (nn % d) continue;
            int e = 0;
            do {
                nn /= d;
                e++;                
            } while (nn % d == 0);
            if (e & 1) {
                e++;
                q[n] *= d;
            }
            for (int i = 0; i < e; i += 2)
                if (i % 2 == 0)
                    f[n] *= d;
        }
        if (nn > 1) {
            f[n] *= nn;
            q[n] *= nn;
        }
    }
    
    int n;
    scanf("%d", &n);
    lint cur = 2;
    for (int level = 1; level <= n; level++) {
        lint nxt = (level + 1) * f[level];
        // debug("level %d: cur = %lld, f = %lld, nxt = %lld\n", level, cur, f[level], nxt);
        cout << lint(level + 1) * (level + 1) * q[level] - cur / level << endl;
        cur = nxt;        
    }
            
    return 0;
}
