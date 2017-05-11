#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;
typedef tuple<int,int,int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

vector<tiii> fix(vector<tiii> v) {
    sort(v.begin(), v.end());
    vector<tiii> ret;
    for (const tiii &t: v) {
        while (!ret.empty() && get<1>(t) <= get<1>(ret.back()))
            ret.pop_back();
        if (!ret.empty() && get<0>(t) == get<0>(ret.back()))
            continue;
        ret.push_back(t);
    }
    return ret;
}

int go(const tiii &t, const vector<tiii> &v, int q) {
    int l = 0, r = v.size() - 1;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (get<1>(t) + get<1>(v[mid]) > q)
            r = mid - 1;
        else
            l = mid;
    }
    if (t == v[l]) l--;
    if (l < 0 || get<1>(t) + get<1>(v[l]) > q) return 0;
    return get<0>(t) + get<0>(v[l]);
}

int main() {
    int n, c, d;
    cin >> n >> c >> d;
    vector<tiii> coins, diams;
    int max_c = 0, max_d = 0;
    for (int i = 0; i < n; i++) {
        int b, p;
        char k;
        scanf("%d%d %c", &b, &p, &k);
        if (k == 'C') {
            coins.push_back(tiii(b, p, i));
            if (p <= c) max_c = max(max_c, b);
        }
        else {
            diams.push_back(tiii(b, p, i));
            if (p <= d) max_d = max(max_d, b);
        }
    }
    int ans = 0;
    if (max_c > 0 && max_d > 0) ans = max_c + max_d;

    vector<tiii> fixed_coins = fix(coins);
    vector<tiii> fixed_diams = fix(diams);

    for (const tiii &p: coins)
        ans = max(ans, go(p, fixed_coins, c));
    for (const tiii &p: diams)
        ans = max(ans, go(p, fixed_diams, d));
    printf("%d\n", ans);    
    return 0;
}
