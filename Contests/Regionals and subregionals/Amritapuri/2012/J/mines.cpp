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

lint bit[2 * MAXN];

void update(int x, int val) {
    for (; x > 0; x -= x & -x)
        bit[x] += val;
}

int query(int x) {
    lint ret = 0;
    for (; x < 2 * MAXN; x += x & -x)
        ret += bit[x];
    return ret;
}    

struct Event {
    int x, y1, y2, i, k;
    Event(int _x, int _y1, int _y2, int _i, int _k) :
        x(_x), y1(_y1), y2(_y2), i(_i), k(_k) {}
    bool operator< (const Event &that) {
        if (x == that.x) return k < that.k;
        return x < that.x;
    }
};

int ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    vector<Event> events;
    vector<int> ys;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        events.push_back(Event(x1, y1, y2, i, 1));
        events.push_back(Event(x2, y1, y2, i, 0));
        ys.push_back(y1);
        ys.push_back(y2);
    }
    sort(events.begin(), events.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    map<int, int> mp;
    for (size_t i = 0; i < ys.size(); i++)
        mp[ys[i]] = i + 1;

    update(2 * n, -1);
    for (const Event &event: events) {
        int y1 = mp[event.y1], y2 = mp[event.y2];
        if (event.k == 1) {
            ans[event.i] = query(y1);
            update(y2 - 1, event.i - ans[event.i]);
            update(y1 - 1, ans[event.i] - event.i);
        }
        else {
            update(y2 - 1, ans[event.i] - event.i);
            update(y1 - 1, event.i - ans[event.i]);
        }
    }        
    for (int i = 0; i < n; i++)
        printf("%d\n", ans[i]);
    return 0;
}
