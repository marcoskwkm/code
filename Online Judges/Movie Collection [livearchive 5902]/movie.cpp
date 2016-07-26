#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int pos[MAXN];
int bit[MAXN];

void update(int i, int val) {
    for (; i < MAXN; i += i & -i)
        bit[i] += val;
}

int query(int i) {
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        memset(bit, 0, sizeof(bit));
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            pos[n - i] = i + 1;
            update(i + 1, 1);
        }
        int nxt = n + 1;
        for (int i = 0; i < m; i++) {
            int box;
            scanf("%d", &box);
            printf("%d%c", n - query(pos[box]), i + 1 == m ? '\n' : ' ');
            update(pos[box], -1);
            update(nxt, 1);
            pos[box] = nxt++;
        }
    }        
    return 0;
}
