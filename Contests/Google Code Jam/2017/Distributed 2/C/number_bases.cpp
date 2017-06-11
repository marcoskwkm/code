#include "number_bases.h"
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

vector<pii> split(int l, int r, int n) {
    int q = (r - l + 1);
    int s = q / n, rem = q % n;
    vector<pii> ret;
    int cur_l = l;
    for (int i = 0; i < n; i++) {
        int cur_r = cur_l + s - 1 + (i < rem);
        ret.push_back(pii(cur_l, cur_r));
        cur_l = cur_r + 1;
    }
    return ret;
}

int main() {
    int qn = NumberOfNodes(), thisId = MyNodeId();
    int N = GetLength();    
    vector<pii> interv = split(0, N - 1, qn);
    if (interv[thisId].first == N) return 0;
    // debug("%d: [%d, %d]\n", thisId, interv[thisId].first, interv[thisId].second);

    int bound = 0;
    vector<int> x, y, z;
    for (int i = interv[thisId].first; i <= interv[thisId].second; i++) {
        x.push_back(GetDigitX(i));
        y.push_back(GetDigitY(i));
        z.push_back(GetDigitZ(i));
        bound = max(bound, x.back() + 1);
        bound = max(bound, y.back() + 1);
        bound = max(bound, z.back() + 1);
    }

    PutInt(0, bound);
    int len = interv[thisId].second - interv[thisId].first + 1;
    for (int add = 0; add < 2; add++) {
        int cur = add;
        int base = 0;
        for (int i = 0; i < len; i++) {
            int l = x[i] + y[i] + cur, r = z[i];
            if (l < r) {
                base = -1;
                break;
            }
            else if (l == r) {
                cur = 0;
                continue;
            }
            else {
                if (base != 0) {
                    if (l % base == r) {
                        cur = 1;
                    }
                    else {
                        base = -1;
                        break;
                    }
                }
                else if (l - r >= bound) {
                    base = l - r;
                    cur = 1;
                }
                else {
                    base = -1;
                    break;
                }
            }
        }
        PutInt(0, base);
        PutInt(0, cur);
        // debug("%d: (%d) base = %d,  cur = %d\n", thisId, add, base, cur);
    }
    Send(0);
    // debug("done %d\n", thisId);
    if (thisId > 0) return 0;

    int total_bound = 0;
    int cur = 0;
    int ans = 0;
    for (int i = 0; i < qn && interv[i].first < N; i++) {
        // debug("proc %d (cur = %d, ans = %d)\n", i, cur, ans);
        Receive(i);
        total_bound = max(total_bound, GetInt(i));
        int node_base[2], node_cur[2];
        for (int j = 0; j < 2; j++) {
            node_base[j] = GetInt(i);
            node_cur[j] = GetInt(i);
        }
        if (node_base[cur] != 0) {
            if (node_base[cur] == -1) {
                ans = -1;
            }
            else if (ans == 0) {
                ans = node_base[cur];
            }
            else if (ans != node_base[cur]) {
                ans = -1;
            }
        }
        cur = node_cur[cur];
    }
    // debug("ans = %d, bound = %d\n", ans, total_bound);
    if (cur) printf("IMPOSSIBLE\n");
    else if (ans == 0) printf("NON-UNIQUE\n");
    else if (ans < total_bound) printf("IMPOSSIBLE\n");
    else printf("%d\n", ans);        
    return 0;
}
