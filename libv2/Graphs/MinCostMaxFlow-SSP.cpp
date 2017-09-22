/* 
   Minimum cost maximum flow: Successive Shortest Path implementation
   O(E*V + U*V^2), where U is the maximum flow
*/
template<class FTYPE, class CTYPE> struct MinCostMaxFlowSSP {
    static const CTYPE CINF = numeric_limits<CTYPE>::max() / 2;
    static const FTYPE FINF = numeric_limits<FTYPE>::max() / 2;
    
    CostFlowGraph<FTYPE, CTYPE> &g;
    vector<CTYPE> d, p;
 
    MinCostMaxFlowSSP(CostFlowGraph<FTYPE, CTYPE> &_g) : g(_g) {
        d.resize(g.V);
        p.resize(g.V);
    }
 
    void init_p(int s) {
        fill(d.begin(), d.end(), CINF);
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
 
    pair<FTYPE, CTYPE> augment(int s, int t) {
        fill(d.begin(), d.end(), CINF);
        d[s] = 0;
        vector<bool> done(g.V, 0);
        vector<int> prv(g.V, -1);
        vector<FTYPE> flow(g.V);
        flow[s] = FINF;
        while (1) {
            int v;
            CTYPE dist_v = CINF;
            for (int w = 0; w < g.V; w++) {
                if (!done[w] && d[w] < dist_v) {
                    v = w;
                    dist_v = d[w];
                }
            }
            if (dist_v == CINF) break;
            for (int i: g.adj[v]) {
                int w = g.edges[i].v;
                FTYPE cap = g.edges[i].cap;
                CTYPE cst = g.edges[i].cst;
                if (cap && d[w] > d[v] + cst + p[v] - p[w]) {
                    d[w] = d[v] + cst + p[v] - p[w];
                    prv[w] = i;
                    flow[w] = min(flow[v], cap);
                }
            }
            done[v] = 1;
        }
        if (d[t] == CINF) return make_pair(-1, 0);
        for (int v = 0; v < g.V; v++) p[v] += d[v];
 
        CTYPE flow_cost = 0;
        for (int v = t; v != s; v = g.edges[prv[v]^1].v) {
            g.edges[prv[v]].cap -= flow[t];
            g.edges[prv[v]^1].cap += flow[t];
            flow_cost += flow[t] * g.edges[prv[v]].cst;
        }
        return make_pair(flow[t], flow_cost);
    }
 
    // Returns a pair (max flow, min cost)
    pair<FTYPE, CTYPE> mcmf(int s, int t) {
        pair<FTYPE, CTYPE> ret(0, 0), aug;
        init_p(s);
        while ((aug = augment(s, t)).first != -1) {
            ret.first += aug.first;
            ret.second += aug.second;
        }
        return ret;
    }
};
