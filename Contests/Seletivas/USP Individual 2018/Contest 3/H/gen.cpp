#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 50000;
    printf("%d\n", 2*N);
    srand(time(0));
    for (int i = 1; i < N; i++)
        printf("%d %d %d\n", i, i + 1, 1);
    for (int i = 1; i <= N; i++)
        printf("%d %d %d\n", N, N + i, 10000);
    for (int i = 2; i <= N; i++)
        printf("%d %d\n", 0, 1000000000);
    for (int i = N + 1; i <= 2*N; i++)
        printf("%d %d\n", 0, 0);
    return 0;
}
