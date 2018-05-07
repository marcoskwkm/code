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
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    bool ok = 1;
    while (ok && v.size() > 1) {
        int hi = 0;
        for (int j = 0; j < (int)v.size(); j++) {
            if (j + 1 < (int)v.size() && abs(v[j] - v[j + 1]) > 1) {
                ok = 0;
                break;
            }
            if (v[j] > v[hi]) hi = j;
        }
        v.erase(v.begin() + hi);
    }
    printf("%s\n", ok ? "YES" : "NO");
    return 0;
}
