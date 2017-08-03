#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int,int> pii;
typedef pair<lint,lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a > b) swap(a, b);
    vector<pii> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back(pii(x, y));
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int s = 0; s < 2; s++) {
                for (int ss = 0; ss < 2; ss++) {
                    int aa = v[i].first + v[j].first, bb = max(v[i].second, v[j].second);
                    if (aa > bb) swap(aa, bb);
                    if (aa <= a && bb <= b)
                        ans = max(ans, v[i].first*v[i].second + v[j].first*v[j].second);
                    swap(v[i].first, v[i].second);
                }
                swap(v[j].first, v[j].second);
            }
        }
    }
    cout << ans << endl;    
    return 0;
}
