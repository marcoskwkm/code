#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int t;
    for (scanf("%d", &t); t--;) {
        int n;
        scanf("%d", &n);
        vector<int> w, h;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            w.push_back(x);
        }
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            h.push_back(x);
        }
        sort(h.begin(), h.end());
        swap(w[0], w.back());
        int lim = w.back() * h.back();
        w.pop_back();
        h.pop_back();
        sort(w.begin(), w.end(), greater<int>());
        bool ok = 1;
        for (int ww: w) {
            int take = -1;
            for (size_t i = 0; i < h.size(); i++)
                if (ww * h[i] < lim && (take == -1 || h[take] < h[i]))
                    take = i;
            if (take == -1) {
                ok = 0;
                break;
            }
            swap(h[take], h.back());
            h.pop_back();
        }
        printf("%s\n", ok ? "YES" : "NO");
    }            
    return 0;
}
