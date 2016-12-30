#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int cur = 1, rem = 4 * 60;
    while (cur <= n && rem - 5*cur - k >= 0) {
        rem -= 5*cur;
        cur++;
    }
    printf("%d\n", cur - 1);
    return 0;
}
