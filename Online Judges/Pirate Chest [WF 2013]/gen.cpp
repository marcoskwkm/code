#include <bits/stdc++.h>
using namespace std;

int main() {
    int N = 500;
    printf("%d %d %d %d\n", N - 1, N, N, N);
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            printf("%d%c", rand() % (int)(1e9 + 1), " \n"[c + 1 == N]);
    return 0;
}
