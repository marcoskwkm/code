#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int needs[MAXN], has[MAXN];
int n, k;

bool check(lint q) {
    lint rem = 0;
    for (int i = 0; i < n; i++) {
        rem += max<lint>(0, lint(needs[i])*q - has[i]);
        if (rem > k) return 0;
    }
    return rem <= k;
}        

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &needs[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &has[i]);
    lint l = 0, r = (lint)3e9 + 10;
    while (l < r) {
        lint mid = (l + r + 1)/2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    cout << l << endl;
    return 0;
}
