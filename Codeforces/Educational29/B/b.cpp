#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 100;

int v[MAXN];

int go(int i, int j, int n) {
    int ret = 0;
    vector<int> vv;
    for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;
        vv.push_back(v[k]);
    }
    for (int i = 0; i < n - 2; i += 2)
        ret += vv[i + 1] - vv[i];
    return ret;
}

int main() {
    int n;
    cin >> n;
    n <<= 1;
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    sort(v, v + n);
    int ans = INF;    
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            ans = min(ans, go(i, j, n));
    cout << ans << endl;
    return 0;
}
