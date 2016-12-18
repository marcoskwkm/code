#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int l, r;
    scanf("%d%d", &l, &r);
    while (l <= r) {
        int mid = (l + r) / 2;
        printf("%d\n", mid);
        fflush(stdout);
        char resp[10];
        scanf("%s", resp);
        if (resp[0] == 'L') l = mid + 1;
        else if (resp[0] == 'H') r = mid - 1;
        else break;
    }
    return 0;
}
