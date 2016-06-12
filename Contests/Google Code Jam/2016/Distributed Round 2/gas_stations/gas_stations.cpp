#include "gas_stations.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    if (thisId > 0) return 0;
    int N = GetNumKms();
    lint ans = 0;
    lint tank = GetTankSize();
    deque<pll> d;
    lint cur_gas = 0;

    for (int i = 0; i <= N; i++) {
        lint this_price;
        if (i < N) this_price = GetGasPrice(i);
        else this_price = 0;
        if (d.empty()) {
            d.push_back(pll(this_price, i));
            continue;
        }
        lint cur_pos = d.front().second;
        lint price = d.front().first;

        if (i - d.front().second > tank) {
            d.pop_front();
            lint dist = d.front().second - cur_pos;
            ans += (tank - cur_gas) * price;
            cur_gas = tank - dist;
            cur_pos = d.front().second;
            price = d.front().first;
        }

        while (d.size() > 1 && d.back().first >= this_price)
            d.pop_back();
        if (d.front().first >= this_price) {
            lint dist = i - cur_pos;
            ans += max(0ll, dist - cur_gas) * price;
            cur_gas = max(0ll, cur_gas - dist);
            d.pop_front();
        }
        d.push_back(pll(this_price, i));
    }

    printf("%lld\n", ans);                
    return 0;
}
