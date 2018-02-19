#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)1e5 + 10;

int v[MAXN];
int is_query[2 * MAXN];
int cnt[2 * MAXN];
map<string, int> mp;

int get_idx(const string &s) {
    static int sz = 0;
    auto it = mp.find(s);
    if (it == mp.end()) return mp[s] = sz++;
    return it->second;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i] = get_idx(s);
    }
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        is_query[get_idx(s)] = 1;
    }

    lint ans = 0;
    int cur = 0;
    int r = 0;
    for (int l = 0; l < n; l++) {
        while (cur < k && r < n) {
            if (is_query[v[r]]) {
                if (cnt[v[r]] == 0) cur++;
                cnt[v[r]]++;
            }
            r++;
        }
        if (cur == k) ans += n - r + 1;
        if (is_query[v[l]]) {
            if (cnt[v[l]] == 1) cur--;
            cnt[v[l]]--;
        }
    }

    cout << ans << endl;            
    return 0;
}
