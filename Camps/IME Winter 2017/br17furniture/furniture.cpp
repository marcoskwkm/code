#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 110;

bool seen[MAXN], done[MAXN];
int sum[MAXN], low[MAXN], len[MAXN];

int main() {
    vector<int> in;
    int ww;
    while (cin >> ww) in.push_back(ww);
    int n = in.size() / 2;
    vector<int> w;
    for (int i = 0; i < n; i++)
        w.push_back(in[i]);
    vector<int> pos(n);
    for (int i = 0; i < n; i++)
        pos[i] = in[i + n];

    int n_cycles = 0;
    int best_cycle = 0;
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        int cur = i;
        low[n_cycles] = INF;
        while (!seen[cur]) {
            seen[cur] = 1;
            sum[n_cycles] += w[cur];
            low[n_cycles] = min(low[n_cycles], w[cur]);
            cur = pos[cur];
            len[n_cycles]++;
        }
        if (low[n_cycles] < low[best_cycle])
            best_cycle = n_cycles;
        n_cycles++;
    }

    int ans = 0;
    for (int i = 0; i < n_cycles; i++) {
        if (i == best_cycle) continue;
        if ((len[i] + 1) * low[best_cycle] < (len[i] - 3) * low[i]) {
            sum[best_cycle] += sum[i];
            len[best_cycle] += len[i];
            done[i] = 1;
            ans += low[i] + low[best_cycle];
        }
    }

    for (int i = 0; i < n_cycles; i++) {
        if (done[i]) continue;
        ans += (len[i] - 1) * low[i] + sum[i] - low[i];
    }

    cout << ans << endl;
            
    return 0;
}
