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
    int t = 1, T;
    for (scanf("%d", &T); t <= T; t++) {
        printf("Case #%d:", t);
        int n, k;
        lint v;
        cin >> n >> k >> v;
        v = (k * (v - 1) + 1) % n;
        vector<string> places;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            places.push_back(s);
        }
        vector<int> sol;
        for (int i = 0; i < k; i++)
            sol.push_back((v + i + n - 1) % n);
        sort(sol.begin(), sol.end());
        for (int i: sol) printf(" %s", places[i].c_str());
        printf("\n");
    }        
    return 0;
}
