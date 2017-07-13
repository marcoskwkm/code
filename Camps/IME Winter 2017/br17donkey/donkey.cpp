#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)5e4 + 10;

struct Rectangle {
    int x, h, w, i;
    Rectangle(int _x = 0, int _h = 0, int _w = 0, int _i = 0) {
        x = _x, h = _h, w = _w, i = _i;
    };
};

int id[MAXN];
int n, H;

inline bool can_swap(const Rectangle &a, const Rectangle &b) {
    return a.h + b.h <= H;
}

int bit[MAXN];

void update(int i, int val) {
    for (; i < MAXN; i += i & -i)
        bit[i] = max(bit[i], val);
}

int query(int i) {
    int ret = 0;
    for (; i > 0; i -= i & -i)
        ret = max(ret, bit[i]);
    return ret;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        memset(bit, 0, sizeof(bit));
        scanf("%d%d", &n, &H);
        vector<Rectangle> beg;
        for (int i = 0; i < n; i++) {
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            if (x0 > x1) swap(x0, x1);
            if (y0 > y1) swap(y0, y1);
            beg.push_back(Rectangle(x0, y1 - y0, x1 - x0, i));
        }
        sort(beg.begin(), beg.end(), [](Rectangle a, Rectangle b) { return a.x < b.x; });
        for (int i = 0; i < n; i++)
            id[beg[i].i] = i;
        
        vector<Rectangle> end;
        vector<int> vh;
        for (int i = 0; i < n; i++) {
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            if (x0 > x1) swap(x0, x1);
            if (y0 > y1) swap(y0, y1);
            end.push_back(Rectangle(x0, y1 - y0, x1 - x0, i));
            vh.push_back(y1 - y0);
        }
        sort(end.begin(), end.end(), [](Rectangle a, Rectangle b) { return a.x < b.x; });

        bool ok = 1;
        for (int i = n - 1; i >= 0 && ok; i--) {
            int got = query(id[end[i].i] + 1);
            if (got > H - end[i].h) {
                ok = 0;
                break;
            }
            update(id[end[i].i] + 1, end[i].h);            
        }
        printf("%s\n", ok ? "ANO" : "NIE");
    }        
    return 0;
}
