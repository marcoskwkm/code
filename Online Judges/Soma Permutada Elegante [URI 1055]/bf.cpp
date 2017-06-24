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
    srand(time(0));
    int n = 9;
    vector<pii> v(n);
    for (int i = 0; i < n; i++)
        v[i] = pii(rand() % 1000, 0);
    printf("%d", n);
    for (int i = 0; i < n; i++)
        printf(" %d", v[i].first);
    printf("\n");
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++)
        v[i].second = i;
    vector<vector<pii>> bests;
    int best = 0;
    do {
        int got = 0;
        for (int i = 0; i < n - 1; i++)
            got += abs(v[i].first - v[i + 1].first);
        if (got > best) {
            best = got;
            bests.clear();
            bests.push_back(v);
        }
        else if (best == got)
            bests.push_back(v);
    } while (next_permutation(v.begin(), v.end()));

    printf("%d\n", best);
    for (auto vv: bests) {
        for (pii x: vv) printf("%d(%d) ", x.first, x.second);
        printf("\n");
    }        
    return 0;
}
