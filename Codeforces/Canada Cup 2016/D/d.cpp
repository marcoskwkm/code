#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct cmp {
    bool operator() (pll a, pll b) {
        if (a.second - a.first == b.second - b.first)
            return a.first < b.first;
        return a.second - a.first < b.second - b.first;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    lint b, w;
    cin >> b >> w;
    vector<pll> behind;
    multiset<pll, cmp> pq;
    for (int i = 1; i < n; i++) {
        lint bb, ww;
        cin >> bb >> ww;
        if (bb > b) pq.insert(pll(bb, ww));
        else behind.push_back(pll(bb, ww));
    }
    sort(behind.begin(), behind.end(), [](pll a, pll b) {
        return a.first < b.first;
    });
    int ans = 1 + pq.size();
    while (1) {
        if (pq.empty()) break;
        pll p = *pq.begin();
        pq.erase(pq.begin());
        lint diff = p.second - p.first + 1;
        if (diff > b) break;
        b -= diff;
        while (!behind.empty() && behind.back().first > b) {
            pq.insert(behind.back());
            behind.pop_back();
        }
        ans = min<int>(ans, 1 + pq.size());
    }

    printf("%d\n", ans);    
    return 0;
}
