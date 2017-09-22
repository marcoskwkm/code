#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

int v[3 * MAXN];
int add[3 * MAXN];
int l[MAXN], r[MAXN];

template<class T> struct StaticRMQ {
    static const int LOG = 20;
    vector<T> rmq[LOG];
    int n;

    StaticRMQ(const vector<T> &v) : n(v.size()) {
        for (int i = 0; i < LOG; i++)
            rmq[i].resize(n);
        for (int i = 0; i < n; i++)
            rmq[0][i] = v[i];
        for (int k = 1; k < LOG; k++)
            for (int i = 0; i < n; i++)
                rmq[k][i] = min(rmq[k - 1][i], rmq[k - 1][min(n - 1, i + (1 << (k - 1)))]);
    }

    T get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(rmq[k][l], rmq[k][r - (1 << k) + 1]);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> coords;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &l[i], &r[i]);
        coords.push_back(l[i]);
        coords.push_back(r[i]);
        coords.push_back(r[i] + 1);
    }
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    map<int, int> mp;
    int x = 1;
    for (int c: coords) {
        mp[c] = x++;
        // printf("%d -> %d\n", c, mp[c]);
    }
    for (int i = 0; i < n; i++) {
        add[mp[l[i]]]++;
        add[mp[r[i] + 1]]--;
    }

    for (int i = 1; i < x; i++) {
        v[i] = v[i - 1] + add[i];
        // printf("v[%d] = %d\n", i, v[i]);
    }

    vector<int> vv(v, v + x);
    // for (size_t i = 0; i < vv.size(); i++)
    //     printf("vv[%d] = %d\n", i, vv[i]);
    StaticRMQ<int> rmq(vv);
    for (int i = 0; i < n; i++) {
        if (rmq.get(mp[l[i]], mp[r[i]]) > 1) {
            printf("%d\n", i + 1);
            return 0;
        }
    }
    printf("-1\n");        
    return 0;
}
