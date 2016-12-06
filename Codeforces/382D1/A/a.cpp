#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXK = (int)2e6 + 10;

lint f[MAXK];

int main() {
    lint n;
    cin >> n; 
    f[0] = 1;
    int ans = 0;
    for (int i = 1; i < MAXK; i++) {
        f[i] = 1;
        for (int j = 0; j < i; j++) {
            int needs = max(0, j - 1);
            f[i] += f[needs];
        }
        if (f[i] > n) break;
        ans = i;
    }

    printf("%d\n", ans);        
    return 0;
}
