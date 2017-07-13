#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, d;
    cin >> n >> d;
    vector<pii> wall;
    lint total = 0;
    for (int i = 0; i < n; i++) {
        int a, k;
        scanf("%d%d", &a, &k);
        int rem = a % k;
        wall.push_back(pii(k, a - rem));
        if (rem) wall.push_back(pii(rem, rem));
        total += a;
    }
    sort(wall.begin(), wall.end(), greater<pii>());
    for (pii p: wall) {
        int take = min(d, p.second/ p.first);
        d -= take;
        total -= take * p.first;
    }
    cout << total << endl;    
    return 0;
}
