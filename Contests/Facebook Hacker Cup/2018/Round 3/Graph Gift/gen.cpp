#include <bits/stdc++.h>
using namespace std;

int main() {
    const int T = 40, N = 30000;
    printf("%d\n", T);
    for (int t = 0; t < T; t++) {
        printf("%d\n", N);
        for (int i = 0; i < N; i++) {
            int x = 1 + rand() % 10000000;
            if (rand() % 2) x = -x;
            printf("%d%c", x, i + 1 == N ? '\n' : ' ');
        }
    }
    return 0;
}
