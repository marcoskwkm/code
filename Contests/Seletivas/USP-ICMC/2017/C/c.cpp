#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 210, MAXP = 15;

int penalty[MAXN][MAXP];
pii score[MAXN];

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    map<string, int> names;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        names[s] = i;
    }

    int last_t = 0;
    int ans = 0;
    for (int s = 0; s < m; s++) {
        string team, verdict;
        char prob;
        int t;
        cin >> team >> prob >> t >> verdict;
        bool leading = 1;
        for (int i = 1; i < n; i++)
            if (score[i] > score[0])
                leading = 0;
        if (leading) ans += t - last_t;
        last_t = t;
        int id = names[team];
        if (verdict == "OK") {
            score[id].first++;
            score[id].second -= t + penalty[id][prob - 'A'];
        }
        else {
            penalty[id][prob - 'A'] += 20;
        }
    }

    bool leading = 1;
    for (int i = 1; i < n; i++)
        if (score[i] > score[0])
            leading = 0;
    if (leading) ans += 300 - last_t;
    cout << ans << endl;
    return 0;
}
