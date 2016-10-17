#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int k, r;
    scanf("%d%d", &k, &r);
    for (int i = 1;; i++) {
        if (k * i % 10 == r || k * i % 10 == 0) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}
