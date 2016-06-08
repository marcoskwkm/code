#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXK = (int)1e5 + 10;

vector<pll> bamboo[MAXK];
int last[MAXK];
int n, k;
lint x;

pll solve(int i, lint motiv) {
    int l = 0, r = (int)bamboo.size();
    while (l < r) {
        int mid = (l + r + 1)/2;
        if (bamboo[mid].first <= motiv) l = mid;
        else r = mid - 1;
    }
    if (bamboo[l].first <= motiv) {
        lint got = tree_query(i, 0, 0, (int)bamboo.size() - 1, 0, l);
        if (got != LINF) {
            tree_update(
        
    else {
        while (lastn[i] < (int)negc[i].size() && negc[i][lastn[i]].first > motiv)
            lastn[i]++;
        if (lastn[i] == (int)negc[i].size()) return pll(-1, -1);
        else return pll(negc[i][lastn[i]++].second, 0);
    }
}

int main() {
    while (scanf("%d%d%lld", &n, &k, &x) > 0) {
        for (int i = 0; i < k; i++) {
            bamboo[i].clear();
            tree[i].clear();
            last[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            int t;
            lint p, c;
            scanf("%d%lld%lld", &t, &p, &c);
            bamboo[t].push_back(pll(p, c));
        }
        for (int i = 0; i < k; i++) {
            sort(bamboo[i].begin(), bamboo[i].end(), [](pll a, pll b) {
                if (a.second >= 0 && b.second < 0) return 1;
                if (a.second < 0 && b.second >= 0) return 0;
                if (a.second >= 0)
                else {
                    
                    
        }
        int ans = 0, cur = 0;
        lint curmotiv = x;
        while (1) {
            pll got = solve(cur, curmotiv);
            if (got.second == -1) break;
            ans++;
            curmotiv += got.first;
            cur++;
            if (cur == k) cur = 0;
        }        
        printf("%d\n", ans);
    }
    return 0;
}
