#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int SAMPLE_SZ = 100;
const int MAXN = (int)3e5 + 10;

lint v[MAXN];
int sample[SAMPLE_SZ];

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        scanf("%lld", &v[i]);

    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--, r--;
        r = min(r, l + SAMPLE_SZ - 1);
        int sz = r - l + 1;
        for (int i = 0; i < sz; i++)
            sample[i] = l + i;
        sort(sample, sample + sz, [](int a, int b) { return v[a] < v[b]; });
        bool found = 0;
        for (int i = 0; i + 2 < sz; i++) {
            if (v[sample[i]] + v[sample[i + 1]] > v[sample[i + 2]]) {
                found = 1;
                vector<int> v = {sample[i], sample[i + 1], sample[i + 2]};
                sort(v.begin(), v.end());
                printf("%d %d %d\n", v[0] + 1, v[1] + 1, v[2] + 1);
                break;
            }
        }
        if (!found) printf("-1\n");
        assert(sz < SAMPLE_SZ || found);
    }    
    return 0;
}
