#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    printf("1\n");
    int n = 200000, m = 1000000;
    printf("%d %d %d %d\n", n, m, rand() % n, rand() % n);
    for (int i = 1; i < n; i++)
        printf("%d\n", rand() % i);
    return 0;
}
