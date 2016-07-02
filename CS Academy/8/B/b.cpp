#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    vector<string> v(n);
    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        int delta = 'z' - v[i][0];
        for (int j = 0; j < (int)v[i].size(); j++)
            v[i][j] = 'a' + (v[i][j] - 'a' + delta) % 26;
        mp[v[i]]++;
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", mp[v[i]] > 1);
    }    
    return 0;
}
