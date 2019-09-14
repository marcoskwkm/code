// TLE (fuck uri)

#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e4 + 10;
const int MAXD = (int)1e5 + 10;

struct Event {
    int type;
    int x, y1, y2;
    Event() {}
    Event(int _type, int _x, int _y1, int _y2) : type(_type), x(_x), y1(_y1), y2(_y2) {}
};

int n, P;
vector<tiii> hSeg; // y, x1, x2
vector<tiii> vSeg; // x, y1, y2
int rx1, ry1, rx2, ry2;
Event events[2 * MAXN];
int nEvents;

int active[4 * MAXD + 10];
int low[4 * MAXD + 10], qlow[4 * MAXD + 10];
int lazy[4 * MAXD + 10];

void build(int i, int l, int r) {
    active[i] = low[i] = lazy[i] = 0;
    qlow[i] = r - l + 1;
    if (l < r) {
        int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
        build(L, l, mid); build(R, mid + 1, r);
    }
}

void refresh(int i, int l, int r) {
    if (!lazy[i]) return;
    
    if (l < r) {
        int L = 2 * i + 1, R = 2 * i + 2;
        lazy[L] += lazy[i];
        lazy[R] += lazy[i];
    }

    if (low[i] > 0 && low[i] + lazy[i] == 0)
        active[i] -= qlow[i];
    else if (low[i] == 0 && low[i] + lazy[i] > 0)
        active[i] = r - l + 1;
    low[i] += lazy[i];
    
    lazy[i] = 0;
}

void update(int i, int l, int r, int ql, int qr, int val) {
    refresh(i, l, r);
    if (r < ql || qr < l) return;
    if (ql <= l && r <= qr) {
        lazy[i] += val;
        refresh(i, l, r);
        return;
    }

    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    update(L, l, mid, ql, qr, val); update(R, mid + 1, r, ql, qr, val);

    active[i] = active[L] + active[R];
    low[i] = min(low[L], low[R]);
    if (low[L] == low[R])
        qlow[i] = qlow[L] + qlow[R];
    else if (low[L] < low[R])
        qlow[i] = qlow[L];
    else
        qlow[i] = qlow[R];
}

int query(int i, int l, int r, int ql, int qr) {
    refresh(i, l, r);
    if (r < ql || qr < l) return 0;
    if (ql <= l && r <= qr) return active[i];
    int L = 2 * i + 1, R = 2 * i + 2, mid = (l + r) / 2;
    return query(L, l, mid, ql, qr) + query(R, mid + 1, r, ql, qr);
}

inline void addEvents(int x1, int y1, int x2, int y2) {
    events[nEvents++] = Event(0, x1, y1, y2);
    events[nEvents++] = Event(1, x2, y1, y2);
}

bool go(int r) {
    build(0, 0, MAXD);
    nEvents = 0;
    for (tiii seg: hSeg) {
        int y, x1, x2;
        tie(y, x1, x2) = seg;
        int srx1 = max(rx1, x1 - r), srx2 = min(rx2, x2 + r);
        int sry1 = max(ry1, y - r), sry2 = min(ry2, y + r);
        addEvents(srx1, sry1, srx2, sry2);
    }
    for (tiii seg: vSeg) {
        int x, y1, y2;
        tie(x, y1, y2) = seg;
        int srx1 = max(rx1, x - r), srx2 = min(rx2, x + r);
        int sry1 = max(ry1, y1 - r), sry2 = min(ry2, y2 + r);
        addEvents(srx1, sry1, srx2, sry2);
    }

    sort(events, events + nEvents, [](const Event &a, const Event &b) {
        if (a.x == b.x)
            return a.type < b.type;
        return a.x < b.x;
    });

    lint area = 0;
    int lastX = rx1;
    for (int i = 0; i < nEvents; i++) {
        const Event &event = events[i];
        area += query(0, 0, MAXD, 0, MAXD) * lint(event.x - lastX);
        lastX = event.x;
        // debug("event: (%d, %d, %d, %d), area = %lld\n", event.type, event.x, event.y1, event.y2, area);

        if (event.type == 0)
            update(0, 0, MAXD, event.y1, event.y2 - 1, 1);
        else
            update(0, 0, MAXD, event.y1, event.y2 - 1, -1);

        // debug("active: %d\n", query(0, 0, MAXD, 0, MAXD));
    }

    // debug("%lld vs %lld\n", 100 * area, lint(rx2 - rx1) * lint(ry2 - ry1) * P);
    return 100 * area >= lint(rx2 - rx1) * lint(ry2 - ry1) * P;
}    

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 == x2)
            vSeg.push_back(tiii(x1, y1, y2));
        else
            hSeg.push_back(tiii(y1, x1, x2));
    }

    cin >> P;
    cin >> rx1 >> ry1 >> rx2 >> ry2;

    int l = 0, r = max(rx2 - rx1, ry2 - ry1);
    while (l < r) {
        int m = (l + r) / 2;
        // debug("m = %d\n", m);
        if (go(m)) r = m;
        else l = m + 1;
    }

    cout << l << endl;    
    return 0;
}
