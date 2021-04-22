#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

bool taken[100];
int perm[100];

int go(int i, int n, int last) {
    if (i == n) {
        for (int j = 0; j < n; j++) {
            printf("%d ", perm[j]);
        }
        printf("\n");
        return 1;
    }

    int ret = 0;
    for (int take = 1; take <= n; take++) {
        if (!taken[take] && (i == 0 || take >= last - 1)) {
            perm[i] = take;
            taken[take] = 1;
            ret += go(i + 1, n, take);
            taken[take] = 0;
        }
    }

    return ret;
}

int main() {
    for (int n = 1; n <= 6; n++) {
        printf("### n = %d ###\n", n);
        int cnt = go(0, n, 0);
        printf("Total: %d\n\n", cnt);
    }
    return 0;
}
