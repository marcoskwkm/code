#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXT = 21, MAXN = 110;

int dp[1 << MAXT];
int cost[MAXN];
int topics[MAXN];

int main() {
    string line;
    map<string, int> id;
    int n = 0, m = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> cost[n];
        string x;
        while (ss >> x) {
            if (id.find(x) == id.end())
                id[x] = m++;
            topics[n] |= (1 << id[x]);
        }
        n++;
    }

    memset(dp, INF, sizeof(dp));
    dp[0] = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        for (int i = 0; i < n; i++) {
            int nxt = mask | topics[i];
            dp[nxt] = min(dp[nxt], dp[mask] + cost[i]);
        }
    }
    printf("%d\n", dp[(1 << m) - 1]);            
    return 0;
}
