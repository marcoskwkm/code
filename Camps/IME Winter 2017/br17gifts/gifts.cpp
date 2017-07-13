#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = (int)1e9 + 7;

int main() {
    int n;
    cin >> n;
    lint ans = 1;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    sort(v.begin(), v.end(), greater<int>());
    int at = 0;
    for (int i = 0; i < n; i++) {
        while (at < n && v[at] >= (n - i)) at++;
        ans = (ans * (at - i)) % MOD;
    }
    cout << ans << endl;
    
    return 0;
}
