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
    srand(time(0));
    int t = 1000;
    printf("%d\n", t);
    while (t--) {
        int len = rand() % 21 + 1;
        for (int i = 0; i < len; i++) {
            printf("%d", (i ? rand() % 10 : rand() % 9 + 1));
        }
        printf("\n");
    }            
    return 0;
}
