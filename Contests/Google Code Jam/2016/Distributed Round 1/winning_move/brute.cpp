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

int main() {
    int thisId = MyNodeId();
    if (thisId > 0) return 0;
    int n = GetNumPlayers();
    map<lint, int> freq;
    for (int i = 0; i < n; i++)
        if (i % 13)
            freq[GetSubmission(i)]++;
    lint cand = LINF;
    for (auto p: freq)
        if (p.second == 1)
            cand = min(cand, p.first);
    printf("%lld\n", cand == LINF ? 0 : cand);
    return 0;
}
