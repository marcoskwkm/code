#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    int n = 1000000;
    for (int i = 0; i < n; i++) {
        printf("%c", rand()%10 + '0');
    }
    printf("%d\n", n);
    printf("010234\n");
    return 0;
}
