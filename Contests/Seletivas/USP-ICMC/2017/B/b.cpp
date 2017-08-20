#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef pair<pii, pii> ppi;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXC = (int)2e6 + 10;
const int MAXN = (int)1e5 + 10;

int bit[MAXC];
int ans[MAXN];

struct Event {
    int x, y0, y1, k;
    Event(int _k, int _x, int _y0, int _y1) {
        k = _k, x = _x, y0 = _y0, y1 = _y1;
    }
};

void update(int i, int v) {
    for (; i > 0; i -= i & -i)
        bit[i] += v;
}

int query(int i) {
    int ret = 0;
    for (; i < MAXC; i += i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    int n, m;
    cin >> n >> m;
    map<int, int>my;
    vector<int> ys;
    vector<pii> dirt;
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        dirt.push_back(pii(x, y));
        ys.push_back(y);
    }
    vector<ppi> rectangle;
    for (int i = 0; i < m; i++) {
        int xl, yl, xh, yh;
        scanf("%d%d%d%d", &xl, &yl, &xh, &yh);
        rectangle.push_back(ppi(pii(xl, yl), pii(xh, yh)));
        ys.push_back(yl); ys.push_back(yh - 1);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (size_t i = 0; i < ys.size(); i++)
        my[ys[i]] = i + 1;

    vector<Event> events;
    for (auto r: rectangle) {
        events.push_back(Event(2, r.first.first, r.first.second, r.second.second - 1));
        events.push_back(Event(0, r.second.first, r.first.second, r.second.second - 1));
    }
    for (size_t i = 0; i < dirt.size(); i++)
        events.push_back(Event(1, dirt[i].first, dirt[i].second, i));

    sort(events.begin(), events.end(), [](Event a, Event b) {
        if (a.x != b.x) return a.x < b.x;
        return a.k < b.k;
    });

    for (Event event: events) {
        if (event.k == 0) {
            update(my[event.y1], -1);
            update(my[event.y0], 1);
            // debug("- %d(%d) %d(%d)\n", my[event.y0], event.y0, my[event.y1], event.y1);
        }
        else if (event.k == 2) {
            update(my[event.y1], 1);
            update(my[event.y0], -1);
            // debug("+ %d(%d) %d(%d)\n", my[event.y0], event.y0, my[event.y1], event.y1);
        }
        else {
            // debug("q %d(%d)\n", my[event.y0], event.y0);
            ans[event.y1] = query(my[event.y0]);
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", ans[i]);    
    return 0;
}

