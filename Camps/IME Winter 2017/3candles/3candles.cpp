#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int c1, c2, c3, t3, t1, t2;

bool check(int x1, int x2, int x3, const vector<int> &c) {
    vector<pii> event;
    event.push_back(pii(x1, 1));
    event.push_back(pii(x1 + c[0], -1));
    event.push_back(pii(x2, 1));
    event.push_back(pii(x2 + c[1], -1));
    event.push_back(pii(x3, 1));
    event.push_back(pii(x3 + c[2], -1));
    sort(event.begin(), event.end());
    int cur = 0, last = 0;
    int q[4];
    memset(q, 0, sizeof(q));
    for (pii p: event) {
        q[cur] += p.first - last;
        last = p.first;
        cur += p.second;
    }
    return q[1] == t1 && q[2] == t2 && q[3] == t3;
}

int main() {
    cin >> c1 >> c2 >> c3 >> t3 >> t1;
    if (c1 > c2) swap(c1, c2);
    if (c2 > c3) swap(c2, c3);
    if (c1 > c2) swap(c1, c2);
    c1 *= 2; c2 *= 2; c3 *= 2; t3 *= 2; t1 *= 2;
    t2 = (c1 + c2 + c3 - 3*t3 - t1) / 2;
    if (t2 < 0) return 0;
    bool ok = 0;
    if (t3 == 0) {
        if (t2 <= min(c3, c1 + c2))
            ok = 1;
    }
    else {
        vector<int> c = {c1, c2, c3};
        do {
            for (int x1 = 0; x1 < 600 && !ok; x1++) {
                for (int x2 = 0; x2 < 600 && !ok; x2++) {
                    int l = max(x1, x2);
                    int r = min(x1 + c[0], x2 + c[1]);
                    if (check(x1, x2, r - t3, c) || check(x1, x2, l + t3 - c3, c)) {
                        ok = 1;
                        break;
                    }
                }
            }
        } while (next_permutation(c.begin(), c.end()) && !ok);
    }
    if (!ok) return 0;                
    printf("%d", t2 / 2);
    if (t2 & 1) printf(".5");
    printf("\n");    
    return 0;
}
