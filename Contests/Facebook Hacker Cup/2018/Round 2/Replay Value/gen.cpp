#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000000;

set<int> xs, ys;
int get_x() {
    while (1) {
        int x = rand() % MOD;
        if (xs.find(x) != xs.end()) continue;
        xs.insert(x);
        return x;
    }
}
int get_y() {
    while (1) {
        int y = rand() % MOD;
        if (ys.find(y) != ys.end()) continue;
        ys.insert(y);
        return y;
    }
}
        
int main () {
    srand(time(0));
    int T = 30, N = 50;
    printf("%d\n", T);
    for (int t = 0; t < T; t++) {
        xs.clear(), ys.clear();
        xs.insert(0), xs.insert(1000000000);
        printf("%d %d %d\n", N, get_y(), get_y());
        for (int i = 0; i < N; i++)
            printf("%d %d\n", get_x(), get_y());
    }
    return 0;
}
        
