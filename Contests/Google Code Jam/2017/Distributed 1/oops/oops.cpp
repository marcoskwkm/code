#include "oops.h"
#include <bits/stdc++.h>
#include <message.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n = GetN(), m = NumberOfNodes();
    int thisId = MyNodeId();
    lint lo = LINF, hi = -LINF;
    for (int i = thisId; i < n; i++) {
        lint got = GetNumber(i);
        lo = min(lo, got);
        hi = max(hi, got);
    }
    PutLL(0, lo);
    PutLL(0, hi);
    Send(0);

    if (thisId == 0) {
        lint global_lo = LINF, global_hi = -LINF;
        for (int node = 0; node < m; node++) {
            Receive(node);
            global_lo = min(global_lo, GetLL(node));
            global_hi = max(global_hi, GetLL(node));
        }
        printf("%lld\n", global_hi - global_lo);
    }    
    return 0;
}
