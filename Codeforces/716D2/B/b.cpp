#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

// Computes b ^ e (mod m)
lint modexp(lint b, lint e, lint m) {
    lint ret = 1;
    while (e) {
        if (e & 1) ret = (ret * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return (ret % m + m) % m;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, k;
        cin >> n >> k;
        cout << modexp(n, k, MOD) << endl;
    }
    return 0;
}
