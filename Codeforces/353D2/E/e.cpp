#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;
const int LOG = 20;

int r[MAXN];
pii vp[MAXN];

pii rmq[LOG][MAXN];
int v[MAXN];
int n;

void build_rmq() {
    for(int i = 0; i < n; i++)
        rmq[0][i] = vp[i];
    for(int log = 1; log < LOG; ++log) {
        for(int i = 0; i < n; i++) {
            rmq[log][i] = max(rmq[log-1][i], rmq[log-1][min(n-1, i + (1<<(log-1)))]);
        }
    }
}

pii get_rmq(int l, int r) {
    int len = r - l + 1;
    int bit = 31 - __builtin_clz(len);
    return max(rmq[bit][l], rmq[bit][r - (1<<bit) + 1]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &r[i]);
        vp[i] = pii(r[i], -i);
    }
    build_rmq();

    
    set<pii> intervals;
    intervals.insert(pii(n, n + 1));
    lint ans = 0, cur = n; 
    for (int i = 1; i < n; i++) {
        cur--;
        if (intervals.begin()->first > i) {
            stack<pii> st;
            st.push(pii(i, r[i]));
            cur += n - r[i];
            while (st.top().second < intervals.begin()->first) {
                pii p = get_rmq(st.top().first, st.top().second);
                st.push(pii(-p.second, p.first));
                cur += n - p.first;
            }
            while (!st.empty()) {
                pii p = st.top();
                st.pop();
                while (intervals.begin()->second <= p.second) {
                    cur -= n - intervals.begin()->second;
                    intervals.erase(intervals.begin());
                }
                intervals.insert(p);
            }
        }
        ans += cur;
        // debug("i = %d (add %lld):\n", i, cur);
        // for (pii p: intervals) {
        //     debug("(%d, %d)\n", p.first, p.second);
        // }
        intervals.erase(intervals.begin());
        cur -= n - r[i];
    }
    cout << ans << endl;    
    return 0;
}
