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
    int T = 100;
    printf("%d\n", T);
    for (int i = 0; i < 10; i++) {
        printf("100 1000\n");
        for (int r = 0; r < 100; r++) {
            for (int c = 0; c < 1000; c++)
                printf("%d ", rand() % 1000000 + 1);
            printf("\n");
        }
    }

    for (int i = 10; i < T; i++) {
        printf("10 100\n");
        for (int r = 0; r < 10; r++) {
            for (int c = 0; c < 100; c++)
                printf("%d ", rand() % 1000000 + 1);
            printf("\n");
        }
    }
    return 0;
}
