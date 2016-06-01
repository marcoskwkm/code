#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 300, m = 300, p = 1000;
    printf("%d %d %d\n", n, m, p);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++)
            printf("%d ", rand() % (p + 1));
        printf("\n");
    }
    return 0;
}

