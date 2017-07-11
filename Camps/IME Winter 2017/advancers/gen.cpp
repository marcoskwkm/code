#include <bits/stdc++.h>
using namespace std;

int main() {
    int t = 100;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        int t = 60;
        int s = rand() % t + 1;
        if (i == 0) s = 1;
        printf("%d %d\n", t, s);
        for (int j = 0; j < t; j++)
            printf("%lld\n", 5000000000 + rand());
        printf("\n");
    }
    return 0;
}
