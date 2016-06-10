#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

int main() {
    int n = 100, m = 99;
    srand(time(0));
    set<pii> foi;
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        if (i < n) {
            int u = rand() % (i + 1) + 1, v = i + 2;
            foi.insert(pii(u, v));
            printf("%d %d\n", u, v);
        }
        else {
            int u = rand() % n + 1, v = rand() % n + 1;
            if (u == v) continue;
            if (u > v) swap(u, v);
            pii p(u, v);
            if (foi.find(p) != foi.end()) continue;
            foi.insert(p);
            printf("%d %d\n", u, v);
        }
    }
    return 0;
}
