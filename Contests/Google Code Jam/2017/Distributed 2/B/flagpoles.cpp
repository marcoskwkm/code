#include "flagpoles.h"
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
    int s = max((q + n - 1) / n, 2);
    vector<pii> ret;
    int cur_l = l;
    for (int i = 0; i < n; i++) {
        int cur_r = min(cur_l + s - 1, r);
        if (cur_r == cur_l) {
            ret.back().second = r;
            cur_l = r + 1;
        }
        ret.push_back(pii(cur_l, cur_r));
        cur_l = cur_r + 1;
    }
    return ret;
}

int main() {
    int qn = NumberOfNodes(), thisId = MyNodeId();
    int N = GetNumFlagpoles();
    if (N == 1) {
        if (thisId > 0) return 0;
        printf("1\n");
        return 0;
    }
    vector<pii> intervals = split(0, N - 1, qn);
    if (intervals[thisId].first == N) return 0;
    // debug("Id %d: [%d, %d]\n", thisId, intervals[thisId].first, intervals[thisId].second);

    vector<lint> h;
    for (int i = intervals[thisId].first; i <= intervals[thisId].second; i++)
        h.push_back(GetHeight(i));
    int len = (int)h.size();
    int best = 0, best_l = 0, best_r = 0;
    for (int i = 0; i < len - 1;) {
        int j = i;
        while (j + 1 < len && h[j + 1] - h[j] == h[i + 1] - h[i])
            j++;
        best = max(best, j - i + 1);
        if (i == 0) best_l = max(best_l, j - i + 1);
        if (j == len - 1) best_r = max(best_r, j - i + 1);
        i = j;
    }
    PutInt(0, best);
    PutInt(0, best_l);
    PutLL(0, h[0]);
    PutLL(0, h[1] - h[0]);
    PutInt(0, best_r);
    PutLL(0, h[len - 1]);
    PutLL(0, h[len - 1] - h[len - 2]);
    Send(0);

    if (thisId > 0) return 0;

    int ans = 0, acc = 0;
    lint last_h, last_d;
    for (int i = 0; i < qn && intervals[i].first < N; i++) {
        // debug("processing %d\n", i);
        int node_len = intervals[i].second - intervals[i].first + 1;
        Receive(i);
        ans = max(ans, GetInt(i));
        int node_best_l = GetInt(i);
        lint node_h = GetLL(i);
        lint node_d = GetLL(i);
        if (i > 0) {
            if (last_d == node_d) {
                if (node_h - last_h == node_d) {
                    acc += node_best_l;
                    ans = max(ans, acc);
                }
            }
            else {
                if (node_h - last_h == last_d)
                    ans = max(ans, acc + 1);
                acc = node_best_l;
                if (node_h - last_h == node_d) {
                    acc++;
                    ans = max(ans, acc);
                }
            }
        }
        else acc = node_best_l;
        int node_best_r = GetInt(i);
        node_h = GetLL(i);
        node_d = GetLL(i);
        if (node_best_r < node_len) acc = node_best_r;
        last_h = node_h;
        last_d = node_d;
    }

    cout << ans << endl;    
    return 0;
}
