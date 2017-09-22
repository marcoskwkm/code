#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int nxt[2][4][4];
int wins[4];

int main() {
    wins[1] = 3, wins[2] = 1, wins[3] = 2;
    lint k;
    int ap, bp;
    cin >> k >> ap >> bp;
    for (int i = 0; i < 2; i++)
        for (int a = 1; a <= 3; a++)
            for (int b = 1; b <= 3; b++)
                scanf("%d", &nxt[i][a][b]);
    map<pii, int> hist;
    map<pii, pii> points;
    lint cur_a = 0, cur_b = 0;
    if (wins[ap] == bp) cur_a++;
    else if (wins[bp] == ap) cur_b++;
    hist[pii(ap, bp)] = 0;
    points[pii(ap, bp)] = pii(cur_a, cur_b);
    bool check = 1;
    for (lint t = 1; t < k; t++) {
        int na = nxt[0][ap][bp];
        int nb = nxt[1][ap][bp];
        ap = na, bp = nb;
        if (wins[ap] == bp) cur_a++;
        else if (wins[bp] == ap) cur_b++;

        if (check) {
            auto it = hist.find(pii(ap, bp));
            if (it != hist.end()) {
                lint cycle = t - it->second;
                lint cycle_a, cycle_b;
                tie(cycle_a, cycle_b) = points[pii(ap, bp)];
                cycle_a = cur_a - cycle_a;
                cycle_b = cur_b - cycle_b;
                lint q = (k - t - 1) / cycle;
                t += q * cycle;
                cur_a += q * cycle_a;
                cur_b += q * cycle_b;
                check = 0;
            }
            else {
                hist[pii(ap, bp)] = t;
                points[pii(ap, bp)] = pii(cur_a, cur_b);
            }            
        }
    }

    printf("%lld %lld\n", cur_a, cur_b);    
    return 0;
}
