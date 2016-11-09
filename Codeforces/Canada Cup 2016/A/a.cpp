#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

char s[MAXN];
bool done[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '<') done[i] = 1, ans++;
        else break;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '>') {
            if (!done[i]) ans++;
        }
        else break;
    }
    printf("%d\n", ans);            
    return 0;
}
