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
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        lint n, k;
        cin >> n >> k;
        map<lint, lint> q;
        set<lint, greater<lint>> pq;
        q[n] = 1;
        pq.insert(n);
        while (1) {
            lint cur = *pq.begin();
            lint lo = (cur - 1) / 2, hi = cur / 2;
            pq.erase(pq.begin());
            lint got = q[cur];
            k -= got;
            if (k <= 0) {
                printf("Case #%d: %lld %lld\n", t, hi, lo);
                break;
            }
            q[lo] += got;
            pq.insert(lo);
            q[hi] += got;
            pq.insert(hi);
        }
    }        
    return 0;
}
