#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0));
    printf("100\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 2000; j++)
            printf("%c", 'A' + rand() % 26);
        printf("\n");
    }
    return 0;
}
