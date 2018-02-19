#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXV = 40;

int drew[MAXV];

int main() {
    for (int i = 0; i < 10; i++) {
        int x;
        scanf("%d", &x);
        drew[x] = 1;
    }
    int n;
    for (scanf("%d", &n); n--;) {
        int cnt = 0;
        for (int i = 0; i < 6; i++) {
            int x;
            scanf("%d", &x);
            cnt += drew[x];
        }
        printf("%s\n", cnt >= 3 ? "Lucky" : "Unlucky");
    }       
    return 0;
}
