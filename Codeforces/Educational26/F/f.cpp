#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

lint v[MAXN];

int main() {
    int n;
    lint k;
    cin >> n >> k;
    bool done = 0;
    for (int i = n - 1; i >= 0; i--) {
        scanf("%lld", &v[i]);
        if (v[i] >= k) done = 1;
    }
    if (done) {
        printf("0\n");
        return 0;
    }
    while (v[n - 1] == 0) n--;
    reverse(v, v + n);

    for (int i = 1;; i++) {
        // debug("i = %d...\n", i);
        lint sum = 0;
        bool done = 0;
        for (int j = 0; j < n; j++) {
            sum += v[j];
            if (sum >= k) done = 1;
        }
        if (done) {
            printf("%d\n", i);
            break;
        }
        for (int j = 1; j < n; j++) {
            v[j] += v[j - 1];
            // debug("%lld ", v[j]);
        }
        // debug("\n");        
    }        
    return 0;
}
