#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 510;

int v[MAXN];
vector< pair<int, char> > ans;

bool solve(int l, int r, int k) {
    if (l == r) return 1;
    int hi = 0, at = -1;
    for (int i = l; i <= r; i++)
        hi = max(hi, v[i]);
    for (int i = l; i <= r; i++) {
        if (v[i] != hi) continue;
        if (i - 1 >= l && v[i - 1] < v[i])
            at = i;
        if (i + 1 <= r && v[i + 1] < v[i])
            at = i;
    }
    if (at == -1) return 0;
    int ll = at - 1, rr = at + 1;
    int cur = v[at];
    for (int i = 0; i < r - l; i++) {
        if (ll >= l && v[ll] < cur) {
            ans.push_back(make_pair(at - l + k, 'L'));
            cur += v[ll--];
            k--;
        }
        else {
            ans.push_back(make_pair(at - l + k, 'R'));
            cur += v[rr++];
        }
    }    
    return 1;
}

int main() {
    int n, k;
    scanf("%d", &n); 
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &k);
    bool ok = 1;
    int at = 0;
    for (int i = 0; i < k; i++) {
        int l = at;
        int x;
        scanf("%d", &x);
        int sum = 0;
        while (at < n && sum < x)
            sum += v[at++];
        if (sum != x) ok = 0;
        else if (!solve(l, at - 1, i)) ok = 0;        
    }
    if (ok && at == n) {
        printf("YES\n");
        for (auto p: ans)
            printf("%d %c\n", p.first + 1, p.second);
    }
    else printf("NO\n");        
    return 0;
}
