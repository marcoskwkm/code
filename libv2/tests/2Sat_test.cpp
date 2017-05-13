#include <bits/stdc++.h>
using namespace std;

#define debug(args...) fprintf(stderr,args)

typedef long long lint;
typedef pair<int, int> pii;
typedef pair<lint, lint> pll;

const int INF = 0x3f3f3f3f;
const lint LINF = 0x3f3f3f3f3f3f3f3fll;

#include "../Graph.h"
#include "../Tarjan.h"
#include "../TopSort.h"
#include "../2Sat.h"

int main() {
    Graph g(8);
    vector<pii> edges = {
        {0^1, 4},
        {4^1, 0},
        {2, 4},
        {4^1, 2^1},
        {4, 6},
        {6^1, 4^1},
        {6, 6^1},
        {6, 2},
        {2^1, 6^1},
    };
    for (pii p: edges) g.add_edge(p.first, p.second);
    SatSolver sat(g);
    assert(sat.solvable);
    debug("%d %d %d %d\n", sat.value[0], sat.value[2], sat.value[4], sat.value[6]);
    assert(sat.value[0] == 1);
    assert(sat.value[2] == 0);
    assert(sat.value[4] == 0);
    assert(sat.value[6] == 0);
    debug("Tests passed!\n");
    return 0;
}
