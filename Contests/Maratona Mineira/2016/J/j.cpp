#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int nxt[MAXN];
int size[MAXN];
bool done[MAXN];
int ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &nxt[i]);
    for (int v = 1; v <= n; v++) {
        if (size[v]) continue;
        int len = 1;
        int cur = v;
        while (nxt[cur] != v) {
            cur = nxt[cur];
            len++;
        }
        size[v] = len;
        cur = v;
        while (nxt[cur] != v) {
            cur = nxt[cur];
            size[cur] = len;
        }
    }        

    int first = 0;
    bool ok = 1;
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (v == 0) continue;
        else if(ans[i] == v) continue;
        else if (done[v]) {
            ok = 0;
            break;
        }
        else if (i < first) {
            ok = 0;
            break;
        }
        else {
            int len = size[v];
            int last = first + len - 1;
            int cur = v, curp = i;
            for (int j = 0; j < len; j++) {
                ans[curp] = cur;
                done[cur] = 1;
                curp++;
                cur = nxt[cur];
                if (curp > last) curp = first;
            }
            first = last + 1;
        }
    }
    if (first != n) ok = 0;
    if (!ok) printf("-1\n");
    else {
        for (int i = 0; i < n; i++) printf("%d%c", ans[i], " \n"[i + 1 == n]);
        printf("\n");
    }    
    return 0;
}
