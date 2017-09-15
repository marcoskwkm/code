#include <bits/stdc++.h>
using namespace std;

int main () {
    int n = 100000, m = 200000;
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        int u = rand() % n + 1, v = rand() % n + 1;
        if (rand() % 3 == 0) u = 1;
        if (u > v) swap(u, v);
        while (u == v) v = rand() % n + 1;
        printf("%d %d\n", u, v);
    }
    return 0;
}
