/* Edmonds-Karp algorithm - O(VE^2) */
namespace EdmondsKarp {
    const int INF = 0x3f3f3f3f;

    int augment(int s, int t, FlowGraph &g) {
        vector<int> prv(g.V, -1), flow(g.V, INF);
        prv[s] = s;
        queue<int> q({s});
        while (!q.empty() && prv[t] == -1) {
            int v = q.front();
            q.pop();
            for (int i: g.adj[v]) {
                if (prv[g.edges[i].v] == -1 && g.edges[i].cap) {
                    prv[g.edges[i].v] = i;
                    flow[g.edges[i].v] = min(flow[v], g.edges[i].cap);
                    q.push(g.edges[i].v);
                }
            }
        }
        if (prv[t] == -1) return 0;
        for (int v = t; v != s; v = g.edges[prv[v]^1].v) {
            g.edges[prv[v]].cap -= flow[t];
            g.edges[prv[v]^1].cap += flow[t];
        }
        return flow[t];
    }

    int max_flow(int s, int t, FlowGraph &g) {
        int total_flow = 0;
        while (int flow = augment(s, t, g)) total_flow += flow;
        return total_flow;
    }
}
