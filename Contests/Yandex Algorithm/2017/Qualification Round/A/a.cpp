#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int pos[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        pos[x] = i;
    }
    int ans = 1;
    for (int i = 2; i <= n; i++)
        if (pos[i] < pos[i - 1])
            ans++;
    
    printf("%d\n", ans);        
    return 0;
}
