#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

lint v[MAXN];
lint acc[MAXN];
int d;
vector<int> len;

vector<int> get_idx(int x) {
    vector<int> ret(d);
    for (int i = d - 1; i >= 0; i--) {
        ret[i] = x % len[i];
        x /= len[i];
    }
    return ret;
}

int get_idx(vector<int> vv) {
    int ret = 0;
    for (int i = 0; i < d; i++)
        ret = len[i] * ret + vv[i];
    return ret;
}

void build_acc(int x) {
    vector<int> vi = get_idx(x);
    acc[x] = v[x];
    for (int mask = 0; mask < (1 << d) - 1; mask++) {
        bool exists = 1;
        vector<int> vv = vi;
        for (int i = 0; i < d; i++) {
            if ((mask & (1 << i)) == 0) {
                vv[i]--;
                if (vv[i] < 0) exists = 0;
            }
        }
        lint val = 0;
        if (exists) val = acc[get_idx(vv)];
        if ((__builtin_popcount(mask) + d) % 2 == 1)
            acc[x] += val;
        else
            acc[x] -= val;
    }
}

int main() {
    cin >> d;
    int n = 1;
    for (int i = 0; i < d; i++) {
        int l;
        scanf("%d", &l);
        len.push_back(l);
        n *= l;
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        build_acc(i);
    }
    int q;
    for (cin >> q; q--;) {
        vector<int> vl(d), vr(d);
        for (int i = 0; i < d; i++)
            scanf("%d", &vl[i]);
        for (int i = 0; i < d; i++)
            scanf("%d", &vr[i]);
        lint ans = 0;
        for (int mask = 0; mask < (1 << d); mask++) {
            vector<int> vv(d);
            bool exists = 1;
            for (int i = 0; i < d; i++) {
                if (mask & (1 << i)) vv[i] = vr[i] - 1;
                else vv[i] = vl[i] - 2;
                if (vv[i] < 0) exists = 0;
            }
            if (!exists) continue;
            if ((__builtin_popcount(mask) + d) % 2 == 0)
                ans += acc[get_idx(vv)];
            else
                ans -= acc[get_idx(vv)];
        }
        printf("%lld\n", ans);
    }    
    return 0;
}
