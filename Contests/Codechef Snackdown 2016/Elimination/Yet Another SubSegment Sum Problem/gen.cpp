#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1000000;

int main() {
    srand(time(0));
    int N = 100000, Q = 10000;
    printf("%d\n", N);
    for (int i = 0; i < N; i++)
        printf("%d ", rand() % (MAXV + 1));
    printf("\n");
    for (int i = 0; i < N; i++)
        printf("%d ", rand() % (MAXV + 1));
    printf("\n");
    printf("%d\n", Q);
    for (int i = 0; i < Q; i++) {
        int l = rand() % N + 1, r = rand() % N + 1;
        int c = rand() % (MAXV + 1);
        int d = rand() % (MAXV + 1);
        if (rand() % 3 == 0) c = 0;
        if (rand() % 3 == 0) d = 0;
        if (l > r) swap(l, r);
        printf("%d %d %d %d\n", l, r, c, d);
    }
    return 0;
}
