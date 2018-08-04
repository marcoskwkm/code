#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 53;
const int OFF = MAXN - 1;
const int MOD = (int)1e9 + 7;

int dp[MAXN][MAXN][MAXN][MAXN][MAXN]; // i, U, D, R_low, R_hi
lint pow4[MAXN];
vector<pii> lasers;
int n, s, e;

int go(int i, int lu, int ld, int lr0, int lr1) {
    if (i == n) return 0;
    if (dp[i][lu][ld][lr0][lr1] != -1) return dp[i][lu][ld][lr0][lr1];
    lint ret = 0;
    int ly = lasers[i].second;

    // Consider U
    if (ly < e && ly < lr0 && lr0 != OFF) ret += pow4[n - 1 - i];
    else ret += go(i + 1, (lu == OFF) ? ly : min(lu, ly), ld, lr0, lr1);

    // Consider D
    if (ly > e && ly > lr1 && lr1 != OFF) ret += pow4[n - 1 - i];
    else ret += go(i + 1, lu, (ld == OFF) ? ly : max(ld, ly), lr0, lr1);

    // Consider L
    if (ly > s && ly < ld && ld != OFF) ret += pow4[n - 1 - i];
    else if (ly < s && ly > lu && lu != OFF) ret += pow4[n - 1 - i];
    else ret += go(i + 1, lu, ld, lr0, lr1);

    // Consider R
    if (ly < e) ret += go(i + 1, lu, ld, (lr0 == OFF) ? ly : max(lr0, ly), lr1);
    else if (ly > e) ret += go(i + 1, lu, ld, lr0, (lr1 == OFF) ? ly : min(lr1, ly));

    return dp[i][lu][ld][lr0][lr1] = ret % MOD;
}

void precalc() {
    pow4[0] = 1;
    for (int i = 1; i < MAXN; i++)
        pow4[i] = 4 * pow4[i - 1] % MOD;
}

int main() {
    precalc();
    int t = 1, T;
    for (cin >> T; t <= T; t++) {
        debug("Case %d...\n", t);
        cin >> n >> s >> e;
        memset(dp, -1, sizeof(dp));
        set<int> xs, ys;
        lasers.clear();
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            lasers.push_back(pii(x, y));
            xs.insert(x);
            ys.insert(y);
        }
        xs.insert(0), ys.insert(s);
        xs.insert(1000000000), ys.insert(e);
        map<int, int> mx, my;
        int cnt = 0;
        for (int x: xs) mx[x] = cnt++;
        cnt = 0;
        for (int y: ys) my[y] = cnt++;
        s = my[s], e = my[e];
        for (pii &laser: lasers) {
            laser.first = mx[laser.first];
            laser.second = my[laser.second];
        }
        if (s < e) {
            swap(s, e);
            for (pii &laser: lasers)
                laser.first = n + 1 - laser.first;
        }
        sort(lasers.begin(), lasers.end());
        // for (pii laser: lasers) {
        //     debug("laser: %d %d\n", laser.first, laser.second);
        //     assert(0 < laser.first && laser.first < n + 1);
        //     assert(0 <= laser.second && laser.second <= n + 1);
        // }
        printf("Case #%d: %d\n", t, go(0, OFF, OFF, OFF, OFF));
    }        
    return 0;
}
