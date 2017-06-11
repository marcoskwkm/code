#include "nanobots.h"
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
const int MOD = (int)1e9 + 7;

int main() {
    int qn = NumberOfNodes(), thisId = MyNodeId();
    lint N = GetNumNanobots(), range = GetRange();
    if (thisId > 0) return 0;

    lint ans = 0;
    lint cur_d = 1;
    while (1) {
        lint l = 0, r = range;
        while (l < r) {
            lint mid = (l + r + 1) / 2;
            char res = Experiment(mid, cur_d);
            if (res == 'T') l = mid;
            else r = mid - 1;
        }
        lint max_c = l;
        if (max_c == 0) break;
        l = cur_d, r = range;
        while (l < r) {
            lint mid = (l + r + 1) / 2;
            char res = Experiment(max_c, mid);
            if (res == 'T') l = mid;
            else r = mid - 1;
        }
        ans += (max_c % MOD) * ((l - cur_d + 1) % MOD) % MOD;
        ans %= MOD;
        cur_d = l + 1;
    }
    cout << ans << endl;    
    return 0;
}
