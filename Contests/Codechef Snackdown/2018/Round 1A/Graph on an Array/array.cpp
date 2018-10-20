#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int v[MAXN];
bool seen[MAXN];
int n;

void dfs(int i) {
    seen[i] = 1;
    for (int j = 0; j < n; j++)
        if (!seen[j] && __gcd(v[i], v[j]) == 1)
            dfs(j);
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int p = 43;
        cin >> n;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            if (v[i] == p) p = 47;
        }
        memset(seen, 0, sizeof(seen));

        dfs(0);
        bool ok = 1;
        for (int i = 0; i < n; i++)
            if (!seen[i])
                ok = 0;
        if (!ok) {
            printf("1\n");
            v[0] = p;
        }
        else
            printf("0\n");
        for (int i = 0; i < n; i++)
            printf("%d%c", v[i], i + 1 == n ? '\n' : ' ');
    }        
    return 0;
}
