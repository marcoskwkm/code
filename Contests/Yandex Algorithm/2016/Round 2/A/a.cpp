#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int price[300];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    string s;
    cin >> s;
    memset(price, INF, sizeof(price));
    for (int i = 0; i < m; i++) {
        int len, cst;
        scanf("%d%d", &len, &cst);
        string p;
        cin >> p;
        for (char c: p)
            price[c] = min(price[c], cst);
    }
    int ans = 0;
    bool ok = 1;
    for (char c: s) {
        if (price[c] == INF) {
            ok = 0;
            break;
        }
        else ans += price[c];
    }
    printf("%d\n", ok ? ans : -1);    
    return 0;
}
