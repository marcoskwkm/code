#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXD = (int)1e6 + 10;
const int MAXN = (int)2e5 + 10;
const int LOGT = 30;

struct Contest {
    int l, h, i;
    Contest(int _l = 0, int _h = 0, int _i = 0) : l(_l), h(_h), i(_i) {}
};

vector<Contest> days[MAXD];
set<tiii> states[MAXD];
pii accmaxs[MAXD];
int prv[MAXN];

int main() {
    int n, s, dt;
    cin >> n >> s >> dt;
    for (int i = 0; i < n; i++) {

        int d, l, h;
        scanf("%d%d%d", &d, &l, &h);
        days[d].push_back(Contest(l, h, i));
        assert(d < MAXD);
    }
    memset(prv, -1, sizeof(prv));

    int ans = s, last = -1;
    states[0].insert(tiii(s, 0, -1));
    accmaxs[0] = pii(s, -1);
    for (int d = 1; d < MAXD; d++) {
        states[d].insert(tiii(s, 0, -1));
        accmaxs[d] = accmaxs[d - 1];
        for (const auto &contest: days[d]) {            
            int min_fat = INF, best = -1;
            if (d >= LOGT && accmaxs[d - LOGT].first >= contest.l)
                min_fat = 0, best = accmaxs[d - LOGT].second;
            else {
                for (int pd = max(0, d - LOGT); pd < d; pd++) {
                    auto it = states[pd].lower_bound(tiii(contest.l, 0, -1));
                    if (it == states[pd].end()) continue;
                    int got = ((get<1>(*it)) >> (d - pd - 1));
                    if (got < min_fat) {
                        min_fat = got;
                        best = get<2>(*it);
                    }
                }
            }
            // debug("%d comes from %d (min_fat = %d, s = %d)\n", contest.i + 1, best + 1, min_fat, contest.h - min_fat);
            if (min_fat == INF || contest.h - min_fat <= s) continue;
            assert(min_fat + dt < 2000000);
            auto it = states[d].lower_bound(tiii(contest.h - min_fat, 0, -1));
            if (it != states[d].end() && get<1>(*it) <= min_fat + dt) continue;
            auto it2 = states[d].insert(tiii(contest.h - min_fat, min_fat + dt, contest.i)).first;
            while (next(it2) != states[d].end() && get<0>(*next(it2)) == contest.h - min_fat)
                states[d].erase(next(it2));
            while (it2 != states[d].begin() && get<1>(*prev(it2)) >= min_fat + dt)
                states[d].erase(prev(it2));
            if (contest.h - min_fat > ans)
                ans = contest.h - min_fat, last = contest.i;
            if (contest.h - min_fat > accmaxs[d].first)
                accmaxs[d] = pii(contest.h - min_fat, contest.i);
            prv[contest.i] = best;
            // for (auto x: states[d])
            //     debug("(%d, %d) ", get<0>(x), get<1>(x));
            // debug("\n");
        }
    }
                                                     
    vector<int> sol;
    while (last != -1) {
        sol.push_back(last + 1);
        last = prv[last];
    }
    printf("%d %d\n", ans, (int)sol.size());
    reverse(sol.begin(), sol.end());
    for (int x: sol) printf("%d ", x);
    printf("\n");
        
    return 0;
}
