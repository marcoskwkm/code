#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

lint r1[MAXN], r2[MAXN], c1[MAXN], c2[MAXN];
int n;

lint get_count(lint x, lint x1[], lint x2[], lint y1[], lint y2[]) {
    lint ret = 0;
    for (int i = 0; i < n; i++) {
        if (x < x1[i]) continue;
        lint xx = min(x, x2[i]);
        ret += (xx - x1[i] + 1) * (y2[i] - y1[i] + 1);
    }
    return ret;
}

inline lint pa(lint l, lint r) {
    lint q = r - l + 1;
    return q * (l + r) / 2;
}

lint sum_dist(lint x, lint l, lint r) {
    if (x <= l) return pa(l - x, r - x);
    if (x >= r) return pa(x - r, x - l);
    return pa(0, x - l) + pa(0, r - x);
}

lint get_dist(lint r, lint c) {
    lint ret = 0;
    for (int i = 0; i < n; i++) {
        lint sr = sum_dist(r, r1[i], r2[i]);
        lint sc = sum_dist(c, c1[i], c2[i]);
        ret += (c2[i] - c1[i] + 1) * sr + (r2[i] - r1[i] + 1) * sc;
    }
    return ret;
}

int main() {
    cin >> n;
    lint total = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld%lld", &c1[i], &r1[i], &c2[i], &r2[i]);
        total += (r2[i] - r1[i] + 1) * (c2[i] - c1[i] + 1);
    }

    lint l = -INF, r = INF;
    while (l < r) {
        lint mid = (l + r) / 2;
        if (l + r < 0 && (l + r) % 2 != 0) mid--;
        if (get_count(mid, r1, r2, c1, c2) >= total / 2) r = mid;
        else l = mid + 1;
    }
    lint mr = l;
    l = -INF, r = INF;
    while (l < r) {
        lint mid = (l + r) / 2;
        if (l + r < 0 && (l + r) % 2 != 0) mid--;
        if (get_count(mid, c1, c2, r1, r2) >= total / 2) r = mid;
        else l = mid + 1;
    }
    lint mc = l;
    
    lint best = LINF, br, bc;
    for (int i = 0; i < n; i++) {
        lint r = max(r1[i], min(r2[i], mr));
        lint c = max(c1[i], min(c2[i], mc));
        lint got = get_dist(r, c);
        if (got < best) {
            best = got;
            br = r, bc = c;
        }
        else if (got == best) {
            if (c < bc) {
                br = r, bc = c;
            }
            else if (c == bc && r < br) {
                br = r, bc = c;
            }
        }
    }

    printf("%lld\n%lld %lld\n", best, bc, br);
    return 0;
}
