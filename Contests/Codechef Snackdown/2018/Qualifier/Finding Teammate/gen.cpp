#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    int k;
    sscanf(argv[1], "%d", &k);
    
    const int t = 100;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        int n = rand() % k + 1;
        n *= 2;
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
            printf("%d ", rand() % 5 + 1);
        printf("\n");
    }
    return 0;
}
