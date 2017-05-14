#include "query_of_death.h"
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
const int N_ITER = (int)1e4 + 10;
const int MAXS = (int)2e6 + 10;

int v[MAXS];

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
    vector<int> rem_nodes;
    for (int i = 1; i < qn; i++)
        rem_nodes.push_back(i);

    if (thisId == 0) {
        int l = 0, r = N - 1;
        while (l < r) {
            vector<pii> parts = split(l, r, rem_nodes.size());
            // for (pii p: parts)
            //     debug("(%d, %d)\n", p.first, p.second);
            for (int i = 0; i < (int)rem_nodes.size(); i++) {
                PutInt(rem_nodes[i], 0);
                PutInt(rem_nodes[i], parts[i].first);
                PutInt(rem_nodes[i], parts[i].second);
                Send(rem_nodes[i]);
            }
            int id = -1;
            for (int i = 0; i < (int)rem_nodes.size(); i++) {
                Receive(rem_nodes[i]);
                int changed = GetInt(rem_nodes[i]);
                if (changed) id = i;
            }
            assert(id != -1);
            l = parts[id].first;
            r = parts[id].second;
            rem_nodes[id] = rem_nodes.back();
            rem_nodes.pop_back();
        }
        // debug("l = %d\n", l);
        vector<pii> parts = split(0, N - 1, rem_nodes.size());
        for (int i = 0; i < (int)rem_nodes.size(); i++) {
            PutInt(rem_nodes[i], 1);
            PutInt(rem_nodes[i], parts[i].first);
            PutInt(rem_nodes[i], parts[i].second);
            PutInt(rem_nodes[i], l);
            Send(rem_nodes[i]);
        }

        int ans = 0;
        for (int node: rem_nodes) {
            Receive(node);
            ans += GetInt(node);
        }
        ans += GetValue(l);
        cout << ans << endl;
        return 0;        
    }
    else {
        while (1) {
            Receive(0);
            int op = GetInt(0);
            if (op == -1) return 0;
            if (op == 0) {
                int l = GetInt(0);
                int r = GetInt(0);
                for (int i = l; i <= r; i++)
                    v[i - l] = GetValue(i);
                bool changed = 0;
                if (l <= r) {
                    int cur = 0;
                    for (int i = 0; i < N_ITER; i++) {
                        if (v[cur] != GetValue(cur + l)) {
                            changed = 1;
                            break;
                        }
                        cur++;
                        if (cur == r - l + 1) cur = 0;                        
                    }
                }
                PutInt(0, changed);
                Send(0);
                if (changed) return 0;
            }
            else if (op == 1) {
                int l = GetInt(0);
                int r = GetInt(0);
                int id = GetInt(0);
                int sum = 0;
                for (int i = l; i <= r; i++) {
                    if (i == id) continue;
                    sum += GetValue(i);
                }
                PutInt(0, sum);
                Send(0);
                return 0;
            }
        }
    }
    return 0;
}
