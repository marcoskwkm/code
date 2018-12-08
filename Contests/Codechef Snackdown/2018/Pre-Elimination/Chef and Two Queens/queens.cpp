#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

// 1-indexado
int count_seen(int qr, int qc, int kr, int kc, int n, int m) {
    int ret = 0;
    // horizontal
    if (qr != kr) ret += m - 1;
    else {
        if (qc < kc) ret += kc - 2;
        else ret += m - kc - 1;
    }
    // debug("%d\n", ret);

    // vertical
    if (qc != kc) ret += n - 1;
    else {
        if (qr < kr) ret += kr - 2;
        else ret += n - kr - 1;
    }
    // debug("%d\n", ret);

    // diagonal r+c
    int c_lo = max(1, qc - (n - qr)), c_hi = min(m, qc + qr - 1);
    // debug("%d - %d\n", c_lo, c_hi);
    if (qr + qc != kr + kc) {
        ret += c_hi - c_lo;
    }
    else {
        if (qc < kc) ret += kc - c_lo - 1;
        else ret += c_hi - kc - 1;
    }
    // debug("%d\n", ret);

    // diagonal r-c
    c_lo = max(1, qc - qr + 1), c_hi = min(m, qc + n - qr);
    // debug("%d - %d\n", c_lo, c_hi);
    if (qr - qc != kr - kc) {
        ret += c_hi - c_lo;
    }
    else {
        if (qc < kc) ret += kc - c_lo - 1;
        else ret += c_hi - kc - 1;
    }
    // debug("%d\n", ret);
    return ret;
}
    

int main() {
    while (1) {
        int qr, qc, kr, kc, n, m;
        cin >> qr >> qc >> kr >> kc >> n >> m;
        printf("%d\n", count_seen(qr, qc, kr, kc, n, m));
    }
    return 0;
}
