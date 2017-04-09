#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct FreeSegment {
    lint l, r, m, size;
    lint lo, hi;
    FreeSegment(lint _l, lint _r) {
        l = _l;
        r = _r;
        m = (l + r) / 2;
        size = r - l - 1;
        lint ls = m - l - 1;
        lint rs = r - m - 1;
        lo = min(ls, rs);
        hi = max(ls, rs);
    }
    bool operator< (const FreeSegment& that) const {
        if (size != that.size) return size > that.size;
        return l < that.l;
    }
};

int main() {
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        lint n, k;
        cin >> n >> k;
        set<FreeSegment> pq;
        pq.insert(FreeSegment(0, n + 1));
        while (k--) {
            FreeSegment cur_segment = *pq.begin();
            pq.erase(pq.begin());
            if (k == 0) {
                printf("Case #%d: %lld %lld\n", t, cur_segment.hi, cur_segment.lo);
            }
            if (cur_segment.l + 1 < cur_segment.m)
                pq.insert(FreeSegment(cur_segment.l, cur_segment.m));
            if (cur_segment.m + 1 < cur_segment.r)
                pq.insert(FreeSegment(cur_segment.m, cur_segment.r));
        }
    }
    return 0;
}
