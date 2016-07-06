#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)2e5 + 10;

const int P = (int)1e9 + 7;
const int MAXV = MAXN;

lint fat[MAXV], inv[MAXV], invfat[MAXV];

lint choose(int n, int k) {
    k = min(k, n - k);
    if (k < 0) return 0;
    return fat[n] * invfat[k] % P * invfat[n - k] % P;
}

lint arrange(int n, int k) {
    if (k > n) return 0;
    return fat[n] * invfat[n - k] % P;
}

lint modexp(lint b, lint e) {
    lint ret = 1, aux = b;
    while (e) {
        if (e & 1) ret = ret * aux % P;
        aux = aux * aux % P;
        e >>= 1;
    }
    return ret;
}

void precalc() {
    fat[0] = fat[1] = 1;
    invfat[0] = invfat[1] = 1;
    inv[1] = 1;
    for (int n = 2; n < MAXV; n++) {
        fat[n] = fat[n - 1] * n % P;
        inv[n] = P - P/n * inv[P%n] % P;
        invfat[n] = invfat[n - 1] * inv[n] % P;
    }
}

int main() {
    precalc();
    int n, k;
    scanf("%d%d", &n, &k);
    map<int, int> ml, mr;
    vector<pii> l_int, r_int;
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        ml[l]++;
        mr[r]++;
        l_int.push_back(pii(l, r));
        r_int.push_back(pii(l, r));
    }
    sort(l_int.begin(), l_int.end(), [](pii a, pii b) {
        return a.first < b.first;
    });

    sort(r_int.begin(), r_int.end(), [](pii a, pii b) {
        return a.second > b.second;
    });
    
    lint ans = 0;
    // closing
    int acc = 0;
    int il = 0, ir = 0;
    multiset<int> sl;
    multiset<int, greater<int>> sr;
    for (auto it = mr.rbegin(); it != mr.rend(); it++) {
        int q = it->second;
        int val = it->first;
        while (ir < n && r_int[ir].second >= val) {
            acc++;
            sr.insert(r_int[ir++].first);
        }
        while (!sr.empty() && *sr.begin() > val) {
            acc--;
            sr.erase(sr.begin());
        }
        assert(acc >= q);
        ans += val * (choose(acc, k) - choose(acc - q, k)) % P;
        ans %= P;
    }

    // opening
    acc = 0;
    for (auto it = ml.begin(); it != ml.end(); it++) {
        int q = it->second;
        int val = it->first;
        while (il < n && l_int[il].first <= val) {
            acc++;
            sl.insert(l_int[il++].second);
        }
        while (!sl.empty() && *sl.begin() < val) {
            acc--;
            sl.erase(sl.begin());
        }
        assert(acc >= q);
        ans -= (val - 1) * (choose(acc, k) - choose(acc - q, k)) % P;
        ans %= P;
    }

    cout << (ans + P) % P << endl;
    return 0;
}
