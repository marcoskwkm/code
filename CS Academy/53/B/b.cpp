#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int solve(vector<int> &v) {
    int ans = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        int j = i;
        while (j + 1 < (int)v.size() && v[j + 1] >= v[j]) j++;
        ans = max(ans, j - i + 1);
        i = j;
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> v(n);
    for (int i = 0; i < n; i++) scanf("%d", &v[i]);
    int ans = solve(v);
    reverse(v.begin(), v.end());
    ans = max(ans, solve(v));
    cout << ans << endl;
    return 0;
}
