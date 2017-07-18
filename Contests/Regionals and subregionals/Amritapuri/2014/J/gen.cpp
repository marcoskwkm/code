#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    int n;
    sscanf(argv[1], "%d", &n);
    printf("1\n");
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
        printf("%d %d %d\n", rand() % 50, rand() % 50, rand() % 100);
    return 0;
}
