/*
  Finds a solution for a 2SAT instance
  g is the implication graph. v must be the negation of v ^ 1
*/

template<class EType> struct TwoSatSolver {
    Graph<EType> &g;
    bool solvable;
    vector<bool> value;

    TwoSatSolver(Graph<EType> &_g) : g(_g) {
        value.resize(g.V);
        Tarjan tarjan(g);
        for (int v = 0; v < g.V; v += 2) {
            if (tarjan.comp_id[v] == tarjan.comp_id[v + 1]) {
                solvable = false;
                return;
            }
        }
        solvable = true;
        auto gc = tarjan.get_contracted_graph();
        auto ord = top_sort(gc);
        vector<int> _value(gc.V, -1);
        for (int c: ord) {
            if (_value[c] == -1) {
                _value[c] = 0;
                for (int v: tarjan.comps[c]) {
                    value[v] = 0;
                    value[v ^ 1] = 1;
                    _value[tarjan.comp_id[v ^ 1]] = 1;
                }
            }
        }
    }
};
