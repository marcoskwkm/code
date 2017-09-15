#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

int freq[MAXN];

int main() {
    int n, c, s;
    scanf("%d%d%d", &n, &c, &s);
    int at = 1;
    freq[1] = 1;
    for (int i = 0; i < c; i++) {
        int x;
        scanf("%d", &x);
        at += x;
        if (at == 0) at = n;
        if (at == n + 1) at = 1;
        freq[at]++;
    }
    printf("%d\n", freq[s]);
    return 0;
}
