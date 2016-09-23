#include <bits/stdc++.h>
using namespace std;

const int MAXV = (int)1e9;

int main() {
    int n = 100000, m = 100000;
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++)
        printf("%d ", 1 + rand() % MAXV);
    printf("\n");
    for (int i = 0; i < m; i++) {
        int op = 1 + rand() % 2;
        int l = 1 + rand() % n, r = 1 + rand() % n;
        if (l > r) swap(l, r);
        if (op == 1) {
            int x = 1 + rand() % MAXV;
            printf("%d %d %d %d\n", op, l, r, x);
        }
        else printf("%d %d %d\n", op, l, r);
    }
    return 0;
}
