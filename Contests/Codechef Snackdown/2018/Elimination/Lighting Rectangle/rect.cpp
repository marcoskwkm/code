#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int dir[4];

bool go(int i, const vector<pii> &rects, const vector<int> &xs, const vector<int> &ys, int k) {
    if (i == k) {
        for (int x: xs) {
            for (int y: ys) {
                bool ok = 0;
                for (int j = 0; j < k; j++) {
                    int xr, yr;
                    tie(xr, yr) = rects[j];
                    if (x >= xr && y >= yr && dir[j] == 0) ok = 1;
                    if (x >= xr && y <= yr && dir[j] == 1) ok = 1;
                    if (x <= xr && y <= yr && dir[j] == 2) ok = 1;
                    if (x <= xr && y >= yr && dir[j] == 3) ok = 1;
                }
                if (!ok) return 0;
            }
        }
        return 1;
    }
    for (int j = 0; j < 4; j++) {
        dir[i] = j;
        if (go(i + 1, rects, xs, ys, k)) return 1;
    }
    return 0;
}

int main() {
    int t;
    for (cin >> t; t--;) {
        int n, k;
        cin >> k >> n;
        vector<pii> rects;
        vector<int> xs = {0, n - 1}, ys = {0, n - 1};
        for (int i = 0; i < k; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            rects.push_back(pii(x, y));
            xs.push_back(x);
            ys.push_back(y);
        }
        if (k >= 4) {
            printf("yes\n");
            continue;
        }
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        printf("%s\n", go(0, rects, xs, ys, k) ? "yes" : "no");
    }        
    return 0;
}
