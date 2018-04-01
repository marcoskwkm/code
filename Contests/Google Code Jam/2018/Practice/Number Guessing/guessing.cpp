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
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        int l, r;
        scanf("%d%d%*d", &l, &r);
        while (l < r) {
            int m = (l + r + 1) / 2;
            printf("%d\n", m);
            fflush(stdout);
            string verdict;
            cin >> verdict;
            if (verdict == "TOO_SMALL")
                l = m;
            else if (verdict == "TOO_BIG")
                r = m - 1;
            else if (verdict == "CORRECT")
                break;
            else return 0;
        }
    }        
    return 0;
}
