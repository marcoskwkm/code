#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<lint, lint, lint> Subset;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 44;

int v[MAXN], w[MAXN];
int ord[MAXN];
Subset lo_masks[1 << (MAXN / 2)], hi_masks[1 << (MAXN / 2)];
int lo_len, hi_len;

int main() {
    int n, b;
    cin >> n >> b;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &v[i], &w[i]);
        ord[i] = i;
    }
    sort(ord, ord + n, [&](int i, int j) { return v[i] < v[j]; });

    vector<int> lo, hi;
    for (int i = 0; i < n / 2; i++) lo.push_back(ord[i]);
    for (int i = n / 2; i < n; i++) hi.push_back(ord[i]);

    for (int m = 0; m < (1 << lo.size()); m++) {
        lint true_mask = 0;
        lint sum_v = 0, sum_w = 0;
        bool ok = 1;
        for (size_t i = 0; i < lo.size(); i++) {
            if (m & (1 << i)) {
                if (v[lo[i]] > sum_v + 1) {
                    ok = 0;
                    break;
                }
                sum_v += v[lo[i]];
                sum_w += w[lo[i]];
                true_mask |= (1LL << lo[i]);
            }
        }
        if (!ok) continue;
        lo_masks[lo_len++] = Subset(sum_v, sum_w, true_mask);
    }

    for (int m = 0; m < (1 << hi.size()); m++) {
        lint true_mask = 0;
        lint sum_v = 0, sum_w = 0, gap = 0;
        for (size_t i = 0; i < hi.size(); i++) {
            if (m & (1 << i)) {
                if (v[hi[i]] > sum_v + 1)
                    gap = max(gap, v[hi[i]] - (sum_v + 1));
                sum_v += v[hi[i]];
                sum_w += w[hi[i]];
                true_mask |= (1LL << hi[i]);
            }
        }
        hi_masks[hi_len++] = Subset(max(b - sum_v, gap), sum_w, true_mask);
    }

    sort(lo_masks, lo_masks + lo_len, greater<Subset>());
    sort(hi_masks, hi_masks + hi_len, greater<Subset>());

    lint best_w = LINF, low_w = LINF;
    lint best_mask, low_mask;
    int at = 0;    
    for (int i = 0; i < hi_len; i++) {
        while (at < lo_len && get<0>(lo_masks[at]) >= get<0>(hi_masks[i])) {
            if (get<1>(lo_masks[at]) < low_w) {
                low_w = get<1>(lo_masks[at]);
                low_mask = get<2>(lo_masks[at]);
            }
            at++;
        }
        if (low_w + get<1>(hi_masks[i]) < best_w) {
            best_w = low_w + get<1>(hi_masks[i]);
            best_mask = low_mask | get<2>(hi_masks[i]);
        }
    }

    if (best_w == LINF) printf("-1\n");
    else {
        printf("%d\n", __builtin_popcountll(best_mask));
        for (int i = 0; i < n; i++)
            if (best_mask & (1LL << i))
                printf("%d ", i + 1);
        printf("\n");
    }
    return 0;
}
