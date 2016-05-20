#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const double PI = acos(-1.0L);
const double EPS = 1e-9;

struct Segment {
    int x0, x1, y;
    Segment(int a, int b, int c) {
        x0 = a; x1 = b; y = c;
    }
};

vector<Segment> segs;

struct Event {
    int kind, value;
    lint dy, dx;
    Event(int b, int c, lint d, lint e) {
        kind = b; value = c;
        dy = d; dx = e;
    }
}; 

int n;

lint go(int idx, int k) {
    vector<Event> events;
    int xo = segs[idx].x0;
    int yo = segs[idx].y;
    if (k == 1) xo = segs[idx].x1;
    for (int i = 0; i < n; i++) {
        if (segs[i].y == segs[idx].y) continue;
        lint dy = yo - segs[i].y, dx = segs[i].x1 - xo;
        if (dy < 0) dy *= -1, dx *= -1;            
        events.push_back(Event((segs[i].y < yo), segs[i].x1 - segs[i].x0, dy, dx));
        dy = yo - segs[i].y, dx = segs[i].x0 - xo;        
        if (dy < 0) dy *= -1, dx *= -1;            
        events.push_back(Event((segs[i].y > yo), segs[i].x1 - segs[i].x0, dy, dx));
    }
    sort(events.begin(), events.end(), [](Event a, Event b) {
        lint lhs = a.dy * b.dx;
        lint rhs = b.dy * a.dx;
        if (lhs == rhs) return a.kind > b.kind;
        return lhs < rhs;
    });
    lint cur = 0, ret = 0;    
    for (Event event: events) {
        if (event.kind == 1) {
            cur += event.value;
            ret = max(ret, cur);
        }
        else {
            cur -= event.value;
        }
    }
    return ret + segs[idx].x1 - segs[idx].x0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x0, x1, y;
        scanf("%d%d%d", &x0, &x1, &y);
        if (x0 > x1) swap(x0, x1);
        segs.push_back(Segment(x0, x1, y));
    }
    lint ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, max(go(i, 0), go(i, 1)));

    printf("%lld\n", ans);    
    return 0;
}
