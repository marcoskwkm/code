#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readIntArray(v, n) for_each(v.begin(), v.begin() + n, [](int &x) { scanf("%d", &x); })
#define readLintArray(v, n) for_each(v.begin(), v.begin() + n, [](lint &x) { scanf("%lld", &x); })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n;
    cin >> n;

    vector<pii> black, white;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if ((r + c) & 1) {
                black.push_back(pii(r + 1, c + 1));
            } else {
                white.push_back(pii(r + 1, c + 1));
            }
        }
    }

    bool gg_n00b = 0;
    for (int s = 0; s < n * n; s++) {
        int a;
        scanf("%d", &a);
        if (!gg_n00b) {
            if (a == 1) {
                auto [r, c] = white.back();
                white.pop_back();
                printf("2 %d %d\n", r, c);
                fflush(stdout);
                if (white.empty()) {
                    gg_n00b = 1;
                }
            } else {
                auto [r, c] = black.back();
                black.pop_back();
                printf("1 %d %d\n", r, c);
                fflush(stdout);
                if (black.empty()) {
                    gg_n00b = 1;
                }
            }
        } else {
            if (!white.empty()) {
                auto [r, c] = white.back();
                white.pop_back();
                printf("%d %d %d\n", a == 2 ? 3 : 2, r, c);
                fflush(stdout);
            } else {
                auto [r, c] = black.back();
                black.pop_back();
                printf("%d %d %d\n", a == 1 ? 3 : 1, r, c);
                fflush(stdout);
            }
        }
    }
    return 0;
}
