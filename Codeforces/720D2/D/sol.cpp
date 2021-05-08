#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr, args)
#define readArray(v, n) for_each(v.begin(), v.begin() + n, [](auto &x) { cin >> x; })

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

template<class T = int> inline T read() {
    T x;
    cin >> x;
    return x;
}

template<class T, class C = vector<T>> inline void printArray(C v, int n = -1) {
    int cnt = 0;
    for (auto it = v.begin(); it != v.end() && cnt != n; it++, cnt++) {
        cout << *it << (next(it) == v.end() || cnt + 1 == n ? '\n' : ' ');
    }
}

int dfs(int v, vector<set<int>> &adj, vector<pii> &removed, int p = -1) {
    int cnt = 0;
    vector<int> avail;
    for (int nxt : adj[v]) {
        if (nxt != p) {
            if (!dfs(nxt, adj, removed, v)) {
                avail.push_back(nxt);
            } else {
                cnt++;
            }
        }
    }

    int removedParent = 0;
    if (adj[v].size() - cnt > 2 && p != -1) {
        removed.push_back({p, v});
        cnt++;
        removedParent = 1;
    }

    while (adj[v].size() - cnt > 2) {
        int u = avail.back();
        avail.pop_back();
        removed.push_back({u, v});
        cnt++;
    }

    return removedParent;
}

int find(int v, vector<set<int>> &adj, vector<bool> &seen) {
    seen[v] = 1;
    for (int nxt : adj[v])
        if (!seen[nxt])
            return find(nxt, adj, seen);
    return v;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int t = read(); t--;) {
        int n = read();
        vector<set<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
        }

        vector<pii> removed;
        dfs(1, adj, removed);
        for (auto [u, v] : removed) {
            adj[u].erase(v);
            adj[v].erase(u);
        }

        vector<set<int>> deg(3);
        for (int v = 1; v <= n; v++) {
            deg[adj[v].size()].insert(v);
        }

        vector<pii> inserted;
        while (deg[0].size() > 1) {
            int u = *deg[0].begin();
            deg[0].erase(deg[0].begin());
            int v = *deg[0].begin();
            deg[0].erase(deg[0].begin());
            inserted.push_back({u, v});
            deg[1].insert(u);
            deg[1].insert(v);
            adj[u].insert(v);
            adj[v].insert(u);
        }

        if (deg[0].size() == 1) {
            int u = *deg[0].begin();
            deg[0].erase(deg[0].begin());
            int v = *deg[1].begin();
            deg[1].erase(deg[1].begin());
            inserted.push_back({u, v});
            deg[1].insert(u);
            adj[u].insert(v);
            adj[v].insert(u);
        }

        vector<bool> seen(n + 1, 0);
        vector<pii> ends;
        for (int v = 1; v <= n; v++) {
            if (seen[v] || adj[v].size() != 1)
                continue;
            ends.push_back({v, find(v, adj, seen)});
        }

        for (size_t i = 0; i + 1 < ends.size(); i++) {
            auto [u, v] = ends[i];
            auto [x, y] = ends[i + 1];
            inserted.push_back({u, y});
        }

        // debug("removed:\n");
        // for_each(removed.begin(), removed.end(),
        //          [](pii e) { debug("%d %d\n", e.first, e.second); });
        // debug("inserted:\n");
        // for_each(inserted.begin(), inserted.end(),
        //          [](pii e) { debug("%d %d\n", e.first, e.second); });
        assert(removed.size() == inserted.size());

        cout << removed.size() << '\n';
        for (size_t i = 0; i < removed.size(); i++) {
            auto [u, v] = removed[i];
            auto [x, y] = inserted[i];
            printArray<int>({u, v, x, y});
        }
    }
    return 0;
}
