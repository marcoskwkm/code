#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;

bool is_psq[MAXN];

int main() {
    for (int i = 1; i * i < MAXN; i++)
        is_psq[i * i] = 1;

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;
        bool flag = 0;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            if (!is_psq[x]) {
                flag = 1;
            }
        }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}
