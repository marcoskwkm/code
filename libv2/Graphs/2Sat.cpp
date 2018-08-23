/* 
   Finds one solution for a 2-sat instance or informs there isn't one.
   Variable x and its negation should have indices 2 * x and 2 * x + 1.
*/

struct SatSolver {
    bool solvable;
    vector<int> value; // 0 - false, 1 - true
    
    const Graph &g;

    SatSolver(const Graph &_g) : g(_g) {
        value.resize(g.V);
        Tarjan tarjan(g);
        for (int v = 0; v < g.V; v += 2) {
            if (tarjan.cmp_id[v] == tarjan.cmp_id[v + 1]) {
                solvable = false;
                return;
            }
        }
        solvable = true;
        Graph gc = tarjan.getContractedGraph();
        TopSort ts(gc);
        vector<int> _value(gc.V, -1);
        for (int c: ts.ord) {
            if (_value[c] == -1) {
                _value[c] = 0;
                for (int v: tarjan.cmp[c]) {
                    value[v] = 0;
                    value[v ^ 1] = 1;
                    _value[tarjan.cmp_id[v ^ 1]] = 1;
                }
            }
        }
    }
};
