#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int main() {
    int t;
    for (cin >> t; t--;) {
        lint n, k;
        cin >> n >> k;
        if (n - 1 <= 62 && (1LL << (n - 1)) < k) {
            printf("-1\n");
            continue;
        }

        int cur_min = 1;
        k--;
        for (int i = 0; i < n;) {
            int take = 1;
            if (n - 2 - i <= 62) {
                for (int j = n - 2 - i; j >= -1; j--) {
                    if (k >= (1LL << max(0, j))) {
                        k -= (1LL << max(0, j));
                        take++;
                    } else {
                        break;
                    }
                }
            }

            for (int x = take; x > 0; x--) {
                printf("%d ", cur_min + x - 1);
            }
            cur_min += take;
            i += take;
        }
        while (cur_min <= n) {
            printf("%d ", cur_min++);
        }
        printf("\n");
    }
    return 0;
}
