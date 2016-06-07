#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = 1010;

map<string, int> mp;
string names[MAXN];
int prv[MAXN], nxt[MAXN];
int cnt = 0;

int getidx(string s) {
    if (mp.find(s) == mp.end()) {
        names[cnt] = s;
        mp[s] = cnt++;
    }
    return mp[s];
}

int main() {
    int n;
    scanf("%d", &n);
    memset(prv, -1, sizeof(prv));
    memset(nxt, -1, sizeof(nxt));
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        int ia = getidx(a), ib = getidx(b);
        prv[ia] = ib;
        nxt[ib] = ia;
    }
    int at = 0;
    while (prv[at] != -1) at = prv[at];
    while (at != -1) {
        printf("%s\n", names[at].c_str());
        at = nxt[at];
    }        
    return 0;
}
