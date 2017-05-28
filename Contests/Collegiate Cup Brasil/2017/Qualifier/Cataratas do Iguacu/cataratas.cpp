#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int v[MAXN];

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    multiset<int> upper;
    multiset<int, greater<int> > lower;
    int ans = 0;
    for (int i = 0; i < k; i++) {        
        scanf("%d", &v[i]);
        upper.insert(v[i]);
    }
    while (lower.size() < k / 2) {
        lower.insert(*upper.begin());
        upper.erase(upper.begin());
    }
    ans = *upper.begin();
    for (int i = k; i < n; i++) {
        if (*upper.begin() <= v[i - k]) {
            upper.erase(upper.find(v[i - k]));
        }
        else {
            lower.erase(lower.find(v[i - k]));
        }
        scanf("%d", &v[i]);
        if (v[i] >= *upper.begin()) upper.insert(v[i]);
        else lower.insert(v[i]);
        while (lower.size() < k / 2) {
            lower.insert(*upper.begin());
            upper.erase(upper.begin());
        }
        while (lower.size() > k / 2) {
            upper.insert(*lower.begin());
            lower.erase(lower.begin());
        }
        ans = max(ans, *upper.begin());
    }
    printf("%d\n", ans);        
    return 0;
}
