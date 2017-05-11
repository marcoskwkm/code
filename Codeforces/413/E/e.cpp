#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int cost[MAXN];
bool likes_a[MAXN];
bool likes_b[MAXN];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    set<pii> all, sa, sb, sc;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cost[i]);
        all.insert(pii(cost[i], i));
    }
    int ka;
    for (scanf("%d", &ka); ka--;) {
        int id;
        scanf("%d", &id);
        likes_a[id] = 1;
    }
    int kb;
    for (scanf("%d", &kb); kb--;) {
        int id;
        scanf("%d", &id);
        likes_b[id] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (likes_a[i] && likes_b[i]) {
            sc.insert(pii(cost[i], i));
            all.erase(pii(cost[i], i));
        }
        else if (likes_a[i])
            sa.insert(pii(cost[i], i));
        else if (likes_b[i])
            sb.insert(pii(cost[i], i));
    }

    lint cur = 0, ans = LINF;
    int qa = 0, qb = 0, taken = 0;
    vector<pii> common;
    for (pii p: sc) {
        common.push_back(p);
        all.erase(p);
        qa++; qb++; taken++;
        cur += p.first;
        if (taken == m) break;
    }
    if (2 * k - taken > m || sa.size() < k - taken || sb.size() < k - taken) {
        printf("-1\n");
        return 0;
    }
    while (qa < k) {
        qa++; taken++;
        cur += sa.begin()->first;
        all.erase(*sa.begin());
        sa.erase(sa.begin());
    }
    while (qb < k) {
        qb++; taken++;
        cur += sb.begin()->first;
        all.erase(*sa.begin());
        sb.erase(sb.begin());
    }
    set<pii, greater<pii>> none;
    while (taken < m) {
        taken++;
        pii p = *all.begin();
        all.erase(p);
        if (likes_a[p.second]) {
            qa++;
            sa.erase(p);
        }
        else if (likes_b[p.second]) {
            qb++;
            sb.erase(p);
        }
        else none.insert(p);
        cur += p.first;
    }
    ans = min(ans, cur);
    while (!common.empty()) {
        pii p = common.back();
        common.pop_back();
        qa--; qb--; taken--;
        bool ok = 1;
        while (qa < k) {
            if (sa.empty()) {
                ok = 0;
                break;
            }
            taken++;
            qa++;
            cur += sa.begin()->first;
            all.erase(*sa.begin());
            sa.erase(sa.begin());
        }
        while (qb < k) {
            if (sb.empty()) {
                ok = 0;
                break;
            }
            taken++; qb++;
            cur += sb.begin()->first;
            all.erase(*sb.begin());
            sb.erase(sb.begin());
        }
        while (taken > m) {
            if (none.empty()) {
                ok = 0;
                break;
            }
            taken--;
            cur -= none.begin()->first;
            all.insert(*none.begin());
            none.erase(none.begin());
        }
        if (!ok) break;
        ans = min(ans, cur);
    }
    
    printf("%lld\n", ans);
    return 0;
}
