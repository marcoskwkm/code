#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e7 + 10;

int q[MAXN], nxt[MAXN][2];
int cur = 1;

void update(int node, int i, int x, int val) {
    q[node] += val;
    if (i == -1) return;
    int bit = ((1 << i) & x) ? 1 : 0;
    if (nxt[node][bit] == -1) nxt[node][bit] = cur++;
    update(nxt[node][bit], i - 1, x, val);    
}

int query(int node, int i, int x) {
    if (i == -1) return 0;
    int bit = ((1 << i) & x) ? 1 : 0;
    if (q[nxt[node][!bit]] > 0)
        return (1 << i) | query(nxt[node][!bit], i - 1, x);
    else
        return query(nxt[node][bit], i - 1, x);
}

int main() {
    int q;
    memset(nxt, -1, sizeof(nxt));
    update(0, 30, 0, 1);
    for (scanf("%d", &q); q--;) {
        char op;
        int x;
        scanf (" %c%d", &op, &x);
        if (op == '+') update(0, 30, x, 1);
        else if (op == '-') update(0, 30, x, -1);
        else printf("%d\n", query(0, 30, x));
    }        
    return 0;
}
