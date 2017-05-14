#include "pancakes.h"
#include <bits/stdc++.h>
#include <message.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    lint N = GetStackSize(), D = GetNumDiners();
    lint qn = NumberOfNodes(), thisId = MyNodeId();
    if (thisId >= N) return 0;
    qn = min(qn, N);
    lint size = N / qn;
    lint l = thisId * size, r = (thisId + 1) * size - 1;
    if (thisId + 1 == qn) r = N - 1;

    lint initial = GetStackItem(l);
    lint n_rev = 0;
    lint last_pos = 0;
    for (int i = l; i <= r; i++) {
        lint x = GetStackItem(i);
        if (x < last_pos) n_rev++;
        last_pos = x;
    }
    PutLL(0, initial);
    PutLL(0, n_rev);
    PutLL(0, last_pos);
    Send(0);
    if (thisId != 0) return 0;

    lint ans = 1;
    last_pos = 0;
    for (int node = 0; node < qn; node++) {
        Receive(node);
        lint initial_pos = GetLL(node);
        if (initial_pos < last_pos) ans++;
        ans += GetLL(node);
        last_pos = GetLL(node);
    }
    cout << ans << endl;
    return 0;
}
