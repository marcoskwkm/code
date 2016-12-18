#include <bits/stdc++.h>
using namespace std;

string gen_random_str() {
    int len = rand() % 6 + 1;
    string s = "";
    for (int i = 0; i < len; i++)
        s += ('a' + rand() % 26);
    return s;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    int n;
    sscanf(argv[1], "%d", &n);
    printf("%d %d\n", n, n);
    for (int i = 0; i < n; i++)
        printf("%s ", gen_random_str().c_str());
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
