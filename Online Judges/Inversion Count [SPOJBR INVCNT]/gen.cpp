#include <bits/stdc++.h>
using namespace std;

int main() {
    int t = 10;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        int n = (int)2e5;
        printf("%d\n", n);
        set<int> cj;
        for (int i = 0; i < n; i++)
            printf("%d ", rand() % 10000000);
        printf("\n");
    }
    return 0;
}
