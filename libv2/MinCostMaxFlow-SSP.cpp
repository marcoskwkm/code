/* 
   Minimum cost maximum flow: Successive Shortest Path implementation
   O(E*V + U*V^2), where U is the maximum flow
*/
struct MinCostMaxFlowSSP {
    CostFlowGraph &g;
    vector<int> d, p;

    MinCostMaxFlowSSP(CostFlowGraph &_g) : g(_g) {
        d.resize(g.V);
        p.resize(g.V);
    }

    void init_p(int s) {
        fill(d.begin(), d.end(), INF);
        d[s] = 0;
        queue<int> q({s});
        vector<bool> queued(g.V, 0);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            queued[v] = 0;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v;
                if (!g.edges[i].cap) continue;
                if (d[w] > d[v] + g.edges[i].cst) {
                    d[w] = d[v] + g.edges[i].cst;
                    if (!queued[w]) {
                        q.push(w);
                        queued[w] = 1;
                    }
                }
            }
        }
        for (int v = 0; v < g.V; v++)
            p[v] = d[v];
    }

    pair<int, int> augment(int s, int t) {
        fill(d.begin(), d.end(), INF);
        d[s] = 0;
        vector<bool> done(g.V, 0);
        vector<int> prv(g.V, -1), flow(g.V);
        flow[s] = INF;
        while (1) {
            int v;
            int dist_v = INF;
            for (int w = 0; w < g.V; w++) {
                if (!done[w] && d[w] < dist_v) {
                    v = w;
                    dist_v = d[w];
                }
            }
            if (dist_v == INF) break;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v;
                int cap = g.edges[i].cap, cst = g.edges[i].cst;
                if (cap && d[w] > d[v] + cst + p[v] - p[w]) {
                    d[w] = d[v] + cst + p[v] - p[w];
                    prv[w] = i;
                    flow[w] = min(flow[v], cap);
                }
            }
            done[v] = 1;
        }
        if (d[t] == INF) return make_pair(-1, 0);
        for (int v = 0; v < g.V; v++) p[v] += d[v];

        int flow_cost = 0;
        for (int v = t; v != s; v = g.edges[prv[v]^1].v) {
            g.edges[prv[v]].cap -= flow[t];
            g.edges[prv[v]^1].cap += flow[t];
            flow_cost += flow[t] * g.edges[prv[v]].cst;
        }
        return make_pair(flow[t], flow_cost);
    }

    // Returns a pair (max flow, min cost)
    pair<int, int> mcmf(int s, int t) {
        pair<int, int> ret(0, 0), aug;
        init_p(s);
        while ((aug = augment(s, t)).first != -1) {
            ret.first += aug.first;
            ret.second += aug.second;
        }
        return ret;
    }
};
