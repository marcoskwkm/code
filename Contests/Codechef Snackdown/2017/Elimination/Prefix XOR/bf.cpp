#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;

int v[MAXN];
int vv[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            int s = 0;
            for (int i = l; i <= r; i++)
                s += min(r, v[i]) - i + 1;
            printf("%d\n", s);
        }
    }
    return 0;
}
