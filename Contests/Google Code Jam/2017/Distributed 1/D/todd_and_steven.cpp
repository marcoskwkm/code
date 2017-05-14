#include "todd_and_steven.h"
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
    int T = GetToddLength(), S = GetStevenLength();
    int size = max(1, (T + S + qn - 1) / qn);
    int last_node = 0;
    
    if (thisId == 0) {
        int lt = 0, ls = 0;
        int rt = -1, rs = -1;
        int l, r;

        int cur_node = 0;
        while (lt < T || ls < S) {
            int rt1, rs1;
            rt1 = min(lt + size - 1, T - 1);
            int xt = GetToddValue(rt1);
            l = ls - 1, r = S - 1;
            while (l < r) {
                int m = (l + r + 1) / 2;
                if (GetStevenValue(m) < xt) l = m;
                else r = m - 1;
            }
            rs1 = l;

            int rt2, rs2;
            rs2 = min(ls + size - 1, S - 1);
            int xs = GetStevenValue(rs2);
            l = lt - 1, r = T - 1;
            while (l < r) {
                int m = (l + r + 1) / 2;
                if (GetToddValue(m) < xs) l = m;
                else r = m - 1;
            }
            rt2 = l;

            if (rs1 - ls + 1 >= size) {
                rt = rt2;
                rs = rs2;
            }
            else if (rt2 - lt + 1 >= size) {
                rt = rt1;
                rs = rs1;
            }
            else if (rs1 - ls + 1 + rt1 - lt + 1 > rs2 - ls + 1 + rt2 - lt + 1) {
                rt = rt1;
                rs = rs1;
            }
            else {
                rt = rt2;
                rs = rs2;
            }
            
            // debug("%d: (%d, %d), (%d, %d)\n", cur_node, lt, rt, ls, rs);
            PutInt(cur_node, lt);
            PutInt(cur_node, rt);
            PutInt(cur_node, ls);
            PutInt(cur_node, rs);
            Send(cur_node++);
            lt = rt + 1;
            ls = rs + 1;
        }
        last_node = cur_node - 1;
        while (cur_node < qn) {
            PutInt(cur_node, -1);
            Send(cur_node++);
        }
    }

    Receive(0);
    int lt = GetInt(0);
    if (lt == -1) return 0;
    int rt = GetInt(0);
    int ls = GetInt(0);
    int rs = GetInt(0);
    lint ret = 0;

    lint cur_pos = lt + ls;
    lint cur_t = -1, cur_s = -1;
    while (lt <= rt && ls <= rs) {
        if (cur_t == -1) cur_t = GetToddValue(lt);
        if (cur_s == -1) cur_s = GetStevenValue(ls);
        if (cur_t < cur_s) {
            ret += (cur_t ^ cur_pos++);
            lt++;
            cur_t = -1;
        }
        else {
            ret += (cur_s ^ cur_pos++);
            ls++;
            cur_s = -1;
        }
    }
    while (lt <= rt) {
        if (cur_t == -1) cur_t = GetToddValue(lt);
        ret += (cur_t ^ cur_pos++);
        lt++; cur_t = -1;
    }
    while (ls <= rs) {
        if (cur_s == -1) cur_s = GetStevenValue(ls);
        ret += (cur_s ^ cur_pos++);
        ls++; cur_s = -1;
    }

    PutLL(0, ret % MOD);
    Send(0);

    if (thisId == 0) {
        lint ans = 0;
        for (int node = 0; node <= last_node; node++) {
            Receive(node);
            ans += GetLL(node);
        }
        cout << ans % MOD << endl;
    }    
    return 0;
}
