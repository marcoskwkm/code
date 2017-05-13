#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

#include "util.h"
#include "../Graph.h"
#include "../Tarjan.h"

int main() {
    Graph g(8);
    vector<pair<int, int>> edges = {
        {2, 3},
        {1, 3},
        {3, 6},
        {6, 1},
        {1, 7},
        {6, 7},
        {6, 4},
        {7, 5},
        {5, 7},
    };
    for (auto p: edges) g.add_edge(p.first, p.second);
    Tarjan t(g);
    // Test components
    assert_equal_vectors(t.cmp[t.cmp_id[0]], {0});    
    assert_equal_vectors(t.cmp[t.cmp_id[1]], {1, 3, 6});
    assert_equal_vectors(t.cmp[t.cmp_id[2]], {2});    
    assert_equal_vectors(t.cmp[t.cmp_id[4]], {4});    
    assert_equal_vectors(t.cmp[t.cmp_id[5]], {5, 7});

    // Test contracted graph
    Graph cg = t.getContractedGraph();
    assert_equal_vectors(cg.adj[t.cmp_id[2]], {t.cmp_id[1]});
    assert_equal_vectors(cg.adj[t.cmp_id[1]], {t.cmp_id[4], t.cmp_id[5]});
    assert_equal_vectors(cg.adj[t.cmp_id[4]], {});
    assert_equal_vectors(cg.adj[t.cmp_id[5]], {});
    
    fprintf(stderr, "Test passed!\n");
    return 0;
}
