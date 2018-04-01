#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXN = (int)1e5 + 10;
int v[MAXN], t[MAXN];

int main() {
    int n;
    cin >> n;
    multiset<lint> snow;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]);

    lint off = 0;
    for (int i = 0; i < n; i++) {
        snow.insert(v[i] + off);
        lint ans = 0;
        while (!snow.empty() && *snow.begin() <= off + t[i]) {
            ans += *snow.begin() - off;
            snow.erase(snow.begin());
        }
        ans += (lint)(snow.size()) * t[i];
        off += t[i];
        printf("%lld ", ans);
    }
    
    cout << endl;
    
    return 0;
}
