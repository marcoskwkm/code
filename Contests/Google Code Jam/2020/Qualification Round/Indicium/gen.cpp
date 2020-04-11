#include <bits/stdc++.h>
using namespace std;

int main() {
    int sum = 0;
    for (int n = 2; n <= 50; n++)
        sum += n * n - n + 1;

    printf("%d\n", sum);

    for (int n = 2; n <= 50; n++) {
        for (int k = n; k <= n * n; k++) {
            printf("%d %d\n", n, k);
        }
    }



    // srand(time(0));
    // for (int t = 0; t < 100; t++) {
    //     int n = rand() % 49 + 2;
    //     int n = 50;
    //     int k = rand() % (n * n - n + 1) + n;
    //     printf("%d %d\n", n, k);
    // }
    return 0;
}
