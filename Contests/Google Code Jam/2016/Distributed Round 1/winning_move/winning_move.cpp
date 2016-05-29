#include "winning_move.h"
#include <message.h>
#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef pair<lint, int> pli;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXM = 110;

int l[MAXM], r[MAXM];

int main() {
    int m = NumberOfNodes(), thisId = MyNodeId();
    int master = m - 1;
    m--;
    int n = GetNumPlayers();
    vector<lint> v;
    if (thisId != master) {
        map<lint, int> freq;
        for (int i = thisId; i < n; i += m) {
            v.push_back(GetSubmission(i));
            freq[v.back()]++;
        }
        sort(v.begin(), v.end());
        lint cand = LINF;
        for (auto p: freq)
            if (p.second == 1)
                cand = min(cand, p.first);
        if (cand == LINF) PutLL(master, -1);
        else PutLL(master, cand);
        Send(master);
    }

    vector<pli> cands;
    if (thisId == master) {
        for (int i = 0; i < m; i++) {
            Receive(i);
            lint x = GetLL(i);
            if (x != -1) cands.push_back(pli(x, i));
        }
        sort(cands.begin(), cands.end());
        for (int i = 0; i < m; i++) {
            for (pli p: cands)
                PutLL(i, p.first);
            PutLL(i, -1);
            Send(i);
        }
    }

    else {
        Receive(master);
        while (1) {
            lint cand = GetLL(master);
            if (cand == -1) break;
            if (binary_search(v.begin(), v.end(), cand)) PutChar(master, 1);
            else PutChar(master, 0);
        }
        Send(master);
    }

    if (thisId == master) {
        vector<int> responses[m];
        for (int i = 0; i < m; i++) {
            Receive(i);
            for (int j = 0; j < (int)cands.size(); j++) {
                responses[i].push_back(GetChar(i));
            }
        }
        for (int i = 0; i < (int)cands.size(); i++) {
            bool ok = 1;
            for (int j = 0; j < m; j++) {
                if (responses[j][i] && j != cands[i].second) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                printf("%lld\n", cands[i].first);
                return 0;
            }
        }
        printf("0\n");
    }        
    
    return 0;
}
