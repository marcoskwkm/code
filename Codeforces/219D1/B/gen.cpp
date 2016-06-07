#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 40, m = 40, q = (int)3e5;
    printf("%d %d %d\n", n, m, q);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++)
            printf("0");
        printf("\n");
    }
    for (int i = 0; i < q; i++) {
        printf("1 1 %d %d\n", n, m);
    }
    return 0;
}
