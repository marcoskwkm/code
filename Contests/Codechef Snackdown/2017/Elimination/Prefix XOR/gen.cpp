#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    int n = 100;
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
        printf("%d\n", min(n - 1, i + rand() % (n - i)));
    return 0;
}
