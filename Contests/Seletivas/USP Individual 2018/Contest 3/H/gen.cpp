#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 100000;
    printf("%d\n", N);
    srand(time(0));
    for (int i = 1; i < N; i++)
        printf("%d %d %d\n", i, i + 1, rand() % 10001);
    for (int i = 2; i <= N; i++)
        printf("%d %d\n", rand() % 1000000001, rand() % 1000000000 + 1);
    return 0;
}
