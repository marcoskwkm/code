#include "again.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MASTER = 0;
const int MOD = (int)1e9 + 7;

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    lint suma = 0, sumb = 0;
    int N = GetN();
    for (int i = thisId; i < N; i += m) {
        suma += GetA(i);
        sumb += GetB(i);
    }
    suma %= MOD;
    sumb %= MOD;
    PutLL(MASTER, suma);
    PutLL(MASTER, sumb);
    Send(MASTER);

    if (thisId == MASTER) {
        vector<lint> idxsuma, idxsumb;
        lint totala = 0, totalb = 0;
        for (int i = 0; i < m; i++) {
            Receive(i);
            lint gota = GetLL(i);
            lint gotb = GetLL(i);
            idxsuma.push_back(gota);
            idxsumb.push_back(gotb);
            totala += gota;
            totalb += gotb;
        }
        totala %= MOD;
        totalb %= MOD;
        lint ans = (totala * totalb) % MOD;
        for (int i = 0; i < m; i++) {
            int j = (m - i) % m;
            ans -= (idxsuma[i] * idxsumb[j]) % MOD;
        }
        ans = (ans % MOD + MOD) % MOD;
        printf("%lld\n", ans);
    }    
    return 0;
}
