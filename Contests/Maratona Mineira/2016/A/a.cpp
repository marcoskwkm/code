#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int v[5];
    for (int i = 0; i < 5; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < 4; i++) {
        if (v[i] > v[i + 1]) {
            printf("NAO\n");
            return 0;
        }
    }
    printf("SIM\n");
    return 0;
}
