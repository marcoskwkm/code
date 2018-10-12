#include <bits/stdc++.h>
using namespace std;

#define debug(x...) fprintf(stderr, x)

typedef long long lint;

const int MAXN = (int)1e5 + 10;

int n;
int s[MAXN];
int paired[MAXN];

bool check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (paired[i] == j) continue;
            if (s[paired[j]] > s[paired[i]] && s[i] > s[j]) return 0;
        }
    }
    return 1;
}

lint go(int i) {
    if (i == n) return check();
    if (paired[i] != -1) return go(i + 1);
    lint ret = 0;
    for (int j = i + 1; j < n; j++) {
        if (paired[j] != -1) continue;
        paired[i] = j;
        paired[j] = i;
        ret += go(i + 1);
        paired[i] = paired[j] = -1;
    }
    return ret;
}    

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        debug("%d cases left...\n", t);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &s[i]);
        memset(paired, -1, sizeof(paired));
        printf("%lld\n", go(0));
    }
}
