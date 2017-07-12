#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e6 + 10;

lint v[MAXN];

int main() {
    int n;
    cin >> n;
    multiset<lint> avail;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        avail.insert(v[i]);
    }
    lint ans = 0;
    lint pos = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] == *avail.begin()) {
            ans += (i - pos) * v[i];
            pos = i;
        }
        avail.erase(avail.find(v[i]));
    }
    cout << ans << endl;    
    return 0;
}
