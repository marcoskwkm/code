#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

lint modexp(lint b, lint e, lint m) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % m;
        aux = aux * aux % m;
        e >>= 1;
    }
    return ret;
}

int main() {
    lint n;
    cin >> n;
    cout << modexp(n, (n - 1) * (n - 1), MOD) << endl;    
    return 0;
}
