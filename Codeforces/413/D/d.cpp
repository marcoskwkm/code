#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int a, b;
vector<pii> v;

int go(lint h, lint w, int i, int q) {
    if (i == v.size()) return INF;
    int take_h = 0, take_w = 0;
    while (take_h < v[i].second && h < a) {
        take_h++;
        h *= v[i].first;
    }
    while (take_h + take_w < v[i].second && w < b) {
        take_w++;
        w *= v[i].first;
    }
    if (h >= a && w >= b) return q + take_h + take_w;
    assert(take_h + take_w == v[i].second);
    int ret = go(h, w, i + 1, q + v[i].second);
    while (take_h > 0 && w < b) {
        h /= v[i].first;
        w *= v[i].first;
        ret = min(ret, go(h, w, i + 1, q + v[i].second));
    }
    return ret;
}        

int main() {
    int h, w, n;
    map<int, int> freq;
    cin >> a >> b >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        freq[x]++;
    }
    int total = 0;
    for (auto it = freq.rbegin(); it != freq.rend(); it++) {
        v.push_back(pii(it->first, min(it->second, 40 - total)));
        total += v.back().second;
        if (total == 40) break;
    }

    int ans = min(go(h, w, 0, 0), go(w, h, 0, 0));
    if (ans == INF) printf("-1\n");
    else printf("%d\n", ans);    
    return 0;
}
