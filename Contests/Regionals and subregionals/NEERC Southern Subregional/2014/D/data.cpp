#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

struct Server {
    lint cap;
    int i, k;
    Server(lint _cap = 0, int _i = 0, int _k = 0) : cap(_cap), i(_i), k(_k) {}
    bool operator<(const Server &that) { return cap > that.cap; }
};

int main() {
    int n;
    lint m;
    cin >> n >> m;
    vector<Server> servers;
    for (int i = 0; i < n; i++) {        
        lint cap;
        int k;
        scanf("%lld%d", &cap, &k);
        servers.push_back(Server(cap, i, k));
    }
    sort(servers.begin(), servers.end());
    lint sum = 0;
    multiset<pll> high_voltage;
    multiset<pll, greater<pll>> low_voltage;
    multiset<pll> all;
    int n_low = 0;
    set<int> idx;
    for (const Server &server: servers) {
        if (sum < m) {
            sum += server.cap;
            all.insert(pll(server.cap, server.i + 1));
            if (!server.k) high_voltage.insert(pll(server.cap, server.i + 1));
            else n_low++;
        }
        else if (server.k) low_voltage.insert(pll(server.cap, server.i + 1));
    }

    while (!high_voltage.empty() && !low_voltage.empty() &&
           sum - high_voltage.begin()->first + low_voltage.begin()->first >= m) {
        sum -= high_voltage.begin()->first;
        all.erase(*high_voltage.begin());
        sum += low_voltage.begin()->first;
        all.insert(*low_voltage.begin());
        high_voltage.erase(high_voltage.begin());
        low_voltage.erase(low_voltage.begin());
        n_low++;
    }

    printf("%d %d\n", (int)all.size(), n_low);
    for (pll p: all) printf("%lld ", p.second);
    printf("\n");
    return 0;
}
