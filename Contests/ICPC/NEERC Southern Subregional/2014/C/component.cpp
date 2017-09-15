#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;
typedef tuple<int, int, int> tiii;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;
const int MAXN = (int)3e5 + 10;
const int MAXL = 30;

/* A directed graph */
struct Graph {
    int V;
    vector<vector<int>> adj;
    
    Graph(int _V) : V(_V) {
        adj.resize(V);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

// Finds heavy paths without building a data structure over them.
struct HeavyLightSimple {
    const Graph &g;
    vector<int> head;   // Head of the heavy path containing i
    vector<int> parent; // Parent of node i

    vector<int> depth, heavy;
    int root;

    HeavyLightSimple(const Graph &_g, int _root) : g(_g), root(_root) {
        head.resize(g.V), parent.resize(g.V), depth.resize(g.V), heavy.resize(g.V, -1);
        parent[root] = -1, depth[root] = 0;
        dfs(root);
        for (int v = 0; v < g.V; v++)
            if (parent[v] == -1 || heavy[parent[v]] != v)
                for (int w = v; w != -1; w = heavy[w])
                    head[w] = v;        
    }

    int dfs(int v) {
        int hi = 0, ret = 1;
        for (int nxt: g.adj[v]) {
            if (nxt == parent[v]) continue;
            parent[nxt] = v;
            depth[nxt] = depth[v] + 1;
            int got = dfs(nxt);
            if (got > hi) {
                hi = got;
                heavy[v] = nxt;
            }
            ret += got;
        }
        return ret;
    }
};

vector<pair<string, string>> properties[MAXN];
map<string, set<pair<int, string>, greater<pair<int, string>>>> props[MAXN];

char buff[MAXL];

int main() {
    int n;
    scanf("%d", &n);
    Graph g(n + 1);
    for (int i = 1; i <= n; i++) {
        int p, k;
        scanf("%d%d", &p, &k);
        if (i) g.add_edge(p, i);
        while (k--) {
            scanf("%s", buff);
            for (int j = 0; buff[j] != 0; j++)
                if (buff[j] == '=')
                    buff[j] = ' ';            
            stringstream s(buff);
            string key, val;
            s >> key >> val;
            properties[i].push_back(make_pair(key, val));
        }
    }
    HeavyLightSimple hld(g, 1);
    for (int i = 1; i <= n; i++) {
        int head = hld.head[i];
        for (auto prop: properties[i]) {
            props[head][prop.first].insert(make_pair(hld.depth[i], prop.second));
            // debug("props[%d][%s] <- (%d, %s)\n", head, prop.first.c_str(),
            //       hld.depth[i], prop.second.c_str());
        }
    }

    int q;
    for (scanf("%d", &q); q--;) {
        int i;
        scanf("%d%s", &i, buff);
        string key(buff);
        bool found = 0;
        while (i != -1) {
            int head = hld.head[i];
            auto it = props[head].find(key);            
            if (it != props[head].end()) {
                // debug("Found %s in %d\n", key.c_str(), head);
                auto it2 = it->second.upper_bound(make_pair(hld.depth[i] + 1, ""));
                if (it2 != it->second.end()) {
                    printf("%s\n", it2->second.c_str());
                    found = 1;
                    break;
                }
            }
            i = hld.parent[head];
        }
        if (!found) printf("N/A\n");
        fflush(stdout);
    }            
    return 0;
}
