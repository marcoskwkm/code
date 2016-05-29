#include "crates.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = 110;
const int MOD = (int)1e9 + 7;
int ll[MAXM], rr[MAXM];

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    int big_n = GetNumStacks();
    if (thisId >= big_n) return 0;
    m = min(m, big_n);
    int small_n = big_n / m;
    int last_r = 0;
    for (int i = 0; i < m; i++) {
        ll[i] = last_r + 1;
        rr[i] = ll[i] + small_n - 1;
        if (i < big_n % m) rr[i]++;
        last_r = rr[i];
    }
    
    int l = ll[thisId], r = rr[thisId];

    lint local_total = 0;
    vector<lint> v(r - l + 1);
    for (int i = l; i <= r; i++) {
        v[i - l] = GetStackHeight(i);
        local_total += v[i - l];
    }
    PutLL(0, local_total);
    Send(0);

    lint global_total = 0;
    lint global_ans = 0;
    if (thisId == 0) {
        vector<lint> local_sizes(m);
        for (int i = 0; i < m; i++) {
            Receive(i);
            local_sizes[i] = GetLL(i);
            global_total += local_sizes[i];
        }

        lint q = global_total / big_n;
        lint rem = global_total % big_n;
        lint balance_l = 0;
        for (int i = 0; i < m; i++) {
            PutLL(i, global_total);
            PutLL(i, balance_l);
            Send(i);
            int il = ll[i], ir = rr[i];
            lint needs = q * (ir - il + 1) + min(ir - il + 1ll, max(0ll, rem - il + 1));
            if (balance_l > 0) global_ans += balance_l;
            else global_ans -= balance_l;
            global_ans %= MOD;
            balance_l += local_sizes[i] - needs;
        }
        assert(balance_l == 0);
    }

    lint local_ans = 0;
    Receive(0);
    global_total = GetLL(0);
    v[0] += GetLL(0);
    lint cur_bal = 0;
    lint q = global_total / big_n;
    lint rem = global_total % big_n;
    for (int i = l; i < r; i++) {
        lint needs = q + (i <= rem ? 1 : 0);
        cur_bal += v[i - l] - needs;
        if (cur_bal > 0) local_ans += cur_bal;
        else local_ans -= cur_bal;
        local_ans %= MOD;
    }

    PutLL(0, local_ans);
    Send(0);

    if (thisId == 0) {
        for (int i = 0; i < m; i++) {
            Receive(i);
            global_ans += GetLL(i);
            global_ans %= MOD;
        }
        printf("%lld\n", (global_ans % MOD + MOD) % MOD);
    }        
    
    return 0;
}
